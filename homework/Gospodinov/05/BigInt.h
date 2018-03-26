#pragma once
#include <iostream>

typedef char T;

class BigInt
{
private:
	T* data;
	size_t size = 0;
	bool isNegative = false;
	size_t capacity = 32;
public:
	BigInt();
	BigInt(const BigInt& number);
	BigInt(int value);
	~BigInt();
	void push_back(T element);
	void push_front(T element);
	void allocate();
	BigInt& operator=(const BigInt& number);
	bool operator==(const BigInt& number) const;
	bool operator!=(const BigInt& number) const;
	bool operator<(const BigInt& number) const;
	bool operator>(const BigInt& number) const;
	bool operator<=(const BigInt& number) const;
	bool operator>=(const BigInt& number) const;
	BigInt operator-() const;
	BigInt operator+(const BigInt& number) const;
	BigInt operator-(const BigInt& number) const;
	BigInt operator*(const BigInt& number) const;
	T binSearch(const BigInt &dividend, const BigInt &divisor) const;
	BigInt operator/(const BigInt& number) const;
	friend std::ostream& operator<<(std::ostream& out, const BigInt& number);
};