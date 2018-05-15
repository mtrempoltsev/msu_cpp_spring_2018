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
	Expression<T>* left_;
	Expression<T>* right_;
public:
	Expression<T>() : value_(0), op_(Operation::val), left_(nullptr), right_(nullptr)
	{
	};

	Expression<T>(const Expression& a) : value_(a.value_), op_(a.op_), left_(a.left_), right_(a.right_)
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

	void createExpression(const std::string& stringOfExpression)
	{
		std::string remainingStr = stringOfExpression;
		this->parseSumOrSubstract(remainingStr);
	}

	bool parseInt(std::string& expressionInString, T& result)
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
			try
			{
				result = std::stoi(remainingStr.substr(flag, numSize));
			}
			catch (...)
			{
				throw Error();
			}
			if (flag)
				result = -result;
			expressionInString = remainingStr.substr(numSize);
			return true;
		}
		return false;
	}

	bool parseOperator(std::string& expressionInString, Operation& op)
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

	void parseAtom(std::string& expressionInString)
	{
		Expression<T>* expr = new(Expression<T>);
		if (!parseInt(expressionInString, expr->value_))
			throw Error();
		*this = *expr;
	}

	void parseSumOrSubstract(std::string& expressionInString)
	{
		Expression<T>* left = new(Expression<T>);
		try
		{
			left->parseMultiplyOrDivide(expressionInString);
		}
		catch (const Error& error)
		{
			throw Error();
		}
		while (!expressionInString.empty())
		{
			Operation op = Operation::val;
			std::string remainingStr = expressionInString;
			if (!parseOperator(remainingStr, op))
				throw Error();
			if (op != Operation::sum && op != Operation::substract)
			{
				*this = *left;
				return;
			}
			expressionInString = remainingStr;

			Expression<T>* right = new(Expression<T>);
			try
			{
				right->parseMultiplyOrDivide(expressionInString);
			}
			catch (const Error& error)
			{
				throw Error();
			}

			Expression<T>* expr = new (Expression<T>);
			expr->left_ = left;
			expr->right_ = right;
			expr->op_ = op;
			left = expr;
		}
		*this = *left;
		return;
	}

	void parseMultiplyOrDivide(std::string& expressionInString)
	{
		Expression<T>* left = new(Expression<T>);
		left->parseAtom(expressionInString);
		while (!expressionInString.empty())
		{
			Operation op = Operation::val;
			std::string remainingStr = expressionInString;
			if (!parseOperator(remainingStr, op))
				throw Error();
			if (op != Operation::multiply && op != Operation::divide)
			{
				*this = *left;
				return;
			}
			expressionInString = remainingStr;

			Expression<T>* right = new(Expression<T>);
			try
			{
				right->parseAtom(expressionInString);
				if (op == Operation::divide && right->value_ == 0)
					throw Error();
			}
			catch (const Error& error)
			{
				throw Error();
			}

			Expression<T>* expr = new (Expression<T>);
			expr->left_ = left;
			expr->right_ = right;
			expr->op_ = op;
			left = expr;
		}
		*this = *left;
		return;
	}
};

template<class T>
class Calculator
{
	std::string str_;
	std::unique_ptr<Expression<T>> expr_;
public:
	Calculator() : str_("0"), expr_(std::make_unique<Expression<T>>())
	{
	};

	Calculator(std::string& s) : str_(s), expr_(std::make_unique<Expression<T>>())
	{
	};

	T calculate()
	{
		expr_->createExpression(str_);
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
