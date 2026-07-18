#pragma once
#include <string>
namespace automation_core{
enum class ValidationStatus{Valid,Rejected,VersionMismatch};
struct ValidationResult{
 ValidationStatus status{ValidationStatus::Rejected};
 std::string error_code;
 std::string detail;
 bool valid() const noexcept{return status==ValidationStatus::Valid;}
};
}
