#pragma once

#include "automation_core/Transport/ITransport.h"

namespace automation_core {

class ConsoleTransport final : public ITransport {
public:
    [[nodiscard]] std::optional<TransportPacket> receive() override;

    bool send(
        const std::string& connection_id,
        const std::string& payload
    ) override;
};

} // namespace automation_core
