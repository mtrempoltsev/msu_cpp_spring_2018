#include<iostream>

namespace options
{	
	constexpr int base = 10000;
	constexpr int numberOfDigitsInBase = 4;
}

class BigInt
{
	int sign_;
	int* bigNumber_;
	size_t size_;
	BigInt(bool q, size_t size, int a = 0) : sign_(1), size_(size)
	{
		bigNumber_ = (int*)malloc(size * sizeof(int));
		for (size_t i = 0; i < size_; i++)
			bigNumber_[i] = 0;
	}
public:
	BigInt() : sign_(1), bigNumber_((int*)malloc(sizeof(int))), size_(1)
	{
		bigNumber_[0] = 0;
	}

	BigInt(int64_t a)
	{
		if (a >= 0)
			sign_ = 1;
		else
		{
			sign_ = -1;
			a = a * (-1);
		}
		int buf = a % options::base;
		bigNumber_ = (int*)malloc(sizeof(int));
		bigNumber_[0] = buf;
		a -= buf;
		a /= options::base;
		size_ = 1;
		while (a != 0)
		{
			buf = a % options::base;
			bigNumber_ = (int*)realloc(bigNumber_, sizeof(int) * (size_ + 1));
			bigNumber_[size_] = buf;
			a -= buf;
			a /= options::base;
			size_++;
		}
	}

	~BigInt()
	{
		free(bigNumber_);
	}

	BigInt(const BigInt& a) : sign_(a.sign_), size_(a.size_)
	{
		bigNumber_ = (int*)malloc(size_ * sizeof(int));
		for (size_t i = 0; i < size_; i++)
			bigNumber_[i] = a.bigNumber_[i];
	}

	BigInt& operator=(const BigInt& a)
	{
		if (this == &a)
			return *this;
		size_ = a.size_;
		sign_ = a.sign_;
		free(bigNumber_);
		bigNumber_ = (int*)malloc(size_ * sizeof(int));
		for (size_t i = 0; i < size_; i++)
			bigNumber_[i] = a.bigNumber_[i];
		return *this;
	}

	BigInt(BigInt &&a) : sign_(a.sign_), bigNumber_(a.bigNumber_), size_(a.size_)
	{
		a.bigNumber_ = nullptr;
	}

	BigInt& operator=(BigInt &&a)
	{
		if (this == &a)
			return *this;
		size_ = a.size_;
		sign_ = a.sign_;
		free(bigNumber_);
		bigNumber_ = a.bigNumber_;
		a.bigNumber_ = nullptr;
		return *this;
	}

	bool operator==(const BigInt& b) const
	{
		if ((*this).sign_ != b.sign_)
			return false;
		if ((*this).size_ != b.size_)
			return false;
		for (size_t i = 0; i < b.size_; i++)
			if ((*this).bigNumber_[i] == b.bigNumber_[i])
				continue;
			else
				return false;
		return true;
	}

	bool operator!=(const BigInt& b) const
	{
		if (*this == b)
			return false;
		else
			return true;
	}

	bool operator<(const BigInt& b) const
	{
		if ((*this).sign_ < b.sign_)
			return true;
		if ((*this).sign_ > b.sign_)
			return false;
		if ((((*this).size_ < b.size_) && (b.sign_ == 1)) || (((*this).size_ > b.size_) && (b.sign_ == -1)))
			return true;
		if ((((*this).size_ > b.size_) && (b.sign_ == 1)) || (((*this).size_ < b.size_) && (b.sign_ == -1)))
			return false;
		if (b.sign_ == 1)
		{
			for (size_t i = b.size_ - 1; ((i < b.size_) && (i >= 0)); i--)
			{
				if ((*this).bigNumber_[i] < b.bigNumber_[i])
					return true;
				if ((*this).bigNumber_[i] == b.bigNumber_[i])
					continue;
				else
					return false;
			}
		}
		else
		{
			for (size_t i = b.size_ - 1; ((i < b.size_) && (i >= 0)); i--)
			{
				if ((*this).bigNumber_[i] > b.bigNumber_[i])
					return true;
				if ((*this).bigNumber_[i] == b.bigNumber_[i])
					continue;
				else
					return false;
			}
		}
	}

