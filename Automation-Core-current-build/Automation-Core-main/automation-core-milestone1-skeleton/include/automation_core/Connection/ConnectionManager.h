#pragma once

#include "automation_core/Connection/Connection.h"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace automation_core {

class ConnectionManager {
public:
    std::string open(const std::string& transport_name);
    bool close(const std::string& connection_id);
    bool touch(const std::string& connection_id);
    bool quarantine(const std::string& connection_id);

    [[nodiscard]] std::optional<Connection> find(
        const std::string& connection_id
    ) const;

    [[nodiscard]] std::vector<Connection> list() const;

private:
    std::unordered_map<std::string, Connection> connections_;
    unsigned long next_connection_number_{1};
};

} // namespace automation_core
