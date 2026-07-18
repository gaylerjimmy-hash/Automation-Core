#pragma once

#include "automation_core/Protocol/Message.h"

#include <optional>
#include <string>

namespace automation_core {

struct RouteResult {
    std::optional<Message> response;
    std::string detail;

    [[nodiscard]] bool has_response() const noexcept {
        return response.has_value();
    }
};

} // namespace automation_core