	bool operator>(const BigInt& b) const
	{
		return !((*this) < b) && !((*this) == b);
	}

	bool operator<=(const BigInt& b) const
	{
		return !((*this) > b);
	}

	bool operator>=(const BigInt& b) const
	{
		return !((*this) < b);
	}

	BigInt abs() const
	{
		BigInt result = (*this);
		result.sign_ = 1;
		return result;
	}

	BigInt operator+(const BigInt& b) const
	{
		BigInt result;
		if ((*this).sign_ * b.sign_ == -1)
		{
			if ((*this).abs() > b.abs())
			{
				result = (*this).abs() - b.abs();
				result.sign_ = (*this).sign_;
				return result;
			}
			if ((*this).abs() == b.abs())
			{
				return result;
			}
			else
			{
				result = b.abs() - (*this).abs();
				result.sign_ = b.sign_;
				return result;
			}
		}
		if ((*this).size_ >= b.size_)
			result = *this;
		else
			result = b;
		int toNextDigit = 0;
		size_t i = 0;
		for (i; i < std::min((*this).size_, b.size_); i++)
		{
			int buf = (*this).bigNumber_[i] + b.bigNumber_[i] + toNextDigit;
			toNextDigit = buf / options::base;
			result.bigNumber_[i] = buf % options::base;
		}
		if (toNextDigit == 1)
			if ((*this).size_ == b.size_)
			{
				result.size_ += 1;
				result.bigNumber_ = (int*)realloc(bigNumber_, sizeof(int));
				result.bigNumber_[result.size_ - 1] = 1;
			}
			else
				result.bigNumber_[i] += toNextDigit;
		return result;
	}

	BigInt operator-()
	{
		if ((size_ == 1) && (bigNumber_[0] == 0))
			return *this;
		(*this).sign_ *= -1;
		return *this;
	}

	BigInt operator-(const BigInt& b) const
	{
		BigInt result;
		if ((*this).sign_ * b.sign_ == -1)
		{
			result = (*this).abs() + b.abs();
			result.sign_ = (*this).sign_;
			return result;
		}
		BigInt bufBigInt;
		if ((*this).abs() == b.abs())
		{
			return result;
		}
		if ((*this).abs() > b.abs())
		{
			result = (*this);
			bufBigInt = b;
		}
		else
		{
			result = b;
			result.sign_ = b.sign_ * -1;
			bufBigInt = (*this);
		}
		int toNextDigit = 0;
		size_t i = 0;
		for (i; i < bufBigInt.size_; i++)
		{
			int buf = result.bigNumber_[i] - bufBigInt.bigNumber_[i] + toNextDigit;
			if (buf < 0)
			{
				result.bigNumber_[i] = options::base + buf;
				int debug = buf - options::base;
				toNextDigit = debug / options::base;
			}
			else
				result.bigNumber_[i] = buf;
		}
		i = result.size_ - 1;
		while (result.size_ > 0)
		{
			if (result.bigNumber_[i] == 0)
				result.size_--;
			else
				break;
			i--;
		}
		if (result.size_ == 0)
		{
			result.size_ = 1;
			return result;
		}
		result.bigNumber_ = (int*)realloc(result.bigNumber_, result.size_ * sizeof(int));
		return result;
	}

	BigInt operator*(const BigInt& b) const
	{
		if ((((*this).size_ == 1) && ((*this).bigNumber_[0] == 0)) || ((b.size_ == 1) && (b.bigNumber_[0] == 0)))
			return 0;
		BigInt result(true, (*this).size_ * b.size_ + 1, 0);
		for (size_t i = 0; i < b.size_; i++)
		{
			size_t j = 0;
			int toNextDigit = 0;
			for (; j < (*this).size_; j++)
			{
				result.bigNumber_[j + i] += toNextDigit;
				result.bigNumber_[j + i] += b.bigNumber_[i] * (*this).bigNumber_[j];
				toNextDigit = result.bigNumber_[j + i] / options::base;
				result.bigNumber_[j + i] %= options::base;
			}
			result.bigNumber_[j + i] += toNextDigit;
		}
		result.sign_ = (*this).sign_ * b.sign_;
		size_t i = result.size_ - 1;
		while (result.size_ > 0)
		{
			if (result.bigNumber_[i] == 0)
				result.size_--;
			else
				break;
			i--;
		}
		result.bigNumber_ = (int*)realloc(result.bigNumber_, result.size_ * sizeof(int));
		return result;
	}

