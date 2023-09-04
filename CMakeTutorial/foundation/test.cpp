#include <iostream>

int main() {
#ifdef USE_MARCO
    std::cout << "Test for [option] " << std::endl;
#endif
    std::cout << "Finished! " << std::endl;
}