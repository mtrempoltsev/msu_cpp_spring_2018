#include <iostream>
#include "calc.h"

int main(int argc, char * argv[]) {
    if(argc != 2) {
        std::cerr << "error" << std::endl;
        return 1;
    } else {
        try {
            calc<int> ctor{std::string(argv[1])};
            int ans = ctor.eval();
            std::cout << ans << std::endl;
        } catch(calc_exception & e) {
            std::cerr << "error" << std::endl;
            return 1;
        }
    }
    return 0;
}