#include "automation_core/Connection/ConnectionManager.h"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>

using automation_core::ConnectionManager;
using automation_core::ConnectionState;

namespace {

int failures = 0;

void check(bool condition, const std::string& message) {
    if (!condition) {
        ++failures;
        std::cerr << "ConnectionManager: " << message << '\n';
    }
}

} // namespace

int run_connection_manager_tests() {
    failures = 0;

    const auto start = ConnectionManager::TimePoint{};
    ConnectionManager manager;

    const auto first = manager.open("serial:/dev/ttyUSB0", start);
    const auto second = manager.open("tcp:192.168.1.20:9000", start);

    check(first == "conn-1", "first connection ID is not deterministic");
    check(second == "conn-2", "second connection ID is not deterministic");

    const auto opened = manager.find(first);
    check(opened.has_value(), "opened connection cannot be found");
    check(
        opened && opened->state == ConnectionState::Connected,
        "opened connection is not Connected"
    );
    check(
        opened && opened->transport_name == "serial:/dev/ttyUSB0",
        "transport name was not retained"
    );

    const auto activity = start + std::chrono::seconds(5);
    check(manager.touch(first, activity), "touch rejected active connection");
    check(
        manager.find(first)->last_activity == activity,
        "touch did not update activity time"
    );

    check(manager.quarantine(second), "quarantine rejected active connection");
    check(
        manager.find(second)->state == ConnectionState::Quarantined,
        "quarantine did not update state"
    );
    check(
        !manager.touch(second, activity),
        "quarantined connection accepted activity"
    );

    const auto expired = manager.expire_stale(
        std::chrono::seconds(10),
        start + std::chrono::seconds(15)
    );
    check(expired.size() == 1 && expired.front() == first,
          "stale active connection was not expired");
    check(
        manager.find(first)->state == ConnectionState::TimedOut,
        "expired connection is not TimedOut"
    );
    check(
        manager.find(second)->state == ConnectionState::Quarantined,
        "quarantined connection was incorrectly timed out"
    );

    check(manager.close(first), "close rejected timed-out connection");
    check(
        manager.find(first)->state == ConnectionState::Disconnected,
        "close did not set Disconnected"
    );
    check(!manager.close(first), "closing twice should report no transition");
    check(!manager.close("missing"), "unknown connection was closed");
    check(!manager.touch("missing", activity), "unknown connection was touched");
    check(!manager.quarantine("missing"), "unknown connection was quarantined");

    const auto all = manager.list();
    check(all.size() == 2, "list returned the wrong number of connections");
    check(
        all.size() == 2 &&
        all[0].connection_id == "conn-1" &&
        all[1].connection_id == "conn-2",
        "list order is not deterministic"
    );

    bool empty_transport_rejected = false;
    try {
        manager.open("", start);
    } catch (const std::invalid_argument&) {
        empty_transport_rejected = true;
    }
    check(empty_transport_rejected, "empty transport name was accepted");

    bool negative_timeout_rejected = false;
    try {
        manager.expire_stale(std::chrono::milliseconds(-1), start);
    } catch (const std::invalid_argument&) {
        negative_timeout_rejected = true;
    }
    check(negative_timeout_rejected, "negative timeout was accepted");

    return failures;
}
