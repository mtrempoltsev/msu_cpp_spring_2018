#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>

struct Expression
{
	Expression(std::string token)
  : token(token) {}
	Expression(std::string token, Expression a)
  : token(token)
  , args{ a } {}
	Expression(std::string token, Expression a, Expression b)
  : token(token)
  , args{ a, b } {}

	std::string token;
	std::vector<Expression> args;
};

template<typename T>
T cast(const std::string& str);

template<> int cast<int>(const std::string& str)
{
	return std::stoi(str);
}

template <typename T>
class Calc
{
public:
	Calc(const char* input) : input(input) {}
	Expression parse();
  T evaluate(const Expression& e);
private:
	std::string parse_token();
	Expression parse_simple_expression();
	Expression parse_binary_expression(int min_priority);

	const char* input;
};

template<typename T>
std::string Calc<T>::parse_token()
{
	while (std::isspace(*input))
		++input;

	if (std::isdigit(*input))
	{
		std::string number;
		while (std::isdigit(*input) || *input == '.') number.push_back(*input++);
		return number;
	}

	static const std::string tokens[] = { "+", "-", "*", "/"};
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

template<typename T>
Expression Calc<T>::parse_simple_expression() {
	auto token = parse_token();
	if (token.empty())
		throw std::runtime_error("Invalid input");

	if (std::isdigit(token[0]))
		return Expression(token);

	return Expression(token, parse_simple_expression());
}

int get_priority(const std::string& binary_op) {
	if (binary_op == "+") return 1;
	if (binary_op == "-") return 1;
	if (binary_op == "*") return 2;
	if (binary_op == "/") return 2;
	return 0;
}

template<typename T>
Expression Calc<T>::parse_binary_expression(int min_priority)
{
	auto left_expr = parse_simple_expression();

	for (;;)
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

template<typename T>
Expression Calc<T>::parse()
{
	return parse_binary_expression(0);
}

template <typename T>
T Calc<T>::evaluate(const Expression& e)
{
	switch (e.args.size())
	{
	case 2:
	{
		auto a = evaluate(e.args[0]);
		auto b = evaluate(e.args[1]);
		if (e.token == "+") return a + b;
		if (e.token == "-") return a - b;
		if (e.token == "*") return a * b;
		if (e.token == "/")
		{
			if (b == 0)
				throw std::runtime_error("Division by zero");
			return a / b;
		}
		throw std::runtime_error("Unknown binary operator");
	}

	case 1:
	{
		auto a = evaluate(e.args[0]);
		if (e.token == "+") return +a;
		if (e.token == "-") return -a;
		throw std::runtime_error("Unknown unary operator");
	}

	case 0:
		return cast<T>(e.token);
	}

	throw std::runtime_error("Unknown expression type");
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "error" << std::endl;
		return 1;
	}
	try
	{
		Calc<int> calc(argv[1]);
		std::cout <<  calc.evaluate(calc.parse()) << std::endl;
	}
	catch (std::exception& expr)
	{
		std::cerr << "error" << std::endl;
			return 1;
	}
	return 0;
}
