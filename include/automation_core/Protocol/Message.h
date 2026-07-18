#pragma once

#include <string>
#include <variant>

namespace automation_core {

struct HelloMessage {
    std::string message_id;
    std::string module_type;
    std::string module_id;
    std::string firmware_version;
    std::string protocol_version;
    std::string session_id;
};

struct HelloAckMessage {
    std::string message_id;
    std::string connection_id;
    std::string status;
};

struct ErrorMessage {
    std::string message_id;
    std::string code;
    std::string detail;
};

using MessagePayload = std::variant<
    HelloMessage,
    HelloAckMessage,
    ErrorMessage
>;

struct Message {
    MessagePayload payload;
};

} // namespace automation_core
