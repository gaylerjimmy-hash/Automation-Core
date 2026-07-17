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

    [[nodiscard]] std::optional<Module> find(
        const std::string& module_id
    ) const;

    [[nodiscard]] std::vector<Module> list() const;

private:
    std::unordered_map<std::string, Module> modules_;
};

} // namespace automation_core
