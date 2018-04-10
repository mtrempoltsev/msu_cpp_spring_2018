#pragma once

#include <string>
#include <algorithm>
#include <memory>

class U_Vector
{
public:
	typedef std::unique_ptr<int[]> ptr;

	U_Vector();
	U_Vector(size_t size);
	U_Vector(size_t size, const int & initial);
	U_Vector(const U_Vector & v);
	~U_Vector();

	size_t size() const;
	size_t capacity() const;

	void push_back(const int & value);
	void push_front(const int & value);
	void pop();

	void reserve(size_t capacity);
	void resize(size_t size);

	int & operator[](size_t index);
	const int & operator[](size_t index) const;

	U_Vector & operator=(const U_Vector &);

private:
	size_t _size;
	size_t _capacity;
	std::unique_ptr<int[]> _buffer;
};

U_Vector::U_Vector()
{
	_size = 0;
	_capacity = 0;
	_buffer = nullptr;
}

U_Vector::~U_Vector()
{

}

U_Vector::U_Vector(size_t size)
{
	_capacity = size;
	_size = size;
	_buffer = std::make_unique<int[]>(_size);
}

U_Vector::U_Vector(const U_Vector & v)
{
	_size = v._size;
	_capacity = v._capacity;
	_buffer = std::make_unique<int[]>(_size);
	for (size_t i = 0; i < _size; i++)
		_buffer[i] = v._buffer[i];
}

U_Vector::U_Vector(size_t size, const int & initial)
{
	_size = size;
	_capacity = size;
	_buffer = std::make_unique<int[]>(_size);
	for (size_t i = 0; i < size; i++)
		_buffer[i] = initial;
}

U_Vector & U_Vector::operator=(const U_Vector & v)
{
	_size = v._size;
	_capacity = v._capacity;
	_buffer = std::make_unique<int[]>(_capacity);
	for (size_t i = 0; i < _size; i++)
		_buffer[i] = v._buffer[i];

	return *this;
}

void U_Vector::reserve(size_t capacity)
{
	if (_size == capacity)
		return;

	ptr new_buffer = std::make_unique<int[]>(capacity);

	size_t l_Size = capacity < _size ? capacity : _size;

	for (size_t i = 0; i < l_Size; i++)
		new_buffer[i] = _buffer[i];

	if (capacity > _size)
		for (size_t i = _size; i < capacity; i++)
			new_buffer[i] = 0;

	_capacity = capacity;

	_buffer = std::move(new_buffer);
}

void U_Vector::push_back(const int & v)
{
	if (_size >= _capacity)
		reserve(_capacity * 2 + 1);
	_buffer[_size++] = v;
}

size_t U_Vector::size() const
{
	return _size;
}

size_t U_Vector::capacity() const
{
	return _capacity;
}

void U_Vector::resize(size_t size)
{
	reserve(size);
	_size = size;
}

int& U_Vector::operator[](size_t index)
{
	return _buffer[index];
}

const int& U_Vector::operator[](size_t index) const
{
	return _buffer[index];
}

void U_Vector::push_front(const int & v)
{
	int prev_size = _size;
	resize(_size + 1);
	for (int i = prev_size - 1; i >= 0; i--)
		_buffer[i + 1] = _buffer[i];
	_buffer[0] = v;
}

void U_Vector::pop()
{
	_size--;
}

class BigInt
{
public:
	BigInt();
	BigInt(const BigInt& copied);
	BigInt(const int64_t& i_copied);

	BigInt& operator=(const BigInt& other);
	BigInt& operator=(const int64_t& i_other);

	bool operator<(const BigInt& right) const;
	bool operator>(const BigInt& right) const;
	bool operator==(const BigInt& right) const;
	bool operator!=(const BigInt& right) const;
	bool operator<=(const BigInt& right) const;
	bool operator>=(const BigInt& right) const;

	BigInt& delete_nulls();

	int binSearch(const BigInt &dividend, const BigInt &divisor) const;

	BigInt operator-(const BigInt& right) const;
	BigInt operator+(const BigInt& right) const;
	BigInt operator*(const BigInt& right) const;
	BigInt operator/(const BigInt& number) const;

