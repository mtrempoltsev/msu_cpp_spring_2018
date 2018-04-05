#pragma once

#include <string>
#include <algorithm>

class  Vector
{
public:

	typedef int* ptr;

	Vector();
	Vector(size_t size);
	Vector(size_t size, const int & initial);
	Vector(const Vector & v);
	~Vector();

	size_t capacity() const;
	size_t size() const;
	ptr begin();
	ptr end();
	ptr begin() const ;
	ptr end() const ;
	int & front();
	int & back();
	void push_back(const int & value);
	void push_front(const int & value);
	void pop_back();

	void reserve(size_t capacity);
	void resize(size_t size);

	int & operator[](unsigned int index);
	int & operator[](unsigned int index) const;
	Vector & operator=(const Vector &);
	void clear();

private:
	size_t my_size;
	size_t my_capacity;
	int * buffer;
};

Vector::Vector()
{
	my_capacity = 0;
	my_size = 0;
	buffer = 0;
}

Vector::Vector(const Vector & v)
{
	my_size = v.my_size;
	my_capacity = v.my_capacity;
	buffer = new int[my_size];
	for (size_t i = 0; i < my_size; i++)
		buffer[i] = v.buffer[i];
}

Vector::Vector(size_t size)
{
	my_capacity = size;
	my_size = size;
	buffer = new int[size];
}

Vector::Vector(size_t size, const int & initial)
{
	my_size = size;
	my_capacity = size;
	buffer = new int[size];
	for (size_t i = 0; i < size; i++)
		buffer[i] = initial;
}

Vector & Vector::operator = (const Vector & v)
{
	delete[] buffer;
	my_size = v.my_size;
	my_capacity = v.my_capacity;
	buffer = new int[my_size];
	for (size_t i = 0; i < my_size; i++)
		buffer[i] = v.buffer[i];
	return *this;
}

Vector::ptr Vector::begin()
{
	return buffer;
}

Vector::ptr Vector::end()
{
	return buffer + size();
}

Vector::ptr Vector::begin() const
{
	return buffer;
}

Vector::ptr Vector::end() const
{
	return buffer + size();
}

int& Vector::front()
{
	return buffer[0];
}

int& Vector::back()
{
	return buffer[my_size - 1];
}

void Vector::push_back(const int & v)
{
	if (my_size >= my_capacity)
		reserve(my_capacity + 5);
	buffer[my_size++] = v;
}

void Vector::push_front(const int & v)
{
	int prev_size = my_size;
	this->resize(my_size + 1);
	for (int i = prev_size - 1; i >= 0; i--)
		buffer[i + 1] = buffer[i];
	buffer[0] = v;
}

void Vector::pop_back()
{
	my_size--;
}

void Vector::reserve(size_t capacity)
{
	if (buffer == 0)
	{
		my_size = 0;
		my_capacity = 0;
	}

	if (capacity == my_size)
		return;

	ptr Newbuffer = new int[capacity];
	size_t l_Size = capacity < my_size ? capacity : my_size;

	for (size_t i = 0; i < l_Size; i++)
		Newbuffer[i] = buffer[i];

	delete[] buffer;

	if (capacity > my_size)
		for (size_t i = my_size; i < capacity; i++)
			Newbuffer[i] = 0;

	my_capacity = capacity;
	buffer = Newbuffer;

}

size_t Vector::size()const
{
	return my_size;
}

void Vector::resize(size_t size)
{
	reserve(size);
	my_size = size;
}

int& Vector::operator[](unsigned int index)
{
	return buffer[index];
}

int& Vector::operator[](unsigned int index) const
{
	return buffer[index];
}

size_t Vector::capacity()const
{
	return my_capacity;
}

Vector::~Vector()
{
	delete[] buffer;
}

void Vector::clear()
{
	my_capacity = 0;
	my_size = 0;
	buffer = 0;
}

class BigInt
{
public:

	BigInt();
	BigInt(const BigInt& copied);
	BigInt(const bool sign, const Vector num);
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
	friend void ref_abs(BigInt& left, BigInt& right);

public:
	Vector bigInt;
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

BigInt::BigInt(const bool sign, const Vector num)
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
	auto it = this->bigInt.end() - 1;
	int c = 0;
	while (*it == 0 && it != this->bigInt.begin())
	{
		c++;
		it--;
	}
	this->bigInt.resize(length - c);
	return *this;
}

BigInt BigInt::operator+(const BigInt& right) const
{
	if (isNegative == right.isNegative)
	{
		size_t length = std::max(bigInt.size(), right.bigInt.size());
		Vector result(length + 1, 0);

		Vector l = bigInt;
		Vector r = right.bigInt;

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
			Vector result(length, 0);

			Vector l = absL.bigInt;
			Vector r = absR.bigInt;

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

	Vector r_copy = right.bigInt;
	Vector l_copy = this->bigInt;
	bool isNeg = !(right.isNegative == this->isNegative);

	size_t length = r_copy.size() + l_copy.size();
	Vector res(length, 0);

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
	aux.bigInt.pop_back();
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

void ref_abs(BigInt& left, BigInt& right)
{
	left.isNegative = false;
	right.isNegative = false;
}

