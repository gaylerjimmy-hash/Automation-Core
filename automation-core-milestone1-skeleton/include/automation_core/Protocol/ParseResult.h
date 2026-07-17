#pragma once

#include "automation_core/Protocol/Message.h"

#include <optional>
#include <string>

namespace automation_core {

struct ParseResult {
    std::optional<Message> message;
    std::string error;

    [[nodiscard]] bool ok() const noexcept {
        return message.has_value();
    }
};

} // namespace automation_core
