#pragma once

#include "automation_core/Connection/ConnectionManager.h"
#include "automation_core/Frame/FrameAssembler.h"
#include "automation_core/Protocol/Parser.h"
#include "automation_core/Protocol/Validator.h"
#include "automation_core/Registry/ModuleRegistry.h"
#include "automation_core/Response/ResponseBuilder.h"
#include "automation_core/Router/MessageRouter.h"
#include "automation_core/Transport/ITransport.h"

namespace automation_core {

class Core {
public:
    explicit Core(ITransport& transport);

    void poll_once();

private:
    ITransport& transport_;
    ConnectionManager connections_;
    FrameAssembler frames_;
    Parser parser_;
    Validator validator_;
    ModuleRegistry registry_;
    ResponseBuilder responses_;
    MessageRouter router_;
};

} // namespace automation_core
