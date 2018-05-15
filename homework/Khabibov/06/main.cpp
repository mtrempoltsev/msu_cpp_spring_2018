#include<iostream>
#include<string>
#include <memory>
#include <algorithm>

class Error
{
};

enum class Operation
{
	val,
	sum,
	substract,
	multiply,
	divide
};

template<class T>
class Expression
{
	T value_;
	Operation op_;
	std::unique_ptr<Expression<T>> left_;
	std::unique_ptr<Expression<T>> right_;
public:
	Expression<T>() : value_(0), op_(Operation::val), left_(nullptr), right_(nullptr)
	{
	};

	T calculateExpression()
	{
		if (this->op_ == Operation::val)
			return this->value_;
		left_->calculateExpression();
		right_->calculateExpression();
		switch (this->op_)
		{
		case Operation::sum:
			this->value_ = this->left_->value_ + this->right_->value_;
			break;
		case Operation::substract:
			this->value_ = this->left_->value_ - this->right_->value_;
			break;
		case Operation::multiply:
			this->value_ = this->left_->value_ * this->right_->value_;
			break;
		case Operation::divide:
			this->value_ = this->left_->value_ / this->right_->value_;
			break;
		}
		return this->value_;
	}

	static std::unique_ptr<Expression<T>> createExpression(const std::string& stringOfExpression)
	{
		std::string remainingStr = stringOfExpression;
		return std::move(parseSumOrSubstract(remainingStr));
	}

	static bool parseInt(std::string& expressionInString, T& result)
	{
		std::string remainingStr = expressionInString;
		size_t numSize = 0;
		size_t flag = 0;
		if (remainingStr[0] == '-')
		{
			numSize++;
			flag = 1;
		}
		if ((remainingStr.size() > 0) && (isdigit(remainingStr[flag])))
		{
			while ((numSize < remainingStr.size()) && (isdigit(remainingStr[numSize])))
			{
				numSize++;
			}
			result = std::stoi(remainingStr.substr(flag, numSize));
			if (flag)
				result = -result;
			expressionInString = remainingStr.substr(numSize);
			return true;
		}
		return false;
	}

	static bool parseOperator(std::string& expressionInString, Operation& op)
	{
		std::string remainingStr = expressionInString;

		if (remainingStr.empty())
		{
			op = Operation::val;
			return false;
		}

		switch (remainingStr[0])
		{
		case '+':
			op = Operation::sum;
			break;
		case '-':
			op = Operation::substract;
			break;
		case '*':
			op = Operation::multiply;
			break;
		case '/':
			op = Operation::divide;
			break;
		default:
			op = Operation::val;
			throw Error();
			break;
		}

		bool succeed = (op != Operation::val);
		if (succeed)
		{
			expressionInString = remainingStr.substr(1);
		}
		return succeed;
	}

	static std::unique_ptr<Expression<T>> parseAtom(std::string& expressionInString)
	{
		std::unique_ptr<Expression<T>> expr = std::make_unique<Expression<T>>();
		if (!parseInt(expressionInString, expr->value_))
			throw Error();
		return std::move(expr);
	}

	static std::unique_ptr<Expression<T>> parseSumOrSubstract(std::string& expressionInString)
	{
		std::unique_ptr<Expression<T>> left = parseMultiplyOrDivide(expressionInString);
		while (!expressionInString.empty())
		{
			Operation op = Operation::val;
			std::string remainingStr = expressionInString;
			if (!parseOperator(remainingStr, op))
				throw Error();
			if (op != Operation::sum && op != Operation::substract)
			{
				return std::move(left);
			}
			expressionInString = remainingStr;

			std::unique_ptr<Expression<T>> right = parseMultiplyOrDivide(expressionInString);

			std::unique_ptr<Expression<T>> expr = std::make_unique<Expression<T>>();
			expr->left_ = std::move(left);
			expr->right_ = std::move(right);
			expr->op_ = op;
			left = std::move(expr);
		}
		return std::move(left);
	}

	static std::unique_ptr<Expression<T>> parseMultiplyOrDivide(std::string& expressionInString)
	{
		std::unique_ptr<Expression<T>> left = parseAtom(expressionInString);
		while (!expressionInString.empty())
		{
			Operation op = Operation::val;
			std::string remainingStr = expressionInString;
			if (!parseOperator(remainingStr, op))
				throw Error();
			if (op != Operation::multiply && op != Operation::divide)
			{
				return std::move(left);
			}
			expressionInString = remainingStr;

			std::unique_ptr<Expression<T>> right = parseAtom(expressionInString);
			if (op == Operation::divide && right->value_ == 0)
				throw Error();

			std::unique_ptr<Expression<T>> expr = std::make_unique<Expression<T>>();
			expr->left_ = std::move(left);
			expr->right_ = std::move(right);
			expr->op_ = op;
			left = std::move(expr);
		}
		return std::move(left);
	}
};

template<class T>
class Calculator
{
	std::string str_;
	std::unique_ptr<Expression<T>> expr_;
public:
	Calculator() : str_("0")
	{
	};

	Calculator(std::string& s) : str_(s)
	{
	};

	T calculate()
	{
		expr_ = std::move(Expression<T>::createExpression(str_));
		T result = expr_->calculateExpression();
		return result;
	};
};

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
		expressionInString.erase(std::remove(expressionInString.begin(), expressionInString.end(), ' '), expressionInString.end());
		Calculator<int> a(expressionInString);
		std::cout << a.calculate() << std::endl;
	}
	catch (const Error& error)
	{
		std::cerr << "error" << std::endl;
		return 1;
	}
	return 0;
}
