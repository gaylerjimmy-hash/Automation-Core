#include "automation_core/Transport/SerialTransport.h"

#include <utility>

namespace automation_core {

SerialTransport::SerialTransport(std::string device_name)
    : device_name_(std::move(device_name)) {}

std::optional<TransportPacket> SerialTransport::receive() {
    return std::nullopt;
}

bool SerialTransport::send(
    const std::string& connection_id,
    const std::string& payload
) {
    (void)connection_id;
    (void)payload;
    return false;
}

} // namespace automation_core