	BigInt& operator*=(const BigInt& right);
	BigInt& operator/=(const BigInt& right);
	BigInt& operator+=(const BigInt& right);
	BigInt& operator-=(const BigInt& right);

	BigInt operator-() const;

	size_t size() const;

	friend std::ostream& operator<<(std::ostream& os, const BigInt& dt);
	friend BigInt abs(const BigInt& other);

private:
	BigInt(const bool sign, const U_Vector num);

	U_Vector bigInt;
	bool isNegative;
};

BigInt::BigInt()
{
	bigInt.push_back(0);
	isNegative = false;
}

BigInt::BigInt(const BigInt& copied)
{
	bigInt = copied.bigInt;
	isNegative = copied.isNegative;
};

BigInt::BigInt(const bool sign, const U_Vector num)
{
	isNegative = sign;
	bigInt = num;
};

BigInt::BigInt(const int64_t& i_copied)
{
	if (i_copied < 0)
		isNegative = true;
	else
		isNegative = false;

	std::string i_str = std::to_string(std::abs(i_copied));
	std::reverse(i_str.begin(), i_str.end());
	bigInt.resize(i_str.size());
	for (int i = 0; i < i_str.size(); i++)
		bigInt[i] = i_str[i] - '0';
};

BigInt& BigInt::operator=(const BigInt& other)
{
	if (this == &other)
		return *this;

	bigInt = other.bigInt;
	isNegative = other.isNegative;
	return *this;
}

BigInt& BigInt::operator=(const int64_t& i_other)
{
	if (i_other < 0)
		isNegative = true;
	else
		isNegative = false;

	std::string i_str = std::to_string(std::abs(i_other));
	std::reverse(i_str.begin(), i_str.end());
	bigInt.resize(i_str.size());
	for (int i = 0; i < i_str.size(); i++)
		bigInt[i] = i_str[i] - '0';

	return *this;
}

bool BigInt::operator<(const BigInt& right) const
{
	if (isNegative != right.isNegative)
		return (isNegative);

	if (!isNegative)
	{
		if (bigInt.size() != right.bigInt.size())
		{
			return (bigInt.size() < right.bigInt.size());
		}
		else
		{
			for (int i = bigInt.size() - 1; i >= 0; i--)
			{
				if (bigInt[i] < right.bigInt[i])
					return true;
				else if (bigInt[i] > right.bigInt[i])
					return false;
			}
			return false;
		}
	}
	else
	{
		if (bigInt.size() != right.bigInt.size())
		{
			return (bigInt.size() > right.bigInt.size());
		}
		else
		{
			for (int i = bigInt.size() - 1; i >= 0; i--)
			{
				if (bigInt[i] < right.bigInt[i])
					return false;
			}
			return true;
		}
	}
}

bool BigInt::operator>(const BigInt& right) const
{
	return right < *this;
}

bool BigInt::operator==(const BigInt& right) const
{
	if (bigInt.size() != right.bigInt.size())
		return false;

	for (int i = 0; i < right.bigInt.size(); i++)
	{
		if (bigInt[i] != right.bigInt[i])
			return false;
	}
	return true;
};

bool BigInt::operator !=(const BigInt& right) const
{
	return !(*this == right);
};

bool BigInt::operator<=(const BigInt& right) const
{
	return !(*this > right);
}

bool BigInt::operator>=(const BigInt& right) const
{
	return !(*this < right);
}

BigInt& BigInt::delete_nulls()
{
	size_t length = this->size();
	int end = bigInt.size() - 1;
	int c = 0;
	while (bigInt[end] == 0 && end != 0)
	{
		c++;
		end--;
	}
	this->bigInt.resize(length - c);
	return *this;
}

