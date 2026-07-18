#pragma once

#include "automation_core/Frame/Frame.h"
#include "automation_core/Protocol/ParseResult.h"

namespace automation_core {

class Parser {
public:
    [[nodiscard]] ParseResult parse(const Frame& frame) const;
};

} // namespace automation_core
