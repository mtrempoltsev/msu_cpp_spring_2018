#include <iostream>


typedef char T;

class BigInt
{
private:
	T* data;
	size_t size = 0;
	bool isNegative = false;
	size_t sizeall = 32;
    void expand();
	T binDiv(const BigInt&, const BigInt&) const;
	void push_back(T element);
	void push_front(T element);
	T pop();	
	void delete_zero();
	void check_zero();
public:
	BigInt();
	BigInt(const BigInt&);
	BigInt(BigInt&&);
	BigInt(int);
	~BigInt();
	BigInt abs() const;
	friend std::ostream& operator<<(std::ostream& out, const BigInt&);
	friend std::istream& operator>>(std::istream& in, BigInt&);
	BigInt& operator=(const BigInt&);
	BigInt& operator=(BigInt&&);
	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;
	BigInt operator-() const;	
	BigInt operator+(const BigInt&) const;
	BigInt operator-(const BigInt&) const;
	BigInt operator*(const BigInt&) const;
	BigInt operator/(const BigInt&) const;	
};


BigInt::BigInt()
{
	data = new T[sizeall];
	push_back(0);
}

BigInt::BigInt(int v)
{
	if (v < 0)
	{
		isNegative = true;
		v *= -1;
	}
	data = new T[sizeall];
	if (v == 0)
	{
		push_back(0);
		return;
	}
	for (size_t i = 0; v > 0; i++)
	{
		push_back(v % 10);
		v /= 10;
	}	
}

BigInt::BigInt(const BigInt& n)
	: size(n.size)
	, isNegative(n.isNegative)
	, sizeall(n.sizeall)
{
	data = new T[sizeall];
	for (size_t i = 0; i < size; i++) data[i] = n.data[i];	
}

BigInt::BigInt(BigInt&& n)
	: size(n.size)
	, isNegative(n.isNegative)
	, sizeall(n.sizeall)
{
	data = n.data;
	n.data = nullptr;
}

BigInt& BigInt::operator=(BigInt&& n)
{
	if (&n == this)
		return *this;
	size = n.size;
	isNegative = n.isNegative;
	sizeall = n.sizeall;
	delete[] data;
	data = n.data;
	n.data = nullptr;
	return *this;
}

void BigInt::push_back(T element)
{
	data[size++] = element;
	if (sizeall == size)
		this->expand();
}



void BigInt::push_front(T element)
{
	for (size_t i = size; i > 0; i--)
		data[i] = data[i - 1];
	size++;
	if (sizeall == size)
		this->expand();
	data[0] = element;
}

T BigInt::pop()
{
	return data[--size];
}

void BigInt::expand()
{
	sizeall *= 2;
	T* new_data = new T[sizeall];
	for (size_t i = 0; i < size; i++) new_data[i] = data[i];	
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
	for (size_t i = size - 1; i > 0; i--)
	{
		if (data[i] > 0)
			break;
		size--;
	}
}

BigInt& BigInt::operator=(const BigInt& n)
{
	if (this == &n)
		return *this;
	size = n.size;
	sizeall = n.sizeall;
	isNegative = n.isNegative;
	delete[] data;
	data = new T[sizeall];
	for (size_t i = 0; i < size; i++) data[i] = n.data[i];	
	return *this;
}

BigInt::~BigInt()
{
	delete[] data;
}

std::ostream& operator<<(std::ostream& out, const BigInt& v)
{
	if (v.isNegative)
		out << '-';
	for (int i = v.size - 1; i >= 0; i--)
		out << (T)('0' + v.data[i]);
	return out;
}

std::istream& operator>>(std::istream& in, BigInt& v)
{
	T* a = new T[5];
	in.getline(a, 5);
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << a[i] << std::endl;
		v.push_back((int)(a[i]));
	}
	
	return in;
}

bool BigInt::operator==(const BigInt& n) const
{
	if (isNegative != n.isNegative || size != n.size)
		return false;
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] != n.data[i])
			return false;
	}
	return true;
}

bool BigInt::operator!=(const BigInt& n) const
{
	return !this->operator==(n);
}

bool BigInt::operator<(const BigInt& n) const
{
	if (isNegative != n.isNegative)
		return isNegative;
	
	if (size > n.size)
		return isNegative;
	else if (size < n.size)
		return !isNegative;
	
	for (int i = size - 1; i >= 0; i--)
	{
		if (data[i] > n.data[i])
			return isNegative;
		else if (data[i] < n.data[i])
			return !isNegative;
	}
	return false;
}

