#include "BigInt.h"


BigInt::BigInt()
{
	num = new short();
	size = 1;
	is_positive = true;
}

BigInt::BigInt(int x)
{
	is_positive = (x >= 0);
	if (!is_positive)
		x = -1 * x;
	int s = 1;
	int x_copy = x;
	while (x_copy / 10)
	{
		x_copy /= 10;
		s++;
	}
	size = s;
	num = new short[size];
	for (int i = size - 1; i >= 0; i--)
	{
		num[size-1-i] = x % 10;
		x /= 10;
	}
}

BigInt::BigInt(const short n[], int s, bool isp)
{
	is_positive = isp;
	size = s;
	num = new short[size];
	for (int i = 0; i < size; i++)
	{
		num[i] = n[i];
	}
}

BigInt::BigInt(const BigInt& other)
{
	is_positive = other.is_positive;
	size = other.size;
	num = new short[size];
	for (int i = 0; i < size; i++)
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
	int max_size,min_size;
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
	short* result = new short[max_size + 1];
	int buf = 0;
	result[0] = 0;

	for (int i = 0; i < min_size; i++)
	{
		result[i] = (num[i] + other.num[i] + buf) % 10;
		buf = (num[i] + other.num[i] + buf) / 10;
	}
	for (int i = min_size; i < max_size; i++)
	{
		result[i] = (num[i] * this_bigger + other.num[i] * (1 - this_bigger) + buf) % 10;
		buf = (num[i] * this_bigger + other.num[i] * (1 - this_bigger) + buf) / 10;
	}
	if (buf != 0)
	{
		result[max_size] = buf;
		max_size += 1;
	}
	else
	{
		short* result_new = new short[max_size];
		for (int i = 0; i < max_size; i++)
		{
			result_new[i] = result[i];
		}
		delete result;
		return BigInt(result_new, max_size, is_positive);
	}
	return BigInt(result, max_size, is_positive);
}
BigInt BigInt::operator-(const BigInt& other) const
{
	int max_size, min_size;
	bool this_bigger = true;
	BigInt tmp = *this;
	BigInt other_tmp = other;
	if (*this == other)
	{
		return BigInt(new short(), 1, true);
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
			tmp = other;
			other_tmp = *this;
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
	short* result = new short[max_size];
	bool buf = false;
	for (int i = 0; i < min_size; i++)
	{
		result[i] = tmp.num[i] - other_tmp.num[i] - buf;
		buf = result[i] < 0;
		if (buf)
		{
			result[i] += 10;
		}
	}
	for (int i = min_size; i < max_size; i++)
	{
		result[i] = tmp.num[i] - buf;
		buf = result[i] < 0;
		if (buf)
		{
			result[i] += 10;
		}
	}
	int last=max_size;
	while (result[last-1] == 0)
		last--;
	short*result_new = new short[last];
	for (int i = 0; i < last; i++)
		result_new[i] = result[i];
	delete result;
	return BigInt(result_new, last, tmp.is_positive*this_bigger);
}
BigInt BigInt::operator*(const BigInt& other) const
{
	if (size == 1 && num[0] == 0 || other.size == 1 && other.num[0] == 0)
		return BigInt(new short(), 1, true);
	int s = size + other.size;
	short*result = new short[s]();
	int buf = 0;
	for (int i = 0; i<size; ++i)
		for (int j = 0, buf = 0; j<other.size || buf; ++j)
		{
			long long cur = result[i + j] + num[i] * (j < other.size ? other.num[j] : 0) + buf;
			result[i + j] = int(cur % 10);
			buf = int(cur / 10);
		}
	int last = s;
	while (result[last - 1] == 0)
		last--;
	short*result_new = new short[last];
	for (int i = 0; i < last; i++)
		result_new[i] = result[i];
	delete result;
	return BigInt(result_new, last, is_positive == other.is_positive);
}
BigInt BigInt::operator/(const BigInt& other) const
{
	BigInt tmp = *this;
	BigInt other_tmp = other;
	if (!tmp.is_positive)
		tmp = -tmp;
	if (!other_tmp.is_positive)
		other_tmp = -other_tmp;
	if (size == 1 && num[0] == 0 || tmp<other_tmp)
		return BigInt();
	int counter = 0;
	while (tmp >= other_tmp)
	{
		tmp = tmp - other_tmp;
		counter++;
	}
	BigInt result = counter;
	return BigInt(result.num, result.size, is_positive == other.is_positive);
}
void BigInt::operator=(const BigInt& other)
{
	if (this == &other)
		return;
	size = other.size;
	num = new short[size];
	is_positive = other.is_positive;
	for (int i = 0; i < size; i++)
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
	num = new short[size];
	for (int i = 0; i < size; i++)
		num[i] = a.num[i];
}
BigInt BigInt::operator-() const
{
	if (size == 1 && num[0] == 0)
		return *this;
	return BigInt(num,size,!is_positive);
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
	if (size == 1 && num[0] == 0 && other.size == 1 && other.num[0] == 0)
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
		out << number.num[i];
	return out;
}
 