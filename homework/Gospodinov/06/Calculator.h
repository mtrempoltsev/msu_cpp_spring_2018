#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <stdexcept>
#include <cstring>
#include <sstream>

class Expression
{
	std::string token;
	std::vector<Expression> args;

	template<class T>
	static T cast(const std::string& str)
	{
		std::istringstream ss(str);
		T num;
		ss >> num;
		return num;
	}
public:
	Expression(std::string token) : token(token) {}
	Expression(std::string token, Expression a) : token(token), args{ a } {}
	Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {}

	template <class T>
	T evaluate()
	{
		switch (args.size())
		{
		case 2:
		{
			auto a = args[0].evaluate<T>();
			auto b = args[1].evaluate<T>();
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
			auto a = args[0].evaluate<T>();
			if (token == "-")
				return -a;
			throw std::runtime_error("Unknown unary operator");
		}
		case 0:
			return cast<T>(token);
		}
		throw std::runtime_error("Unknown expression type");
	}
};

template<class T>
class Calculator
{
	static int get_priority(const std::string& binary_op);
	std::string parse_token();
	Expression parse_simple_expression();
	Expression parse_binary_expression(int min_priority);
	Expression parse();
	const char* input;
public:
	Calculator(const char* input) : input(input) {}
	T run();
};

template<class T>
int Calculator<T>::get_priority(const std::string& binary_op)
{
	if (binary_op == "*" || binary_op == "/")
		return 2;
	if (binary_op == "+" || binary_op == "-")
		return 1;
	return 0;
}

template<class T>
std::string Calculator<T>::parse_token()
{
	while (std::isspace(*input))
		input++;

	if (std::isdigit(*input))
	{
		std::string number;
		while (std::isdigit(*input))
			number.push_back(*input++);
		return number;
	}

	static const std::string tokens[] = { "+", "-", "*", "/" };
	for (auto& t : tokens)
	{
		if (std::strncmp(input, t.c_str(), t.size()) == 0)
		{
			input += t.size();
			return t;
		}
	}
	return "";
}

template<class T>
Expression Calculator<T>::parse_simple_expression()
{
	auto token = parse_token();
	if (token.empty())
		throw std::runtime_error("Invalid input");

	if (std::isdigit(token[0]))
		return Expression(token);

	return Expression(token, parse_simple_expression());
}

template<class T>
Expression Calculator<T>::parse_binary_expression(int min_priority)
{
	auto left_expr = parse_simple_expression();

	while (true)
	{
		auto op = parse_token();
		auto priority = get_priority(op);
		if (priority <= min_priority)
		{
			input -= op.size();
			return left_expr;
		}

		auto right_expr = parse_binary_expression(priority);
		left_expr = Expression(op, left_expr, right_expr);
	}
}

template<class T>
Expression Calculator<T>::parse()
{
	return parse_binary_expression(0);
}

template <class T>
T Calculator<T>::run()
{
	return this->parse().template evaluate<T>();
}