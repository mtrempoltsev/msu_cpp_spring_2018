// Kononov Sergey BD-11

#include "calc.h"
#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "error\n";
		return 1;
	}
	
	Calculator <int> c;
	try {
		std::cout << c.calculate(argv[1]) << std::endl;
	}
	catch(CalcError& error) {
		std::cerr << "Error\n";
		return 1;
	}
	
	return 0;
}
