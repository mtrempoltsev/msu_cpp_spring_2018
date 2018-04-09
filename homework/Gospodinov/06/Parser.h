#pragma once

#include <string>
#include <vector>
#include <stdexcept>

struct Expression
{
	Expression(std::string token) : token(token) {}
	Expression(std::string token, Expression a) : token(token), args{ a } {}
	Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {}

	template<class T>
	T eval();

	std::string token;
	std::vector<Expression> args;
};

class Parser
{
public:
	Parser(const char* input) : input(input) {}
	Expression parse();
private:
	std::string parse_token();
	Expression parse_simple_expression();
	Expression parse_binary_expression(int min_priority);

	const char* input;
};

template<class T>
T Expression::eval()
{
	switch (args.size())
	{
	case 2:
	{
		auto a = args[0].eval<T>();
		auto b = args[1].eval<T>();
		switch (token[0])
		{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
		{
			if (b == 0)
				throw std::runtime_error("Division by zero");
			return a / b;
		}
		}
	}
	case 1:
	{
		auto a = args[0].eval<T>();
		if (token == "-")
			return -a;
		throw std::runtime_error("Unknown unary operator");
	}
	case 0:
		return atoi(token.c_str());
	}
	throw std::runtime_error("Unknown expression type");
}