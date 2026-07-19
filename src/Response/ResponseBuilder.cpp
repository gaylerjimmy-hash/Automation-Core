#include "automation_core/Response/ResponseBuilder.h"

#include <stdexcept>
#include <type_traits>
#include <variant>

namespace automation_core {

Message ResponseBuilder::hello_ack(
    const std::string& message_id,
    const std::string& connection_id
) const
{
    return Message{
        HelloAckMessage{
            message_id,
            connection_id,
            "accepted"
        }
    };
}

Message ResponseBuilder::error(
    const std::string& message_id,
    const std::string& code,
    const std::string& detail
) const
{
    return Message{
        ErrorMessage{
            message_id,
            code,
            detail
        }
    };
}

std::string ResponseBuilder::serialize(
    const Message& message
) const
{
    return std::visit(
        [](const auto& payload) -> std::string {
            using Payload = std::decay_t<decltype(payload)>;

            if constexpr (std::is_same_v<Payload, HelloMessage>) {
                return
                    "HELLO"
                    "|message_id=" + payload.message_id +
                    "|module_type=" + payload.module_type +
                    "|module_id=" + payload.module_id +
                    "|firmware_version=" + payload.firmware_version +
                    "|protocol_version=" + payload.protocol_version +
                    "|session_id=" + payload.session_id;
            }
            else if constexpr (std::is_same_v<Payload, HelloAckMessage>) {
                return
                    "HELLO_ACK"
                    "|message_id=" + payload.message_id +
                    "|connection_id=" + payload.connection_id +
                    "|status=" + payload.status;
            }
            else if constexpr (std::is_same_v<Payload, ErrorMessage>) {
                return
                    "ERROR"
                    "|message_id=" + payload.message_id +
                    "|code=" + payload.code +
                    "|detail=" + payload.detail;
            }

            throw std::logic_error("Unsupported message payload");
        },
        message.payload
    );
}

} // namespace automation_core
