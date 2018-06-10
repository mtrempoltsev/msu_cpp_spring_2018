#include <iostream>
#include <algorithm>
#include "CalcAlg.h"

int main(int argc, char *argv[]) {
	
	try {
		if (argc != 2) {
			throw std::runtime_error("error");
		}

		Calculator<int> calc;
		std::cout << calc.calculate(argv[1]) << std::endl;
	}
	catch (std::runtime_error err) {
		std::cout << err.what() << std::endl;

		return  -1;
	}
	catch (...) {
		std::cout << "error" << std::endl;

		return -2;
	}
	

	return 0;
}