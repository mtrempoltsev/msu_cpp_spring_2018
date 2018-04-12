#include "Calculator.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "error" << std::endl;
		return 1;
	}
	try 
	{
		Calculator<int> calc(argv[1]);
		std::cout << calc.run() << std::endl;
	}
	catch (std::exception& expr) 
	{
		std::cerr << "error" << std::endl;
		//std::cerr << expr.what() << std::endl;
		return 1;
	}
	return 0;
}