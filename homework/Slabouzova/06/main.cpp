#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>


class CalculatorError
{
    std::string message_;
public:
    CalculatorError(const std::string& message):
    	message_(message)
    { }
    const std::string& getMessage() const
    {
    	return message_;
    }
};



template <class T>
class Calculator
{
public:
	T runCalculator(const std::string& expression)
	{
		// remove spaces from expression
		std::string str = expression;
		str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
		return calculate(str);
	}

private:
	T calculate (const std::string& str)
	{
		// + OR (binary) -  		
	    size_t found = str.find_last_of("+-");
	    while (found != std::string::npos and found != 0) {
	    	if (str.at(found) == '+')    		
	    		return calculate(str.substr(0, found)) + calculate(str.substr(found+1));
	    	if (not isUnary(str, found))
	    		return calculate(str.substr(0, found)) - calculate(str.substr(found+1));
	    	found = str.find_last_of("+-", found-1);
	    }

	    // * OR /
	    found = str.find_last_of("*/");
	    if (found != std::string::npos) {
	    	T val1 = calculate(str.substr(0, found));
	    	T val2 = calculate(str.substr(found+1));
	    	if (str.at(found) == '*')    		
	    		return val1 * val2;
	    	else if (val2 == 0) // check if divided by 0
	    		throw CalculatorError("Divide by zero");
	    	else
	    		return val1 / val2;
	    }
	    // getting value and checking value
	    std::istringstream iss (str);
	    T Value;
	    iss >> Value;
		if (str.compare(std::to_string(Value)) != 0)
			throw CalculatorError("Not vaid value");
		return Value;
	}

	bool isUnary(const std::string& str, int pos)
	{
		for(int i = pos - 1; i >= 0; i--) {
			switch(str.at(i)) {
			    case ' ': 
			    	continue;
			    case '+':
			    case '-':
			    case '/':
			    case '*': 
			    	return true;
			    default:
			    	return false;
			}
		}
		return true;
	}
};

int main(int argc, char *argv[])
{
	try {
		if (argc != 2)
			throw CalculatorError("Not valid argv");
		Calculator<int> calc;
		std::cout << calc.runCalculator(argv[1]) << std::endl;
	} 
	catch (const CalculatorError& calc_error) {
		std::cout << "error" << std::endl;
		return 1;
	}
	return 0;
}