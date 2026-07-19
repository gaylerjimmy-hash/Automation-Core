#include "automation_core/Response/ResponseBuilder.h"

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


} // namespace automation_core


