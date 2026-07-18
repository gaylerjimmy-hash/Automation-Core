#pragma once

#include "automation_core/Registry/Module.h"
#include "automation_core/Registry/RegistrationResult.h"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace automation_core {

class ModuleRegistry {
public:
    RegistrationResult register_module(const Module& module);

    bool mark_offline_by_connection(const std::string& connection_id);
    bool quarantine(const std::string& module_id);

    [[nodiscard]] std::optional<Module> find(
        const std::string& module_id
    ) const;

    [[nodiscard]] std::optional<Module> find_by_connection(
        const std::string& connection_id
    ) const;

    [[nodiscard]] std::vector<Module> list() const;

private:
    std::unordered_map<std::string, Module> modules_;
};

} // namespace automation_core
