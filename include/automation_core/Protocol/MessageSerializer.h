#pragma once

#include "automation_core/Protocol/Message.h"

#include <string>

namespace automation_core {

class MessageSerializer {
public:
    [[nodiscard]] std::string serialize(
        const Message& message
    ) const;
};

} // namespace automation_core