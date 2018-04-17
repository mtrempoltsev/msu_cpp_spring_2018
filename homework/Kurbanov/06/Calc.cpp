#include <iostream>
#include <string.h>
#include <stdexcept>
#include <memory>
#include <math.h>
#include <assert.h>
#include <ctype.h>


enum class Operation
{
	NOP = 0, // just a value
	ADD, // +
	SUB, // -
	MUL, // *
	DIV, // /
	MOD, // %
	POW // ^
};


template<typename T>
class Expression
{
	T value = 0;
	T result;
	Operation op = Operation::NOP;
	std::shared_ptr<Expression> pLeft;
	std::shared_ptr<Expression> pRight;
	void SkipSpaces(std::string& expression)
	{
		size_t numSize = 0;
		while (numSize < expression.size() && (expression[numSize] == ' '))
			++numSize;
		expression = expression.substr(numSize);
	}
	std::shared_ptr<Expression> ParseAddSub(std::string &str)
	{
		std::shared_ptr<Expression> left = ParseMulDiv(str);
		while (true)
		{
			Operation op = Operation::NOP;
			std::string remainingStr = str;
			if (!ParseOperator(remainingStr, op) || (op != Operation::ADD && op != Operation::SUB))
				return left;
			switch (op)
			{
			case Operation::ADD:
			case Operation::SUB:
				break;
			default:
				return left;
			}
			str = remainingStr;
			std::shared_ptr<Expression> right = ParseMulDiv(str);
			std::shared_ptr<Expression> expr(new Expression);
			expr->pLeft = left;
			expr->pRight = right;
			expr->op = op;
			left = expr;
		}

		return left;
	}
	std::shared_ptr<Expression> ParseMulDiv(std::string &str)
	{
		std::shared_ptr<Expression> left = ParsePow(str);
		while (true)
		{
			Operation op = Operation::NOP;
			std::string remainingStr = str;
			if (!ParseOperator(remainingStr, op) || (op != Operation::MUL && op != Operation::DIV && op != Operation::MOD))
				return left;
			switch (op)
			{
			case Operation::MUL:
			case Operation::DIV:
			case Operation::MOD:
				break;
			default:
				return left;
			}
			str = remainingStr;
			std::shared_ptr<Expression> right = ParseMulDiv(str);
			std::shared_ptr<Expression> expr(new Expression);
			expr->pLeft = left;
			expr->pRight = right;
			expr->op = op;
			left = expr;
		}

		return left;
	}
	std::shared_ptr<Expression> ParsePow(std::string &str)
	{
		std::shared_ptr<Expression> left = ParseAtom(str);
		while (true)
		{
			Operation op = Operation::NOP;
			std::string remainingStr = str;
			if (!ParseOperator(remainingStr, op) || (op != Operation::POW))
				return left;
			switch (op)
			{
			case Operation::POW:
				break;
			default:
				return left;
			}
			str = remainingStr;
			std::shared_ptr<Expression> right = ParseAtom(str);
			std::shared_ptr<Expression> expr(new Expression);
			expr->pLeft = left;
			expr->pRight = right;
			expr->op = op;
			left = expr;
		}

		return left;
	}
	std::shared_ptr<Expression> ParseAtom(std::string &str)
	{
		std::shared_ptr<Expression> expr(new Expression);
		if (!ParseNum(str, expr->value))
		{
			throw std::runtime_error("");
		}
		return expr;
	}
	bool ParseNum(std::string &expression, double &result)
	{
		std::string remainingStr = expression;
		SkipSpaces(remainingStr);
		size_t numSize = 0;
		bool isnegative = false;
		if (remainingStr[0] == '-')
		{
			remainingStr = remainingStr.substr(1);
			SkipSpaces(remainingStr);
			isnegative = true;
		}
		if (remainingStr.size() > 0 && isdigit(remainingStr[0]))
		{
			while (numSize < remainingStr.size() && isdigit(remainingStr[numSize]))
				++numSize;
			result = atof(remainingStr.substr(0, numSize).c_str());
			if (isnegative) {
				result *= -1;
				op = Operation::ADD;
			}
			expression = remainingStr.substr(numSize);
			return true;
		}
		return false;
	}
	bool ParseNum(std::string &expression, int &result)
	{
		std::string remainingStr = expression;
		SkipSpaces(remainingStr);
		size_t numSize = 0;
		bool isnegative = false;
		if (remainingStr[0] == '-')
		{
			remainingStr = remainingStr.substr(1);
			SkipSpaces(remainingStr);
			isnegative = true;
		}
		SkipSpaces(remainingStr);
		if (remainingStr.size() > 0 && isdigit(remainingStr[0]))
		{
			while (numSize < remainingStr.size() && isdigit(remainingStr[numSize]))
				++numSize;
			result = atoi(remainingStr.substr(0, numSize).c_str());
			if (isnegative) {
				result *= -1;
				op = Operation::ADD;
			}
			expression = remainingStr.substr(numSize);
			return true;
		}
		return false;
	}
	bool ParseOperator(std::string &expression, Operation &op)
	{
		std::string remainingStr = expression;
		SkipSpaces(remainingStr);
		if (remainingStr.empty())
		{
			op = Operation::NOP;
			return false;
		}
		switch (remainingStr[0])
		{
		case '+':
			op = Operation::ADD; break;
		case '-':
			op = Operation::SUB; break;
		case '*':
			op = Operation::MUL; break;
		case '/':
			op = Operation::DIV; break;
		case '%':
			op = Operation::MOD; break;
		case '^':
			op = Operation::POW; break;
		default:
			op = Operation::NOP; break;
		}

		const bool succeed = (op != Operation::NOP);
		if (succeed)
			expression = remainingStr.substr(1);
		return succeed;
	}
	T CalculateExpression(std::shared_ptr<Expression> pExpr)
	{
		if (pExpr->op == Operation::NOP)
		{
			return pExpr->value;
		}
		assert(pExpr->pLeft);
		assert(pExpr->pRight);
		CalculateExpression(pExpr->pLeft);
		CalculateExpression(pExpr->pRight);
		switch (pExpr->op)
		{
		case Operation::ADD:
			pExpr->value = pExpr->pLeft->value + pExpr->pRight->value;
			break;
		case Operation::SUB:
			pExpr->value = pExpr->pLeft->value - pExpr->pRight->value;
			break;
		case Operation::MUL:
			pExpr->value = pExpr->pLeft->value * pExpr->pRight->value;
			break;
		case Operation::DIV:
			if (pExpr->pRight->value == 0) throw std::runtime_error("Divizion by zero");
			pExpr->value = pExpr->pLeft->value / pExpr->pRight->value;
			break;
		case Operation::MOD:
			pExpr->value = fmod(pExpr->pLeft->value, pExpr->pRight->value);
			break;
		case Operation::POW:
			pExpr->value = pow(pExpr->pLeft->value, pExpr->pRight->value);
			break;
		case Operation::NOP:
			assert(false);
			break;
		}

		return pExpr->value;
	}

public:
	Expression() {}
	Expression(const std::string &str)
	{
		std::string remainingStr = str;
		std::shared_ptr<Expression> pExpr = ParseAddSub(remainingStr);
		SkipSpaces(remainingStr);
		if (!remainingStr.empty())
		{
			const auto message = "Unexpected symbol at: " + remainingStr;
			throw std::runtime_error(message);
		}

		result = CalculateExpression(std::move(pExpr));
	}
	T show_result() { return result; }
	~Expression() {}
};



int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cout << "error";
		return 1;
	}
	std::string str = argv[1];
	try {
		Expression<int> a(str);
		std::cout << a.show_result() << std::endl;
	}
	catch (const std::runtime_error) {
		std::cout << "error";
		return 1;
	}
	return 0;
}
