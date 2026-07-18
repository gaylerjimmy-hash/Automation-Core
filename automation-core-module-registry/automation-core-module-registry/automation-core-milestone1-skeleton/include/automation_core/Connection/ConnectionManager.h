#pragma once

#include "automation_core/Connection/Connection.h"

#include <chrono>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace automation_core {

class ConnectionManager {
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    std::string open(
        const std::string& transport_name,
        TimePoint now = Clock::now()
    );

    bool close(const std::string& connection_id);

    bool touch(
        const std::string& connection_id,
        TimePoint now = Clock::now()
    );

    bool quarantine(const std::string& connection_id);

    std::vector<std::string> expire_stale(
        std::chrono::milliseconds timeout,
        TimePoint now = Clock::now()
    );

    [[nodiscard]] std::optional<Connection> find(
        const std::string& connection_id
    ) const;

    [[nodiscard]] std::vector<Connection> list() const;

private:
    std::unordered_map<std::string, Connection> connections_;
    unsigned long next_connection_number_{1};
};

} // namespace automation_core
