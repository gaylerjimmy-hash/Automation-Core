#include "automation_core/Protocol/Validator.h"

#include <utility>

namespace automation_core {

Validator::Validator(std::string supported_protocol_version)
    : supported_protocol_version_(
        std::move(supported_protocol_version)
      ) {}

ValidationResult Validator::validate(
    const Message& message
) const {
    (void)message;
    return {
        ValidationStatus::Rejected,
        "NOT_IMPLEMENTED",
        "Validator is not implemented yet."
    };
}

} // namespace automation_core
