#include "automation_core/Router/MessageRouter.h"

namespace automation_core {

MessageRouter::MessageRouter(
    Validator& validator,
    ModuleRegistry& registry,
    ResponseBuilder& responses
)
    : validator_(validator),
      registry_(registry),
      responses_(responses) {}

RouteResult MessageRouter::route(
    const std::string& connection_id,
    const Message& message
) {
    (void)connection_id;
    (void)message;
    return {
        std::nullopt,
        "MessageRouter is not implemented yet."
    };
}

} // namespace automation_core
