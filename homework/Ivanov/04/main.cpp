#include <iostream>
#include "matrix.h"

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet()
{
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    check(m[0][0] == 1);
    check(m[0][1] == 2);
    check(m[0][2] == 3);
    check(m[1][0] == 4);
    check(m[1][1] == 5);
    check(m[1][2] == 6);
    
    m[1][2] = 100; 
    
    check(m[1][2] == 100);
}

int
main()
{
	checkGetSet();
	Matrix m1(3, 3), m2(3, 3);
	m1[0][0] = 1; m2[0][0] = 1;
	m1[0][1] = -100; m2[0][1] = -100;
	if (m1 != m2) {
		std::cout << "error2" << std::endl;
	}
	std::vector<double> d1 = {100, 500, -1000};
	std::vector<double> d2 = {0.1, 1.5436, 5.6574};
	(m1 *= d1) *= d2;
	(m2 *= 0.4) *= -500;
	return 0;
}
