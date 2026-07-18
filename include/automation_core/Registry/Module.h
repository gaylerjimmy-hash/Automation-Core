#pragma once

#include <string>

namespace automation_core {

enum class ModuleStatus {
    Active,
    Offline,
    Quarantined
};

struct Module {
    std::string module_id;
    std::string module_type;
    std::string firmware_version;
    std::string protocol_version;
    std::string session_id;
    std::string connection_id;
    ModuleStatus status{ModuleStatus::Active};
};

} // namespace automation_core
