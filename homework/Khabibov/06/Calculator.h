#pragma once
#include<iostream>
#include<string>
#include <memory>

enum class Operation
{
	val,
	sum,
	substract,
	multiply,
	divide
};

void deleteSpaces(std::string& expressionInString)
{
	size_t i = 0;
	while (i < expressionInString.size())
	{
		if (expressionInString[i] == ' ')
		{
			expressionInString.erase(i, 1);
		}
		i++;
	}
}

template<class T>
class Expression
{
	T value_;
	Operation op_;
	Expression<T>* left_;
	Expression<T>* right_;
public:
	Expression<T>() : value_(0), op_(Operation::val), left_(nullptr), right_(nullptr) {};

	Expression<T>(const Expression& a) : value_(a.value_), op_(a.op_), left_(a.left_), right_(a.right_) {};

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

	static Expression<T> createExpression(const std::string& stringOfExpression)
	{
		std::string remainingStr = stringOfExpression;
		Expression<T> expr;
		expr.parseSumOrSubstract(remainingStr);
		if (!remainingStr.empty())
		{
			std::cerr << "error";
		}
		return expr;
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
			result = std::stoi(remainingStr.substr(flag, numSize));
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
			break;
		}

		const bool succeed = (op != Operation::val);
		if (succeed)
		{
			expressionInString = remainingStr.substr(1);
		}
		return succeed;
	}

	void parseAtom(std::string& expressionInString)
	{
		Expression<T> expr;
		if (!parseInt(expressionInString, expr.value_))
		{
			std::cerr << "error";
			throw std::invalid_argument("error");
		}
		*this = expr;
	}

	void parseSumOrSubstract(std::string& expressionInString)
	{
		Expression<T> left;
		left.parseMultiplyOrDivide(expressionInString);
		while (!expressionInString.empty())
		{
			Operation op = Operation::val;
			std::string remainingStr = expressionInString;
			if (!parseOperator(remainingStr, op) || (op != Operation::sum && op != Operation::substract))
			{
				*this = left;
				return;
			}
			expressionInString = remainingStr;

			Expression<T> right;
			try
			{
				right.parseMultiplyOrDivide(expressionInString);
			}
			catch (...)
			{
				throw;
			}

			try
			{
				this->left_ = &left;
				this->right_ = &right;
				this->op_ = op;
			}
			catch (...)
			{
				throw;
			}
		}
		return;
	}

	void parseMultiplyOrDivide(std::string& expressionInString)
	{
		Expression<T> left;
		left.parseAtom(expressionInString);
		while (!expressionInString.empty())
		{
			Operation op = Operation::val;
			std::string remainingStr = expressionInString;
			if (!parseOperator(remainingStr, op) || (op != Operation::multiply && op != Operation::divide))
			{
				*this = left;
				return;
			}
			expressionInString = remainingStr;

			Expression<T> right;
			try
			{
				right.parseAtom(expressionInString);
			}
			catch (...)
			{
				throw;
			}

			try
			{
				this->left_ = &left;
				this->right_ = &right;
				this->op_ = op;
			}
			catch (...)
			{
				throw;
			}
		}
		return;
	}
};

template<class T>
class Calculator
{
	std::string str_;
	std::unique_ptr<Expression<T>> expr_;
public:
	Calculator() : str_("0"), expr_(std::make_unique<Expression<T>>()) {};
	Calculator(std::string& s) : str_(s), expr_(std::make_unique<Expression<T>>()) {};
	T calculate()
	{
		*expr_ = Expression<T>::createExpression(str_);
		T result = expr_->calculateExpression();
		return result;
	};
};
