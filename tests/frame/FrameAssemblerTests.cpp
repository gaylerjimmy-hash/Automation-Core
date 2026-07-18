#include "automation_core/Frame/FrameAssembler.h"
using namespace automation_core;
int run_frame_tests(){
 int f=0;
 FrameAssembler a(64);
 if(!a.assemble("c","HELLO\nEND\n").ok()) ++f;
 if(a.assemble("","HELLO\nEND\n").ok()) ++f;
 if(a.assemble("c","HELLO").ok()) ++f;
 return f;
}
