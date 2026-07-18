#pragma once

#include "automation_core/Frame/Frame.h"
#include "automation_core/Frame/FrameError.h"

#include <optional>
#include <string>

namespace automation_core {

struct FrameResult {
    std::optional<Frame> frame;
    FrameError error{FrameError::None};
    std::string detail;

    [[nodiscard]] bool ok() const noexcept {
        return frame.has_value();
    }
};

} // namespace automation_core
