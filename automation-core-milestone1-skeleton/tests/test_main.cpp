#include <iostream>
int run_frame_tests();
int main(){
 int f=run_frame_tests();
 if(f){std::cerr<<f<<" failures\n"; return 1;}
 std::cout<<"Tests passed\n";
 return 0;
}
