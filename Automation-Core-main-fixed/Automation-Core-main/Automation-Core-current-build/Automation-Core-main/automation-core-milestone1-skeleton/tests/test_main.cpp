#include <iostream>
int run_frame_tests();
int run_parser_tests();
int run_validator_tests()+run_connection_manager_tests()+run_module_registry_tests()+run_router_tests();
int run_connection_manager_tests();
int run_module_registry_tests();
int run_router_tests();
int main(){
 int f=run_frame_tests()+run_parser_tests()+run_validator_tests()+run_connection_manager_tests()+run_module_registry_tests()+run_router_tests();
 if(f){std::cerr<<f<<" failures\n"; return 1;}
 std::cout<<"All tests passed\n"; return 0;
}
