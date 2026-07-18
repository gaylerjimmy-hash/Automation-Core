#pragma once

namespace automation_core {

enum class FrameError {
    None,
    Empty,
    TooLarge,
    TimedOut,
    MissingTerminator
};

} // namespace automation_core
