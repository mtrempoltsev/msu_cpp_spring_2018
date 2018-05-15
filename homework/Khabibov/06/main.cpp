#include "Calculator.h"
#include<iostream>
#include<string>


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "error" << std::endl;
		return 1;
	}
	try
	{
		std::string expressionInString(argv[1]);
		deleteSpaces(expressionInString);
		Calculator<int> a(expressionInString);
		std::cout << a.calculate() << std::endl;
	}
	catch (const Error& error)
	{
		std::cerr << "error" << std::endl;
	}
	system("pause");
}
