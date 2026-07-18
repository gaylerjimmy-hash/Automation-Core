#include <iostream>
int run_frame_tests();
int run_parser_tests();
int run_validator_tests();
int main(){
 int f=run_frame_tests()+run_parser_tests()+run_validator_tests();
 if(f){std::cerr<<f<<" failures\n"; return 1;}
 std::cout<<"All tests passed\n"; return 0;
}
