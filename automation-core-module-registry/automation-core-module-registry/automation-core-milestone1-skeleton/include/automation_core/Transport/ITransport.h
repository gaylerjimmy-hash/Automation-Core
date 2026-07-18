#pragma once

#include <optional>
#include <string>

namespace automation_core {

struct TransportPacket {
    std::string connection_id;
    std::string payload;
};

class ITransport {
public:
    virtual ~ITransport() = default;

    [[nodiscard]] virtual std::optional<TransportPacket> receive() = 0;
    virtual bool send(
        const std::string& connection_id,
        const std::string& payload
    ) = 0;
};

} // namespace automation_core
