#pragma once
#include<iostream>
class BigInt
{
private:
	bool is_positive;
	int size;
	short* num =nullptr;
public:
	BigInt();
	BigInt(int);
	BigInt(const short[],int,bool);
	BigInt(const BigInt&);
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
	void operator=(const int&);
	friend std::ostream& operator<<(std::ostream& out, const BigInt& number);
};

