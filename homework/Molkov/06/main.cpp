#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <stdexcept>

struct Expression {
	Expression(std::string token) : token(token) {}
	Expression(std::string token, Expression a) : token(token), args{ a } {}
	Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {}
	std::string token;
	std::vector<Expression> args;
};

//template <class T>
class Parser {
public:
	Parser(const char* input) : input(input) {}
	Expression parse(int min_priority);
private:
	std::string parse_token();
	Expression parse_simple_expression();
	const char* input;
};

std::string Parser::parse_token() {
	while (std::isspace(*input)) ++input;

	if (std::isdigit(*input)) {
		std::string number;
		while (std::isdigit(*input)) number.push_back(*input++);
		return number;
	}
	
	switch (*input) {
	case('+'):
		input++;
		return "+";
	case('-'):
		input++;
		return "-";
	case('*'):
		input++;
		return "*";
	case('/'):
		input++;
		return "/";

	}
	
	return "";
}

Expression Parser::parse_simple_expression() {
	auto token = parse_token();
	if (token.empty()) throw std::runtime_error("Invalid input");

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

Expression Parser::parse(int min_priority) {
	auto left_expr = parse_simple_expression();

	for (;;) {
		auto op = parse_token();
		int priority = get_priority(op);
		if (priority <= min_priority) {
			input -= op.size();
			return left_expr;
		}
		auto right_expr = parse(priority);
		left_expr = Expression(op, left_expr, right_expr);
	}
}


template <class T>
class Calc {
public:
	Parser p;
	Calc(char* argv) : p(argv) {}
	T eval(const Expression& expr) {
		switch (expr.args.size()) {
		case 2: {
			T a = eval(expr.args[0]);
			T b = eval(expr.args[1]);
			if (expr.token == "+") return a + b;
			if (expr.token == "-") return a - b;
			if (expr.token == "*") return a * b;
			if (expr.token == "/") {
				if (b == 0) throw std::runtime_error("Divizion by zero");
				return a / b;
			}

			throw std::runtime_error("Unknown binary operator");
		}

		case 1: {
			auto a = eval(expr.args[0]);
			if (expr.token == "+") return +a;
			if (expr.token == "-") return -a;
			throw std::runtime_error("Unknown unary operator");
		}

		case 0:
			return atoi(expr.token.c_str());
		}

		throw std::runtime_error("Unknown expression type");
	}
};


int main(int argc, char* argv[]) {

	if (argc != 2) {
		std::cout << "error";
		return 1;
	}
	try {
		Calc<int> calc(argv[1]);
		Expression e = calc.p.parse(0);
		std::cout << calc.eval(e);
	}
	catch (const std::runtime_error) {
		std::cout << "error";
		return 1;
	}

	return 0;
}