BigInt BigInt::operator+(const BigInt& right) const
{
	if (isNegative == right.isNegative)
	{
		size_t length = std::max(bigInt.size(), right.bigInt.size());
		U_Vector result(length + 1, 0);

		U_Vector l = bigInt;
		U_Vector r = right.bigInt;

		l.resize(length);
		r.resize(length);

		for (int i = 0; i < length; i++)
		{
			result[i] += l[i] + r[i];
			result[i + 1] += result[i] / 10;
			result[i] %= 10;
		}

		auto res = BigInt(isNegative, result);
		res.delete_nulls();

		return res;
	}
	else
	{
		if (*this == 0 || right == 0)
			return *this == 0 ? right : *this;

		auto absR = abs(right);
		auto absL = abs(*this);

		if (absR == absL)
			return BigInt(0);

		if (absL > absR)
		{
			bool sign = this->isNegative;
			size_t length = std::max(bigInt.size(), right.bigInt.size());
			U_Vector result(length, 0);

			U_Vector l = absL.bigInt;
			U_Vector r = absR.bigInt;

			l.resize(length);
			r.resize(length);
			for (int i = 0; i < length; i++)
			{
				result[i] += l[i] - r[i];
				if (result[i] < 0)
				{
					result[i] += 10;
					result[i + 1] -= 1;
				}
			}

			auto res = BigInt(sign, result);
			res.delete_nulls();

			return res;
		}
		else
			return right.operator+(*this);
	}
}

BigInt BigInt::operator*(const BigInt& right) const
{
	if (*this == 0 || right == 0)
		return BigInt(0);

	U_Vector r_copy = right.bigInt;
	U_Vector l_copy = this->bigInt;
	bool isNeg = !(right.isNegative == this->isNegative);

	size_t length = r_copy.size() + l_copy.size();
	U_Vector res(length, 0);

	for (int ix = 0; ix < r_copy.size(); ix++)
		for (int jx = 0; jx < l_copy.size(); jx++)
			res[ix + jx] += r_copy[ix] * l_copy[jx];

	for (int ix = 0; ix < length - 1; ix++)
	{
		res[ix + 1] += res[ix] / 10;
		res[ix] %= 10;
	}

	auto result = BigInt(isNeg, res);
	result.delete_nulls();

	return result;
}

int BigInt::binSearch(const BigInt &dividend, const BigInt &divisor) const
{
	int result = 0;
	int min = 0;
	int max = 10;

	while (min <= max)
	{
		int curr = (max + min) / 2;
		if (BigInt(curr) * divisor <= dividend)
		{
			result = curr;
			min = curr + 1;
		}
		else
			max = curr - 1;
	}
	return result;
}

BigInt BigInt::operator/(const BigInt& number) const
{
	BigInt result;
	BigInt aux;
	aux.bigInt.pop();
	BigInt abs_number = abs(number);
	for (size_t i = 0; i < this->size(); i++)
	{
		aux.bigInt.push_front(bigInt[this->size() - 1 - i]);
		aux.delete_nulls();
		int div = binSearch(aux, abs_number);
		result.bigInt.push_front(div);
		aux = aux - abs_number * BigInt(div);
		aux.isNegative = false;
	}

	result.delete_nulls();
	result.isNegative = isNegative != number.isNegative;
	return result;
}

BigInt& BigInt::operator*=(const BigInt& right)
{
	*this = *this * right;
	return *this;
};

BigInt& BigInt::operator/=(const BigInt& right)
{
	*this = *this / right;
	return *this;
};

BigInt& BigInt::operator+=(const BigInt& right)
{
	*this = *this + right;
	return *this;
};

BigInt BigInt::operator-(const BigInt& right) const
{
	return (*this + (-right));
}

BigInt& BigInt::operator-=(const BigInt& right)
{
	*this = *this - right;
	return *this;
};

BigInt BigInt::operator-() const
{
	BigInt copy(*this);
	copy.isNegative = !isNegative;

	return copy;
}

size_t BigInt::size() const
{
	return this->bigInt.size();
}

std::ostream& operator<<(std::ostream& os, const BigInt& dt)
{
	if (dt.size() == 1 && dt.bigInt[0] == 0)
	{
		os << 0;
		return os;
	}
	if (dt.isNegative)
		os << '-';
	for (int i = int(dt.bigInt.size()) - 1; i >= 0; i--)
		os << dt.bigInt[i];

	return os;
};

BigInt abs(const BigInt& other)
{
	BigInt copy(other);
	copy.isNegative = false;
	return copy;
}