	BigInt operator*(int a) const
	{
		BigInt buf(true, 1, 0);
		buf.bigNumber_[0] = a;
		return (*this) * buf;
	}

	BigInt operator/(const BigInt &b) const
	{
		BigInt result(true, (*this).size_, 0);
		BigInt curValue(true, 1, 0);
		for (size_t i = (*this).size_ - 1; ((i < (*this).size_) && (i >= 0)); i--)
		{
			curValue = curValue * options::base;
			curValue.bigNumber_[0] = (*this).bigNumber_[i];
			int x = 0;
			int l = 0, r = options::base;
			while (l <= r)
			{
				int m = (l + r) >> 1;
				BigInt cur = b.abs() * m;
				if (cur <= curValue)
				{
					x = m;
					l = m + 1;
				}
				else
					r = m - 1;
			}
			result.bigNumber_[i] = x;
			curValue = curValue - b.abs() * x;
		}
		size_t i = result.size_ - 1;
		while (i > 0)
		{
			if (result.bigNumber_[i] == 0)
				result.size_--;
			else
				break;
			i--;
		}
		result.bigNumber_ = (int*)realloc(result.bigNumber_, result.size_ * sizeof(int));
		if ((result.size_ == 1) && (result.bigNumber_[0] == 0))
			return 0;
		result.sign_ = (*this).sign_ * b.sign_;
		return result;
	}

	friend std::istream& operator>>(std::istream& in, BigInt& a)
	{
		char ch;
		char* stringOfNumber = new char[1024 * 1024];
		in >> ch;
		size_t i = 0;
		size_t bufNumberOfDigitsInBase = options::numberOfDigitsInBase;
		int buf = 0;
		if (ch == '-')
			a.sign_ = -1;
		else
		{
			a.sign_ = 1;
			i++;
			stringOfNumber[0] = ch;
		}
		in >> ch;
		while (ch != 't')
		{
			stringOfNumber[i] = ch;
			i++;
			in >> ch;
		}
		size_t sizeOfBigNumber = i / options::numberOfDigitsInBase;
		bool flag = false;
		if (i % options::numberOfDigitsInBase != 0)
		{
			a.size_ = sizeOfBigNumber + 1;
			a.bigNumber_ = new int[a.size_];
			flag = true;
		}
		else
		{
			a.size_ = sizeOfBigNumber;
			a.bigNumber_ = new int[a.size_];
		}
		for (size_t j = 0; j < sizeOfBigNumber; j++)
		{
			char bufString[options::numberOfDigitsInBase];
			for (size_t k = 0; k < options::numberOfDigitsInBase; k++)
			{
				char nBuf = stringOfNumber[i - options::numberOfDigitsInBase * (j + 1) + k];
				bufString[k] = nBuf;
			}
			a.bigNumber_[j] = atoi(bufString);
		}
		if (flag == true)
		{
			size_t buff = i % options::numberOfDigitsInBase;
			char* bufString = new char[buff + 1];
			for (size_t k = 0; k < buff; k++)
				bufString[k] = stringOfNumber[k];
			bufString[buff + 1] = '\0';
			a.bigNumber_[a.size_ - 1] = atoi(bufString);
		}
		return in;
	}

	friend std::ostream& operator<<(std::ostream& out, const BigInt& a)
	{
		if (a.sign_ == -1)
			out << "-";
		out << a.bigNumber_[a.size_ - 1];
		for (size_t i = a.size_ - 2; (i >= 0) && (i <= a.size_ - 1); i--)
		{
			if (a.bigNumber_[i] == 0)
				if (a.size_ == 1)
				{
					out << "0";
					return out;
				}
				else
				{
					out << "0000";
					continue;
				}
			int buf = a.bigNumber_[i];
			int secondBuf = options::base / 10;
			while ((buf / secondBuf) == 0)
			{
				out << "0";
				secondBuf /= 10;
			}
			out << a.bigNumber_[i];
		}
		return out;
	}
};
