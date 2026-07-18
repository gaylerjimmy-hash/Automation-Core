#include "automation_core/Core/Core.h"

namespace automation_core {

Core::Core(ITransport& transport)
    : transport_(transport),
      connections_(),
      frames_(),
      parser_(),
      validator_("1"),
      registry_(),
      responses_(),
      router_(validator_, registry_, responses_) {}

void Core::poll_once() {
    // TODO:
    // 1. Receive transport packet.
    // 2. Update connection state.
    // 3. Assemble and validate frame.
    // 4. Parse typed message.
    // 5. Route message.
    // 6. Serialize and send response.
}

} // namespace automation_core
