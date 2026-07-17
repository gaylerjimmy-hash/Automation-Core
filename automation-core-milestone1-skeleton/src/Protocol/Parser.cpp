#include "automation_core/Protocol/Parser.h"

namespace automation_core {

ParseResult Parser::parse(const Frame& frame) const {
    (void)frame;
    return {
        std::nullopt,
        "Parser is not implemented yet."
    };
}

} // namespace automation_core
