#include "BigInt.h"
#include <cstring>

BigInt::BigInt()
{
	data = new cell_type[capacity];
	this->push_back(0);
}

BigInt::BigInt(int64_t value)
{
	if (value < 0)
	{
		isNegative = true;
		value *= -1;
	}
	data = new cell_type[capacity];
	if (value == 0)
	{
		this->push_back(0);
		return;
	}
	for (size_t i = 0; value > 0; i++)
	{
		this->push_back(value % 10);
		value /= 10;
	}
}

BigInt::BigInt(const BigInt& number) 
	: size(number.size)
	, isNegative(number.isNegative)
	, capacity(number.capacity)
{
	data = new cell_type[capacity];
	memcpy(data, number.data, size);
}

BigInt::BigInt(BigInt&& number) 
	: size(number.size)
	, isNegative(number.isNegative)
	, capacity(number.capacity)
	, data(number.data)
{
	number.data = nullptr;
}

BigInt& BigInt::operator=(BigInt&& number)
{
	if (this == &number)
		return *this;
	size = number.size;
	isNegative = number.isNegative;
	capacity = number.capacity;
	delete[] data;
	data = number.data;
	number.data = nullptr;
	return *this;
}

void BigInt::push_back(cell_type element)
{
	data[size++] = element;
	if (capacity == size)
		this->allocate();
}

cell_type BigInt::pop()
{
	return data[--size];
}

void BigInt::push_front(cell_type element)
{
	for (size_t i = size; i > 0; i--)
		data[i] = data[i - 1];
	size++;
	if (capacity == size)
		this->allocate();
	data[0] = element;
}

void BigInt::allocate()
{
	capacity *= 2;
	cell_type* new_data = new cell_type[capacity];
	memcpy(new_data, data, size);
	delete[] data;
	data = new_data;
}

void BigInt::check_zero()
{
	if (size == 1 && data[0] == 0)
		isNegative = false;
}

void BigInt::delete_zero()
{
	for (size_t i = size - 1; i != 0; i--)
	{
		if (data[i] > 0)
			break;
		size--;
	}
}

BigInt& BigInt::operator=(const BigInt& number)
{
	if (this == &number)
		return *this;
	size = number.size;
	capacity = number.capacity;
	isNegative = number.isNegative;
	delete[] data;
	data = new cell_type[capacity];
	memcpy(data, number.data, size);
	return *this;
}

BigInt::~BigInt()
{
	delete[] data;
}

std::ostream& operator<<(std::ostream& out, const BigInt& value)
{
	if (value.isNegative)
		out << '-';
	for (int i = value.size - 1; i != -1; i--)
		out << static_cast<cell_type>('0' + value.data[i]);
	return out;
}

bool BigInt::operator==(const BigInt& number) const
{
	if (size != number.size || isNegative != number.isNegative)
		return false;
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] != number.data[i])
			return false;
	}
	return true;
}

bool BigInt::operator!=(const BigInt& number) const
{
	return !this->operator==(number);
}

bool BigInt::operator<(const BigInt& number) const
{
	if (isNegative != number.isNegative)
		return isNegative;
	// now sign_1 == sign_2
	if (size > number.size)
		return isNegative;
	else if (size < number.size)
		return !isNegative;
	// now sign_1 == sign_2 && len_1 == len_2
	for (int i = size - 1; i != -1; i--)
	{
		if (data[i] > number.data[i])
			return isNegative;
		else if (data[i] < number.data[i])
			return !isNegative;
	}
	return false;
}

bool BigInt::operator>(const BigInt& number) const
{
	if (isNegative != number.isNegative)
		return !isNegative;
	// now sign_1 == sign_2
	if (size < number.size)
		return isNegative;
	else if (size > number.size)
		return !isNegative;
	// now sign_1 == sign_2 && len_1 == len_2
	for (int i = size - 1; i != -1; i--)
	{
		if (data[i] < number.data[i])
			return isNegative;
		else if (data[i] > number.data[i])
			return !isNegative;
	}
	return false;
}

