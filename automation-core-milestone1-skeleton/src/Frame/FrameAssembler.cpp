#include "automation_core/Frame/FrameAssembler.h"

namespace automation_core {

FrameAssembler::FrameAssembler(
    std::size_t maximum_frame_size,
    std::chrono::milliseconds frame_timeout
)
    : maximum_frame_size_(maximum_frame_size),
      frame_timeout_(frame_timeout) {}

FrameResult FrameAssembler::assemble(
    const std::string& connection_id,
    const std::string& raw_input
) const {
    (void)connection_id;
    (void)raw_input;
    return {
        std::nullopt,
        FrameError::Empty,
        "FrameAssembler is not implemented yet."
    };
}

} // namespace automation_core
