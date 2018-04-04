#include<iostream>

constexpr int base = 10000;
constexpr int numberOfDigitsInBase = 4;

class BigInt
{
	int sign_;
	int* bigNumber_;
	size_t size_;
public:
	BigInt() : bigNumber_(NULL) {}
	
	BigInt(size_t size, int a = 0) : sign_(1), size_(size)
	{
		bigNumber_ = (int*) malloc(size * sizeof(int));
		for (size_t i = 0; i < size_; i++)
			bigNumber_[i] = 0;
	}

	~BigInt()
	{
		free(bigNumber_);
	}

	BigInt(const BigInt& a) : sign_(a.sign_), size_(a.size_)
	{
		bigNumber_ = (int*) malloc(size_ * sizeof(int));
		for(size_t i = 0; i < size_; i++)
			bigNumber_[i] = a.bigNumber_[i];
	}

	BigInt& operator=(const BigInt& a)
	{
		if (this == &a)
			return *this;
		size_ = a.size_;
		sign_ = a.sign_;
		free(bigNumber_);
		bigNumber_ = (int*) malloc(size_ * sizeof(int));
		for (size_t i = 0; i < size_; i++)
			bigNumber_[i] = a.bigNumber_[i];
		return *this;
	}

	BigInt(BigInt &&a) : sign_(a.sign_), bigNumber_(a.bigNumber_), size_(a.size_)
	{
		a.bigNumber_ = NULL;
	}