bool BigInt::operator>(const BigInt& n) const
{
	if (isNegative != n.isNegative)
		return !isNegative;
	
	if (size < n.size)
		return isNegative;
	if (size > n.size)
		return !isNegative;
	
	for (int i = size - 1; i >= 0; i--)
	{
		if (data[i] < n.data[i])
			return isNegative;
		else if (data[i] > n.data[i])
			return !isNegative;
	}
	return false;
}

bool BigInt::operator<=(const BigInt& n) const
{
	return !this->operator>(n);
}

bool BigInt::operator>=(const BigInt& n) const
{
	return !this->operator<(n);
}

BigInt BigInt::operator-() const
{
	BigInt num = *this;
	num.isNegative = !isNegative;
	num.check_zero();
	return num;
}

BigInt BigInt::abs() const
{
	BigInt temp = *this;
	temp.isNegative = false;
	return temp;
}

BigInt BigInt::operator+(const BigInt& n) const
{
	if (isNegative != n.isNegative)
	{
		if (isNegative)
			
			return n - abs();
		else
			
			return *this - n.abs();
	}
	BigInt res = *this;
	for (size_t i = res.size; i < n.size; i++)
		res.push_back(0);
	T d = 0;
	for (size_t i = 0; i < n.size; i++)
	{
		T sum = res.data[i] + n.data[i] + d;
		res.data[i] = sum % 10;
		d = sum / 10;
	}
	for (size_t i = n.size; i < res.size; i++)
	{
		T sum = res.data[i] + d;
		res.data[i] = sum % 10;
		d = sum / 10;
	}
	if (d > 0)
		res.push_back(d);
    res.delete_zero();
	res.check_zero();
	return res;
}

BigInt BigInt::operator-(const BigInt& n) const
{
	if (isNegative != n.isNegative)
	{
		if (!isNegative)
			return (*this + n.abs());
		else                      
			return -(abs() + n);
			
	}
	if (isNegative) 					
		return n.abs() + *this;
	if (*this < n) 						
		return -(n - *this);
	BigInt res = *this;
	T d = 0;
	for (size_t i = 0; i < n.size; i++)
	{
		T dif = res.data[i] - n.data[i] - d;
		if (dif < 0)
		{
			res.data[i] = dif + 10;
			d = 1;
		}
		else
		{
			res.data[i] = dif;
			d = 0;
		}
	}
	for (size_t i = n.size; i < res.size; i++)
	{
		T dif = res.data[i] - d;
		if (dif < 0)
		{
			res.data[i] = dif + 10;
			d = 1;
		}
		else
		{
			res.data[i] = dif;
			d = 0;
		}
	}
	res.delete_zero();
	res.check_zero();
	return res;
}

BigInt BigInt::operator*(const BigInt& n) const
{
	BigInt res;
	for (size_t i = 0; i < n.size; i++)
	{
		BigInt temp;
	    temp.pop();
		T d = 0;
		for (size_t j = 0; j < i; j++)
			temp.push_back(0);
		for (size_t j = 0; j < size; j++)
		{
			T mult = n.data[i] * data[j] + d;
		    temp.push_back(mult % 10);
			d = mult / 10;
		}
		if (d > 0)
			temp.push_back(d);
		res = res + temp;
	}
	res.isNegative = isNegative != n.isNegative;
	res.delete_zero();
	res.check_zero();
	return res;
}

T BigInt::binDiv(const BigInt &dividend, const BigInt &divisor) const
{
	T res = 0, min = 0, max = 10;
	
	while (min <= max)
	{
		T c = (max + min) / 2;
		BigInt tek(c);
		if (tek * divisor <= dividend)
		{
			res = c;
			min = c + 1;
		}
		else
			max = c - 1;
	}
	return res;
}

BigInt BigInt::operator/(const BigInt& n) const
{
	BigInt res, temp;	
	temp.pop();
	BigInt abs_number = n.abs();
	for (size_t i = 0; i < size; i++)
	{
		temp.push_front(data[size - 1 - i]);
		temp.delete_zero();
		T div = binDiv(temp, abs_number);
		res.push_front(div);
		temp = temp - abs_number * BigInt(div);
	}
	res.delete_zero();
	res.isNegative = isNegative != n.isNegative;
	res.check_zero();
	return res;
}


int main()
{
	BigInt a(120);
	BigInt b(10);
	BigInt c(a - b);
	BigInt d(a * b);
	BigInt dd(a / b);
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << dd << std::endl;
	return 0;
}
