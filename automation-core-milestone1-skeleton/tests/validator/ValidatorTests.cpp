#include "automation_core/Protocol/Validator.h"
using namespace automation_core;
int run_validator_tests(){
 int f=0;
 HelloMessage h{"1","Scale","scale01","1.0.0","1","81A9C5D2"};
 Message m{h};
 Validator v("1");
 if(!v.validate(m).valid()) ++f;
 h.protocol_version="2"; if(v.validate(Message{h}).status!=ValidationStatus::VersionMismatch) ++f;
 h.protocol_version="1"; h.session_id="BAD"; if(v.validate(Message{h}).valid()) ++f;
 return f;
}
