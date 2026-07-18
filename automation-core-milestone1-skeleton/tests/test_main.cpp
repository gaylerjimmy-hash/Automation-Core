#include <cstdlib>
#include <iostream>

int run_frame_tests();
int run_parser_tests();

int main() {
    int failures = 0;

    failures += run_frame_tests();
    failures += run_parser_tests();

    if (failures != 0) {
        std::cerr << failures << " test(s) failed.\n";
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed.\n";
    return EXIT_SUCCESS;
}
