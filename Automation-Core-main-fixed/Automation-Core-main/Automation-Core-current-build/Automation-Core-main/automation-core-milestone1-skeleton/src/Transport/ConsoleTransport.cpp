#include "automation_core/Transport/ConsoleTransport.h"

#include <iostream>
#include <string>

namespace automation_core {

std::optional<TransportPacket> ConsoleTransport::receive() {
    return std::nullopt;
}

bool ConsoleTransport::send(
    const std::string& connection_id,
    const std::string& payload
) {
    (void)connection_id;
    std::cout << payload;
    return true;
}

} // namespace automation_core
