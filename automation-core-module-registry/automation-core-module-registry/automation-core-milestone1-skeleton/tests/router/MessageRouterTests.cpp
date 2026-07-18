// MessageRouter tests go here.
#include "automation_core/Protocol/Message.h"
#include "automation_core/Protocol/Validator.h"
#include "automation_core/Registry/ModuleRegistry.h"
#include "automation_core/Response/ResponseBuilder.h"
#include "automation_core/Router/MessageRouter.h"

#include <iostream>
#include <string>
#include <variant>

using namespace automation_core;

namespace {

int failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "MessageRouter: " << message << '\n';
        ++failures;
    }
}

Message make_hello(
    std::string module_id = "scale-01",
    std::string session_id = "81A9C5D2",
    std::string message_id = "msg-1"
) {
    return Message{
        HelloMessage{
            std::move(message_id),
            "Scale",
            std::move(module_id),
            "1.0.0",
            "1",
            std::move(session_id)
        }
    };
}

const HelloAckMessage* get_ack(const RouteResult& result) {
    if (!result.response) {
        return nullptr;
    }

    return std::get_if<HelloAckMessage>(&result.response->payload);
}

const ErrorMessage* get_error(const RouteResult& result) {
    if (!result.response) {
        return nullptr;
    }

    return std::get_if<ErrorMessage>(&result.response->payload);
}

void test_routes_valid_hello() {
    Validator validator;
    ModuleRegistry registry;
    ResponseBuilder responses;
    MessageRouter router{validator, registry, responses};

    const RouteResult result =
        router.route("connection-1", make_hello());

    const auto* ack = get_ack(result);
    const auto module = registry.find("scale-01");

    expect(result.has_response(), "valid HELLO produced no response");
    expect(ack != nullptr, "valid HELLO did not produce HELLO_ACK");

    expect(
        ack && ack->message_id == "msg-1",
        "HELLO_ACK did not preserve message ID"
    );

    expect(
        ack && ack->connection_id == "connection-1",
        "HELLO_ACK used wrong connection ID"
    );

    expect(
        module && module->connection_id == "connection-1",
        "valid HELLO was not registered"
    );
}

void test_rejects_invalid_hello() {
    Validator validator;
    ModuleRegistry registry;
    ResponseBuilder responses;
    MessageRouter router{validator, registry, responses};

    Message message = make_hello();
    std::get<HelloMessage>(message.payload).session_id = "bad";

    const RouteResult result =
        router.route("connection-1", message);

    const auto* error = get_error(result);

    expect(error != nullptr, "invalid HELLO did not produce ERROR");

    expect(
        error && error->code == "SESSION",
        "validation error code was not preserved"
    );

    expect(
        registry.list().empty(),
        "invalid HELLO entered the registry"
    );
}

void test_rejects_missing_connection_id() {
    Validator validator;
    ModuleRegistry registry;
    ResponseBuilder responses;
    MessageRouter router{validator, registry, responses};

    const RouteResult result =
        router.route("", make_hello());

    const auto* error = get_error(result);

    expect(
        error && error->code == "CONNECTION",
        "missing connection ID was not rejected"
    );

    expect(
        registry.list().empty(),
        "message without connection ID entered registry"
    );
}

void test_reconnects_same_session() {
    Validator validator;
    ModuleRegistry registry;
    ResponseBuilder responses;
    MessageRouter router{validator, registry, responses};

    router.route("connection-1", make_hello());

    const RouteResult result =
        router.route("connection-2", make_hello());

    const auto* ack = get_ack(result);
    const auto module = registry.find("scale-01");

    expect(
        ack != nullptr,
        "same-session reconnect did not produce HELLO_ACK"
    );

    expect(
        module && module->connection_id == "connection-2",
        "same-session reconnect did not update connection binding"
    );
}

void test_rejects_duplicate_identity() {
    Validator validator;
    ModuleRegistry registry;
    ResponseBuilder responses;
    MessageRouter router{validator, registry, responses};

    router.route(
        "connection-1",
        make_hello("scale-01", "81A9C5D2", "msg-1")
    );

    const RouteResult result = router.route(
        "connection-2",
        make_hello("scale-01", "AAAAAAAA", "msg-2")
    );

    const auto* error = get_error(result);
    const auto module = registry.find("scale-01");

    expect(
        error && error->code == "DUPLICATE_IDENTITY",
        "duplicate identity was not rejected correctly"
    );

    expect(
        module && module->connection_id == "connection-1",
        "duplicate identity replaced authoritative registration"
    );
}

void test_rejects_quarantined_identity() {
    Validator validator;
    ModuleRegistry registry;
    ResponseBuilder responses;
    MessageRouter router{validator, registry, responses};

    router.route("connection-1", make_hello());
    registry.quarantine("scale-01");

    const RouteResult result =
        router.route("connection-2", make_hello());

    const auto* error = get_error(result);

    expect(
        error && error->code == "QUARANTINED",
        "quarantined identity was not rejected"
    );
}

void test_rejects_unsupported_message() {
    Validator validator;
    ModuleRegistry registry;
    ResponseBuilder responses;
    MessageRouter router{validator, registry, responses};

    const Message message{
        ErrorMessage{
            "msg-1",
            "TEST",
            "Not an inbound HELLO"
        }
    };

    const RouteResult result =
        router.route("connection-1", message);

    const auto* error = get_error(result);

    expect(
        error && error->code == "UNSUPPORTED",
        "unsupported message type was not rejected"
    );
}

} // namespace

int run_message_router_tests() {
    failures = 0;

    test_routes_valid_hello();
    test_rejects_invalid_hello();
    test_rejects_missing_connection_id();
    test_reconnects_same_session();
    test_rejects_duplicate_identity();
    test_rejects_quarantined_identity();
    test_rejects_unsupported_message();

    return failures;
}
