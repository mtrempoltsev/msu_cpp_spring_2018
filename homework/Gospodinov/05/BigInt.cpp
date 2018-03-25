#include "BigInt.h"

BigInt::BigInt()
{
	data = new T[capacity];
}

BigInt::BigInt(const BigInt& number) : size(number.size), isNegative(number.isNegative), capacity(number.capacity)
{
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
		data[i] = number.data[i];
}

BigInt::BigInt(int value)
{
	if (value < 0)
	{
		isNegative = true;
		value *= -1;
	}
	data = new T[capacity];
	for (size_t i = 0; value > 0; i++)
	{
		this->push_back(value % 10);
		value /= 10;
	}
}

void BigInt::push_back(T element)
{
	data[size++] = element;
	if (capacity == size)
		this->allocate();
}

void BigInt::push_front(T element)
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
	T* new_data = new T[capacity];
	for (size_t i = 0; i < size; i++)
		new_data[i] = data[i];
	delete[] data;
	data = new_data;
}

BigInt& BigInt::operator=(const BigInt& number)
{
	if (this == &number)
		return *this;
	size = number.size;
	capacity = number.capacity;
	isNegative = number.isNegative;
	delete[] data;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
		data[i] = number.data[i];
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
		out << static_cast<T>('0' + value.data[i]);
	return out;
}

bool BigInt::operator==(const BigInt& number) const
{
	if (size != number.size || isNegative != isNegative)
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
	// знаки точно равны
	if (size > number.size)
		return isNegative;
	else if (size < number.size)
		return !isNegative;
	// равны знаки и длины
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
	// знаки точно равны
	if (size < number.size)
		return isNegative;
	else if (size > number.size)
		return !isNegative;
	// равны знаки и длины
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
	return number;
}

BigInt BigInt::operator+(const BigInt& number) const
{
	BigInt result(*this);
	BigInt num(number);
	if (result.isNegative != num.isNegative)
	{
		if (result.isNegative)
		{
			// num - (-result)
			result.isNegative = false;
			return num - result;
		}
		else
		{
			// result - (-num)
			num.isNegative = false;
			return result - num;
		}
	}
	for (size_t i = result.size; i < num.size; i++)
		result.push_back(0);
	T to_next = 0;
	for (size_t i = 0; i < result.size; i++)
	{
		T sum = result.data[i] + number.data[i] + to_next;
		result.data[i] = sum % 10;
		to_next = sum / 10;
	}
	if (to_next > 0)
		result.push_back(to_next);
	return result;
}

BigInt BigInt::operator-(const BigInt& number) const
{
	BigInt result(*this);
	BigInt num(number);
	if (result.isNegative != num.isNegative)
	{
		if (result.isNegative)
		{
			// -(-result + number)
			result.isNegative = false;
			BigInt sum = result + num;
			sum.isNegative = true;
			return sum;
		}
		else
		{
			// result + (-num)
			num.isNegative = false;
			return result + num;
		}
	}
	if (result.isNegative) // оба отрицательные
	{
		// -((-result) - (-number))
		result.isNegative = false;
		num.isNegative = false;
		BigInt difference = result - num;
		difference.isNegative = !difference.isNegative;
		return difference;
	}
	// оба положительные
	if (result < num)
	{
		// -(num - result)
		BigInt difference = num - result;
		difference.isNegative = true;
		return difference;
	}
	T to_next = 0;
	for (size_t i = 0; i < num.size; i++)
	{
		T difference = result.data[i] - num.data[i] - to_next;
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
	for (size_t i = num.size; i < result.size; i++)
	{
		T difference = result.data[i] - to_next;
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
	for (size_t i = result.size - 1; i != 0; i--)
	{
		if (result.data[i] > 0)
			break;
		result.size--;
	}
	return result;
}

BigInt BigInt::operator*(const BigInt& number) const
{
	BigInt result;
	for (size_t i = 0; i < number.size; i++)
	{
		BigInt aux;
		T to_next = 0;
		for (size_t j = 0; j < i; j++)
			aux.push_back(0);
		for (size_t j = 0; j < size; j++)
		{
			T multiplication = number.data[i] * data[j] + to_next;
			aux.push_back(multiplication % 10);
			to_next = multiplication / 10;
		}
		if (to_next > 0)
			aux.push_back(to_next);
		result = result + aux;
	}
	result.isNegative = isNegative != number.isNegative;
	if (result.size == 1 && result.data[0] == 0)
		result.isNegative = false;
	return result;
}

T BigInt::binSearch(const BigInt &dividend, const BigInt &divisor) const
{
	// result = max(x : divisor * x <= dividend)
	T result = 0;
	T min = 0;
	T max = 10;

	while (min <= max)
	{
		T curr = (max + min) / 2;
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
	for (size_t i = 0; i < size; i++)
	{
		aux.push_front(data[size - 1 - i]);
		T div = binSearch(aux, number);
		result.push_front(div);
		aux = aux - number * BigInt(div);
	}
	for (size_t i = result.size - 1; i != 0; i--)
	{
		if (result.data[i] > 0)
			break;
		result.size--;
	}
	result.isNegative = isNegative != number.isNegative;
	if (result.size == 1 && result.data[0] == 0)
		result.isNegative = false;
	return result;
}