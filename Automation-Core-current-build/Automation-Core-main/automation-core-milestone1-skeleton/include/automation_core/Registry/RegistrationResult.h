#pragma once

#include <string>

namespace automation_core {

enum class RegistrationStatus {
    Added,
    Reconnected,
    Rejected,
    DuplicateIdentity,
    Quarantined
};

struct RegistrationResult {
    RegistrationStatus status{RegistrationStatus::Rejected};
    std::string detail;
};

} // namespace automation_core
