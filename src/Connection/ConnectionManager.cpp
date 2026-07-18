#include "automation_core/Connection/ConnectionManager.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace automation_core {

std::string ConnectionManager::open(
    const std::string& transport_name,
    TimePoint now
) {
    if (transport_name.empty()) {
        throw std::invalid_argument("transport name must not be empty");
    }

    const std::string connection_id =
        "conn-" + std::to_string(next_connection_number_++);

    Connection connection{
        connection_id,
        transport_name,
        ConnectionState::Connected,
        now
    };

    connections_.emplace(connection_id, std::move(connection));
    return connection_id;
}

bool ConnectionManager::close(const std::string& connection_id) {
    const auto iterator = connections_.find(connection_id);
    if (iterator == connections_.end()) {
        return false;
    }

    if (iterator->second.state == ConnectionState::Disconnected) {
        return false;
    }

    iterator->second.state = ConnectionState::Disconnected;
    return true;
}

bool ConnectionManager::touch(
    const std::string& connection_id,
    TimePoint now
) {
    const auto iterator = connections_.find(connection_id);
    if (iterator == connections_.end()) {
        return false;
    }

    if (iterator->second.state != ConnectionState::Connected) {
        return false;
    }

    iterator->second.last_activity = now;
    return true;
}

bool ConnectionManager::quarantine(const std::string& connection_id) {
    const auto iterator = connections_.find(connection_id);
    if (iterator == connections_.end()) {
        return false;
    }

    if (iterator->second.state != ConnectionState::Connected) {
        return false;
    }

    iterator->second.state = ConnectionState::Quarantined;
    return true;
}

std::vector<std::string> ConnectionManager::expire_stale(
    std::chrono::milliseconds timeout,
    TimePoint now
) {
    if (timeout.count() < 0) {
        throw std::invalid_argument("timeout must not be negative");
    }

    std::vector<std::string> expired;

    for (auto& entry : connections_) {
        Connection& connection = entry.second;

        if (connection.state != ConnectionState::Connected) {
            continue;
        }

        if (now - connection.last_activity >= timeout) {
            connection.state = ConnectionState::TimedOut;
            expired.push_back(connection.connection_id);
        }
    }

    std::sort(expired.begin(), expired.end());
    return expired;
}

std::optional<Connection> ConnectionManager::find(
    const std::string& connection_id
) const {
    const auto iterator = connections_.find(connection_id);
    if (iterator == connections_.end()) {
        return std::nullopt;
    }

    return iterator->second;
}

std::vector<Connection> ConnectionManager::list() const {
    std::vector<Connection> result;
    result.reserve(connections_.size());

    for (const auto& entry : connections_) {
        result.push_back(entry.second);
    }

    std::sort(
        result.begin(),
        result.end(),
        [](const Connection& left, const Connection& right) {
            return left.connection_id < right.connection_id;
        }
    );

    return result;
}

} // namespace automation_core
