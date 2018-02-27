#include <iostream>

#include "matrix.h"
#include "timer.h"

int main() {
    Matrix m(10000, 10000);
    Timer t;
    std::cout << "res by cols: " << m.SumByCols() << std::endl;
}