	BigInt& operator=(BigInt &&a)
	{
		if (this == &a)
			return *this;
		size_ = a.size_;
		sign_ = a.sign_;
		free(bigNumber_);
		bigNumber_ = a.bigNumber_;
		a.bigNumber_ = NULL;
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
		if (b.sign_ == 1)
		{
			for(size_t i = b.size_ - 1;((i < b.size_) && (i >= 0)); i--)
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
			for(size_t i = b.size_ - 1;((i < b.size_) && (i >= 0)); i--)
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
		if (!((*this) <= b))
			return true;
		else
			return false;
	}

	bool operator<=(const BigInt& b) const
	{
		if (((*this) == b) || ((*this) < b))
			return true;
		else
			return false;
	}

	bool operator>=(const BigInt& b) const
	{
		return !((*this) < b);
	}

	BigInt operator+(const BigInt& b) const
	{
		BigInt result;
		if ((*this).size_ >= b.size_)
			result = *this;
		else
			result = b;
		int toNextDigit = 0;
		size_t i = 0;
		for(i; i < std::min((*this).size_ , b.size_); i++)
		{
			int buf = (*this).bigNumber_[i] + b.bigNumber_[i] + toNextDigit;
			toNextDigit = buf / base;
			result.bigNumber_[i] = buf % base;
		}
		if (toNextDigit == 1)
			if ((*this).size_ == b.size_)
			{
				result.size_ += 1;
				result.bigNumber_ = (int*) realloc (bigNumber_, sizeof(int));
				result.bigNumber_[result.size_ - 1] = 1;
			}
			else
				result.bigNumber_[i + 1] += toNextDigit;
		return result;
	}

	BigInt operator-()
	{
		(*this).sign_ *= -1;
		return *this;
	}

	BigInt abs() const
	{
		BigInt result = (*this);
		result.sign_ = 1;
		return result;
	}

	BigInt operator-(const BigInt& b) const
	{
		if (((*this).sign_ == 1) && (b.sign_ == -1))
			return (*this) + b;
		BigInt result;
		if (((*this).sign_ == -1) && (b.sign_ == 1))
			{
				result = (*this) + b;
				result.sign_ = -1;
				return result;
		}
		BigInt bufBigInt;
		if ((*this).abs() > b.abs())
		{
			result = (*this);
			bufBigInt = b;
		}
		else
		{
			result = b;
			bufBigInt = (*this);
		}
		int toNextDigit = 0;
		size_t i = 0;
		for(i; i < bufBigInt.size_; i++)
		{
			int buf = result.bigNumber_[i] - bufBigInt.bigNumber_[i] + toNextDigit;
			if (buf < 0)
			{
				result.bigNumber_[i] = base + buf;
				int debug = buf - base;
				toNextDigit = debug / base;
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
		result.bigNumber_ = (int*) realloc(result.bigNumber_, result.size_ * sizeof(int));
		return result;
	}

	BigInt operator*(const BigInt& b) const
	{
		BigInt result((*this).size_ * b.size_ + 1, 0);
		for (size_t i = 0; i < b.size_; i++)
		{
			size_t j = 0;
			int toNextDigit = 0;
			for (; j < (*this).size_; j++)
			{
				result.bigNumber_[j + i] += toNextDigit;
				result.bigNumber_[j + i] += b.bigNumber_[i] * (*this).bigNumber_[j];
				toNextDigit = result.bigNumber_[j + i] / base;
				result.bigNumber_[j + i] %= base;
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
		result.bigNumber_ = (int*) realloc(result.bigNumber_, result.size_ * sizeof(int));
		return result;
	}

	BigInt operator*(int a) const
	{
		BigInt buf(1, 0);
		buf.bigNumber_[0] = a;
		return (*this) * buf;
	}

	void LevelUp()
	{
		(*this).bigNumber_ = (int*) realloc((*this).bigNumber_, sizeof(int) * ((*this).size_ + 1));
		(*this).size_++;
		for (size_t i = size_ - 1; i >= 1; i--)
			bigNumber_[i] = bigNumber_[i-1];
		bigNumber_[0] = 0;
	}

	BigInt operator/(const BigInt &b) const
	{
		BigInt result((*this).size_, 0);
		BigInt curValue(1, 0);
		for (size_t i = (*this).size_ - 1;((i < (*this).size_) && (i >= 0)); i--)
		{
			curValue.LevelUp();
			curValue.bigNumber_[0] = (*this).bigNumber_[i];
			int x = 0;
			int l = 0, r = base;
			while (l <= r)
			{
				int m = (l + r) >> 1;
				BigInt cur = b * m;
				if (cur <= curValue)
				{
					x = m;
					l = m + 1;
				}
				else
					r = m - 1;
			}
			result.bigNumber_[i] = x;
			curValue = curValue - b * x;
		}
		size_t i = result.size_ - 1;
		while (result.size_ > 0)
		{
			if (result.bigNumber_[i] == 0)
				result.size_--;
			else
				break;
			i--;
		}
		result.bigNumber_ = (int*) realloc(result.bigNumber_, result.size_ * sizeof(int));
		result.sign_ = (*this).sign_ * b.sign_;
		return result;
	}

	friend std::istream& operator>>(std::istream& in, BigInt& a)
	{
		char ch;
		char* stringOfNumber = new char[1024 * 1024];
		in >> ch;
		size_t i = 0;
		size_t bufNumberOfDigitsInBase = numberOfDigitsInBase;
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
		size_t sizeOfBigNumber = i / numberOfDigitsInBase;
		bool flag = false;
		if (i % numberOfDigitsInBase != 0)
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
			char bufString[numberOfDigitsInBase];
			for (size_t k = 0; k < numberOfDigitsInBase; k++)
			{
				char nBuf = stringOfNumber[i - numberOfDigitsInBase * (j + 1) + k];
				bufString[k] = nBuf;
			}
			a.bigNumber_[j] = atoi(bufString);
		}
		if (flag == true)
		{
			size_t buff = i % numberOfDigitsInBase;
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
			std::cout << "-";
		std::cout << a.bigNumber_[a.size_ - 1];
		for (size_t i = a.size_ - 2; (i >= 0) && (i <= a.size_ - 1); i--)
		{
			if (a.bigNumber_[i] == 0)
				if (a.size_ == 1)
					{
						std::cout << "0";
						return out;
					}
				else
				{
					std:: cout << "0000";
					continue;
				}
			int buf = a.bigNumber_[i];
			int secondBuf = base / 10;
			while((buf / secondBuf) == 0)
			{
				std::cout << "0";
				secondBuf /= 10;
			}
			std::cout << a.bigNumber_[i];
		}
		std::cout << std::endl;
		return out;
	}
};
