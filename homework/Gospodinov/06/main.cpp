#include "Parser.h"
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
		Parser p(argv[1]);
		auto result = p.parse().eval<int>();
		std::cout << result << std::endl;
	}
	catch (std::exception& expr) 
	{
		std::cerr << "error" << std::endl;
		//std::cerr << expr.what() << std::endl;
		return 1;
	}
	return 0;
}