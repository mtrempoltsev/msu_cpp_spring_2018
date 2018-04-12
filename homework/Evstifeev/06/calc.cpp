#include <iostream>
#include "calc.hpp"
#include "exception.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong number of input" << std::endl;
        return -255;
    }
    Calculator<int> calc{std::string(argv[1])};
    try {
        int expression = calc.expression();
        std::cout << "=" << expression << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -255;
    }
}
