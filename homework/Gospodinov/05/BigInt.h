#pragma once
#include <iostream>

typedef char cell_type;

class BigInt
{
private:
	cell_type* data;
	size_t size = 0;
	bool isNegative = false;
	size_t capacity = 32;

	cell_type binSearch(const BigInt& dividend, const BigInt& divisor) const;
	void push_back(cell_type element);
	void push_front(cell_type element);
	cell_type pop();
	void allocate();
	void delete_zero();
	void check_zero();
public:
	BigInt();
	BigInt(const BigInt& number);
	BigInt(BigInt&& number);
	BigInt(int64_t value);
	~BigInt();
	BigInt& operator=(const BigInt& number);
	BigInt& operator=(BigInt&& number);
	bool operator==(const BigInt& number) const;
	bool operator!=(const BigInt& number) const;
	bool operator<(const BigInt& number) const;
	bool operator>(const BigInt& number) const;
	bool operator<=(const BigInt& number) const;
	bool operator>=(const BigInt& number) const;
	BigInt operator-() const;
	BigInt abs() const;
	BigInt operator+(const BigInt& number) const;
	BigInt operator-(const BigInt& number) const;
	BigInt operator*(const BigInt& number) const;
	BigInt operator/(const BigInt& number) const;
	friend std::ostream& operator<<(std::ostream& out, const BigInt& number);
};