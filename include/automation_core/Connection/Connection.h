#pragma once

#include <chrono>
#include <string>

namespace automation_core {

enum class ConnectionState {
    Connected,
    Disconnected,
    TimedOut,
    Quarantined
};

struct Connection {
    std::string connection_id;
    std::string transport_name;
    ConnectionState state{ConnectionState::Disconnected};
    std::chrono::steady_clock::time_point last_activity{};
};

} // namespace automation_core
