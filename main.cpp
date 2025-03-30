#include <iostream>

extern "C" void hello() {
    std::cout << "Hello from shared C++ library!" << std::endl;
}