#include "automation_core/Core/Core.h"
#include "automation_core/Transport/ConsoleTransport.h"

int main() {
    automation_core::ConsoleTransport transport;
    automation_core::Core core(transport);

    core.poll_once();

    return 0;
}
