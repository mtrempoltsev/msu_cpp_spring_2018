#include <iostream>
#include "hw06.h"

constexpr int EXERCISE = 1;
constexpr int ARGNUM = 2;

int main(int argc, char **argv)
{
    try {
        if(argc != ARGNUM) throw std::invalid_argument("Wrong number of arguments");
        Calculator<int> calc(argv[EXERCISE]);
        std::cout << calc.calculate() << std::endl;
    } catch(...) {
        std::cout << "error" << std::endl;
        return 1;
    }
    return 0;
}
