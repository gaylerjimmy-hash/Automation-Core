#pragma once

#include "automation_core/Protocol/Message.h"
#include "automation_core/Protocol/ValidationResult.h"

#include <string>

namespace automation_core {

class Validator {
public:
    explicit Validator(std::string supported_protocol_version = "1");

    [[nodiscard]] ValidationResult validate(
        const Message& message
    ) const;

private:
    std::string supported_protocol_version_;
};

} // namespace automation_core
