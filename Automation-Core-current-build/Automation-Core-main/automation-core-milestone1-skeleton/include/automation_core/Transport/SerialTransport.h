#pragma once

#include "automation_core/Transport/ITransport.h"

#include <string>

namespace automation_core {

class SerialTransport final : public ITransport {
public:
    explicit SerialTransport(std::string device_name);

    [[nodiscard]] std::optional<TransportPacket> receive() override;

    bool send(
        const std::string& connection_id,
        const std::string& payload
    ) override;

private:
    std::string device_name_;
};

} // namespace automation_core
