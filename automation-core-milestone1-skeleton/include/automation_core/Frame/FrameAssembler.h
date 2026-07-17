#pragma once

#include "automation_core/Frame/FrameResult.h"

#include <chrono>
#include <cstddef>
#include <string>

namespace automation_core {

class FrameAssembler {
public:
    explicit FrameAssembler(
        std::size_t maximum_frame_size = 1024,
        std::chrono::milliseconds frame_timeout =
            std::chrono::milliseconds{1000}
    );

    [[nodiscard]] FrameResult assemble(
        const std::string& connection_id,
        const std::string& raw_input
    ) const;

private:
    std::size_t maximum_frame_size_;
    std::chrono::milliseconds frame_timeout_;
};

} // namespace automation_core