bool BigInt::operator<=(const BigInt& number) const
{
	return !this->operator>(number);
}

bool BigInt::operator>=(const BigInt& number) const
{
	return !this->operator<(number);
}

BigInt BigInt::operator-() const
{
	BigInt number(*this);
	number.isNegative = !isNegative;
	number.check_zero();
	return number;
}

BigInt BigInt::abs() const
{
	BigInt tmp = *this;
	tmp.isNegative = false;
	return tmp;
}

BigInt BigInt::operator+(const BigInt& number) const
{
	if (isNegative != number.isNegative)
	{
		if (isNegative)
			// num - (-result)
			return number - this->abs();
		else
			// result - (-num)
			return *this - number.abs();
	}
	BigInt result(*this);
	for (size_t i = result.size; i < number.size; i++)
		result.push_back(0);
	cell_type to_next = 0;
	for (size_t i = 0; i < number.size; i++)
	{
		cell_type sum = result.data[i] + number.data[i] + to_next;
		result.data[i] = sum % 10;
		to_next = sum / 10;
	}
	for (size_t i = number.size; i < result.size; i++)
	{
		cell_type sum = result.data[i] + to_next;
		result.data[i] = sum % 10;
		to_next = sum / 10;
	}
	if (to_next > 0)
		result.push_back(to_next);
	result.delete_zero();
	result.check_zero();
	return result;
}

BigInt BigInt::operator-(const BigInt& number) const
{
	if (isNegative != number.isNegative)
	{
		if (isNegative)
			// -(-result + number)
			return -(this->abs() + number);
		else
			// result + (-num)
			return *this + number.abs();
	}
	if (isNegative) // sign_1 = -, sign_2 = -
		// (-result) - (-number) = number + (-result)
		return number.abs() + *this;
	if (*this < number) // sign_1 = +, sign_2 = +
		// -(num - result)
		return -(number - *this);
	BigInt result(*this);
	cell_type to_next = 0;
	for (size_t i = 0; i < number.size; i++)
	{
		cell_type difference = result.data[i] - number.data[i] - to_next;
		if (difference < 0)
		{
			result.data[i] = difference + 10;
			to_next = 1;
		}
		else
		{
			result.data[i] = difference;
			to_next = 0;
		}
	}
	for (size_t i = number.size; i < result.size; i++)
	{
		cell_type difference = result.data[i] - to_next;
		if (difference < 0)
		{
			result.data[i] = difference + 10;
			to_next = 1;
		}
		else
		{
			result.data[i] = difference;
			to_next = 0;
		}
	}
	result.delete_zero();
	result.check_zero();
	return result;
}

BigInt BigInt::operator*(const BigInt& number) const
{
	BigInt result;
	for (size_t i = 0; i < number.size; i++)
	{
		BigInt aux;
		aux.pop();
		cell_type to_next = 0;
		for (size_t j = 0; j < i; j++)
			aux.push_back(0);
		for (size_t j = 0; j < size; j++)
		{
			cell_type multiplication = number.data[i] * data[j] + to_next;
			aux.push_back(multiplication % 10);
			to_next = multiplication / 10;
		}
		if (to_next > 0)
			aux.push_back(to_next);
		result = result + aux;
	}
	result.isNegative = isNegative != number.isNegative;
	result.delete_zero();
	result.check_zero();
	return result;
}

cell_type BigInt::binSearch(const BigInt &dividend, const BigInt &divisor) const
{
	// result = max(x : divisor * x <= dividend)
	cell_type result = 0;
	cell_type min = 0;
	cell_type max = 10;

	while (min <= max)
	{
		cell_type curr = (max + min) / 2;
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
	aux.pop();
	BigInt abs_number = number.abs();
	for (size_t i = 0; i < size; i++)
	{
		aux.push_front(data[size - 1 - i]);
		aux.delete_zero();
		cell_type div = binSearch(aux, abs_number);
		result.push_front(div);
		aux = aux - abs_number * BigInt(div);
	}
	result.delete_zero();
	result.isNegative = isNegative != number.isNegative;
	result.check_zero();
	return result;
}