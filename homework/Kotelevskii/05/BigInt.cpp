#include "BigInt.h"

BigInt::BigInt()
{
	num = new char[1]{ '0' };
	size = 1;
	is_positive = true;
}
BigInt::BigInt(int64_t x)
{
	is_positive = (x >= 0);
	if (!is_positive)
		x *=-1;
	size_t s = 1;
	int64_t x_copy = x;
	while (x_copy / 10)
	{
		x_copy /= 10;
		s++;
	}
	size = s;
	num = new char[size];
	for (int i = size - 1; i >= 0; i--)
	{
		num[size-1-i] = x % 10 +'0';
		x /= 10;
	}
}

BigInt::BigInt(const BigInt& other)
{
	is_positive = other.is_positive;
	size = other.size;
	num = new char[size];
	for (size_t i = 0; i < size; i++)
	{
		num[i] = other.num[i];
	}
}

BigInt::~BigInt()
{
	delete num;
}

BigInt BigInt::operator+(const BigInt& other) const
{
	if (is_positive != other.is_positive)
	{
		if (!is_positive)
		{
			return other-(-*this);
		}
		else
		{
			return *this - (-other);
		}
	}
	size_t max_size,min_size;
	bool this_bigger = false;
	if (size > other.size)
	{
		max_size = size;
		min_size = other.size;
		this_bigger = true;
	}
	else
	{
		max_size = other.size;
		min_size = size;
	}
	BigInt result;
	result.resize(max_size + 1);
	result.fill_zeros();
	int buf = 0;
	for (size_t i = 0; i < min_size; i++)
	{
		result.num[i] = (num[i]-'0' + other.num[i]-'0' + buf) % 10 +'0';
		buf = (num[i] - '0' + other.num[i] - '0' + buf) / 10;
	}
	for (size_t i = min_size; i < max_size; i++)
	{
		result.num[i] = ((num[i]-'0') * this_bigger + (other.num[i]-'0') * (1 - this_bigger) + buf) % 10 +'0';
		buf = ((num[i] - '0') * this_bigger + (other.num[i] - '0') * (1 - this_bigger) + buf) / 10;
	}
	if (buf != 0)
	{
		result.num[max_size] = buf+'0';
		max_size += 1;
	}
	else
	{
		BigInt result_new;
		result_new.resize(max_size);
		result_new.fill_zeros();
		for (size_t i = 0; i < max_size; i++)
		{
			result_new.num[i] = result.num[i];
		}
		result_new.set_sign(is_positive);
		return result_new;
	}
	result.set_sign(is_positive);
	return result;
}
BigInt BigInt::operator-(const BigInt& other) const
{
	size_t max_size, min_size;
	bool this_bigger = true;
	BigInt tmp = *this;
	BigInt other_tmp = other;
	if (*this == other)
	{
		return BigInt();
	}
	else if (is_positive == false && other.is_positive == true)
	{
		return -(-(*this) + other);
	}
	else if (is_positive == true && other.is_positive == false)
	{
		return (*this) + (-other);
	}
	else if (is_positive == true)
	{
		this_bigger = (*this) > other;
		if (!this_bigger)
		{
			std::swap(tmp.num, other_tmp.num);
		}
		max_size = size*this_bigger + (1 - this_bigger)*other.size;
		min_size = size*(1 - this_bigger) + this_bigger*other.size;
	}
	else
	{
		if (other.size > size)
		{
			max_size = other.size;
			min_size = size;
			tmp = -other_tmp;
			other_tmp = *this;
		}
		else if(other.size < size)
		{
			max_size = size;
			min_size = other.size;
			other_tmp = -other_tmp;
		}
		else
		{
			max_size = size;
			min_size = size;
			if (other < *this)
			{
				tmp = -other;
				other_tmp = *this;
			}
		}
	}
	BigInt result;
	result.resize(max_size);
	result.fill_zeros();
	bool buf = false;
	for (size_t i = 0; i < min_size; i++)
	{
		result.num[i] = tmp.num[i] - other_tmp.num[i] - buf;
		buf = result.num[i] < 0;
		if (buf)
		{
			result.num[i] = result.num[i] + 10;
		}
		result.num[i] += '0';
	}
	for (size_t i = min_size; i < max_size; i++)
	{
		result.num[i] = tmp.num[i] - (buf+'0');
		buf = result.num[i] < 0;
		if (buf)
		{
			result.num[i] = result.num[i] + 10;
		}
		result.num[i] += '0';
	}
	size_t last=max_size;
	while (result.num[last-1] == '0')
		last--;
	BigInt result_new;
	result_new.resize(last);
	result_new.fill_zeros();
	for (size_t i = 0; i < last; i++)
		result_new.num[i] = result.num[i];
	result_new.set_sign(tmp.is_positive&&this_bigger);
	return result_new;
}
BigInt BigInt::operator*(const BigInt& other) const
{
	if (size == 1 && num[0] == '0' || other.size == 1 && other.num[0] == '0')
		return BigInt();
	size_t s = size + other.size;
	BigInt result;
	result.resize(s);
	result.fill_zeros();
	int buf = 0;
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0, buf = 0; j < other.size || buf; ++j)
		{
			long long cur = result.num[i + j] - '0' + (num[i] - '0') * (j < other.size ? (other.num[j] - '0') : 0) + buf;
			result.num[i + j] = int(cur % 10) + '0';
			buf = int(cur / 10);
		}
	size_t last = s;
	while (result.num[last - 1] == '0')
		last--;
	BigInt result_new;
	result_new.resize(last);
	result_new.fill_zeros();
	for (size_t i = 0; i < last; i++)
		result_new.num[i] = result.num[i];
	result_new.set_sign(is_positive == other.is_positive);
	return result_new;
}
BigInt BigInt::operator/(const BigInt& other) const
{
	BigInt tmp = *this;
	BigInt other_tmp = other;
	if (!tmp.is_positive)
		tmp.set_sign(true);
	if (!other_tmp.is_positive)
		other_tmp.set_sign(true);
	if (size == 1 && num[0] == '0' || tmp < other_tmp)
	{
		return BigInt();
	}
	else if ((*this) == other)
	{
		return BigInt(1);
	}
	size_t counter = 0;
	unsigned mult = 1;
	bool f;
	while (tmp >= other_tmp)
	{
		f = false;
		mult = 1;
		while (tmp >= BigInt(mult)*other_tmp)
		{
			mult *= 100;
		}
		if (mult > 1)
		{
			mult /= 100;
		}
		while (tmp >= BigInt(mult)*other_tmp)
		{
			mult *= 2;
			f = true;
		}
		if (f)
		{
			mult /= 2;
		}
		tmp = std::move(tmp - BigInt(mult)*other_tmp);
		counter+=mult;
	}
	BigInt result = counter;
	result.set_sign(is_positive == other.is_positive);
	return result;
}
void BigInt::operator=(const BigInt& other)
{
	if (this == &other)
		return;
	delete[] num;
	size = other.size;
	num = new char[other.size];
	is_positive = other.is_positive;
	for (size_t i = 0; i < size; i++)
		num[i] = other.num[i];
	return;
}
void BigInt::operator=(const int& number)
{
	BigInt a(number);
	if (num != nullptr)
	{
		delete num;
	}
	size = a.size;
	num = new char[size];
	for (size_t i = 0; i < size; i++)
		num[i] = a.num[i];
}
BigInt BigInt::operator-() const
{
	if (size == 1 && num[0] == '0')
		return *this;
	BigInt result;
	result.resize(size);
	for (size_t i = 0; i < size; i++)
		result.num[i] = num[i];
	result.set_sign(!is_positive);
	return result;
}
bool BigInt::operator>(const BigInt& other) const
{
	if (is_positive)
	{
		if (!other.is_positive)
		{
			return true;
		}
		else
		{
			if (size > other.size)
			{
				return true;
			}
			else if (size < other.size)
			{
				return false;
			}
			else
			{
				for (int i = size - 1; i >= 0; i--)
				{
					if (num[i] > other.num[i])
					{
						return true;
					}
					else if (num[i] < other.num[i])
					{
						return false;
					}
				}
				return false;
			}
		}
	}
	else
	{
		if (other.is_positive)
		{
			return false;
		}
		else
		{
			BigInt other_tmp = other;
			BigInt tmp = *this;
			return (-other_tmp) > (-tmp);
		}
	}
}
bool BigInt::operator<(const BigInt& other) const
{
	return other > *this;
}
bool BigInt::operator==(const BigInt& other) const
{
	if (size == 1 && num[0] == '0' && other.size == 1 && other.num[0] == '0')
		return true;
	return !((*this > other) || (*this < other));
}
bool BigInt::operator!=(const BigInt& other) const
{
	return !(*this == other);
}
bool BigInt::operator>=(const BigInt& other) const
{
	return (*this > other) || (*this == other);
}
bool BigInt::operator<=(const BigInt& other) const
{
	return (*this < other) || (*this == other);
}
std::ostream& operator<<(std::ostream& out, const BigInt& number)
{
	if (!number.is_positive)
		out << '-';
	for (int i = number.size - 1; i >= 0; i--)
		out << number.num[i]-'0';
	return out;
}
void BigInt::resize(size_t n)
{
	size = n;
	delete num;
	num = new char[n];
}
void BigInt::fill_zeros()
{
	for (size_t i = 0; i < size; i++)
		num[i] = '0';
}
void BigInt::set_sign(bool sign)
{
	is_positive = sign;
}