#pragma once
#include<iostream>
class BigInt
{
private:
	bool is_positive;
	size_t size;
	char* num =nullptr;
public:
	BigInt();
	BigInt(int64_t);
	BigInt(const BigInt&);
	BigInt(BigInt&&);
	BigInt operator-() const;
	~BigInt();
	BigInt operator+(const BigInt& other) const;
	BigInt operator-(const BigInt& other) const;
	BigInt operator*(const BigInt& other) const;
	BigInt operator/(const BigInt& other) const;
	bool operator>(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
	bool operator==(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator>=(const BigInt& other) const;
	bool operator<=(const BigInt& other) const;
	void operator=(const BigInt&);
	void operator=(BigInt&&);
	void operator=(const int&);
	void resize(size_t);
	void fill_zeros();
	void set_sign(bool);
	friend std::ostream& operator<<(std::ostream& out, const BigInt& number);
};

