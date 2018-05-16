#include <iostream>
#include "Calc.h"

int main(int argc, char *argv[])
{
    try {
        if (argc != 2) {
            throw std::runtime_error("error");
        }

        Calc<int> object;
        std::cout << object.compute(argv[1]) << std::endl;
    } catch(std::runtime_error err) {
        std::cout << err.what() << std::endl;

        return  1;
    } catch(...) {
        std::cout << "error" << std::endl;

        return 1;
    }

    return 0;
}