#include "automation_core/Protocol/Validator.h"
#include <regex>
using namespace automation_core;
Validator::Validator(std::string v):supported_protocol_version_(std::move(v)){}
ValidationResult Validator::validate(const Message& m) const{
 auto h=std::get_if<HelloMessage>(&m.payload);
 if(!h) return {ValidationStatus::Rejected,"UNSUPPORTED","Only HELLO supported"};
 if(h->protocol_version!=supported_protocol_version_)
   return {ValidationStatus::VersionMismatch,"PROTO_VERSION","Unsupported protocol"};
 auto hex8=std::regex("^[A-Fa-f0-9]{8}$");
 auto id=std::regex("^[A-Za-z][A-Za-z0-9_-]*$");
 auto fw=std::regex(R"(^\d+\.\d+\.\d+$)");
 auto msg=std::regex("^[A-Za-z0-9_-]+$");
 if(!std::regex_match(h->session_id,hex8)) return {ValidationStatus::Rejected,"SESSION","Invalid session"};
 if(!std::regex_match(h->module_id,id)) return {ValidationStatus::Rejected,"MODULE_ID","Invalid module id"};
 if(!std::regex_match(h->firmware_version,fw)) return {ValidationStatus::Rejected,"FW","Invalid firmware"};
 if(!std::regex_match(h->message_id,msg)) return {ValidationStatus::Rejected,"MSG","Invalid message id"};
 return {ValidationStatus::Valid,"",""};
}
