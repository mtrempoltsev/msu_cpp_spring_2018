#pragma once
#include <iostream>
#include <stdio.h>

struct ListItem
{
	ListItem *next, *prev;
	char digit;
	ListItem() { SetZero(); }
	void SetZero() { next = prev = NULL; digit = 0;}
};

class BigInt
{
private:
	bool isNegative;
	size_t length;
	ListItem *cur, *first, *last;
public:
	BigInt() { SetZero(); AddCur(0);}
	BigInt(const BigInt &copied) { CopyOnly(copied); }
	BigInt(int64_t);
	~BigInt() { Clean(); }
	void SetZero() { isNegative = false; cur = NULL; first = NULL; last = NULL; length = 0; }
	void Clean();
	void CopyOnly(const BigInt &);
	bool IsEmpty() { return (first == NULL) || (cur == NULL); }
	void GoToFirst() { if (cur != first) cur = first; }
	void GoToLast() { if (cur != last) cur = last; }
	void GoToNext() { cur = cur->next; }
	void GoToPrev() { cur = cur->prev; }
	void AddAfter(char);
	void AddCur(char);
	char GetCurrent() const { return cur->digit; }
	BigInt& operator= (const BigInt &other) { if (this != &other) { Clean(); CopyOnly(other); } return *this; }
	const BigInt operator+ (const BigInt&) const;
	const BigInt operator- (const BigInt&) const;
	const BigInt operator* (const BigInt&) const;
	const BigInt operator* (char) const;
	const BigInt operator/ (const BigInt&) const;
	BigInt& operator- ();
	bool operator == (const BigInt &) const;
	bool operator != (const BigInt &other) const { return !(*this == other); }
	bool operator > (const BigInt &) const;
	bool operator < (const BigInt &) const;
	bool operator <= (const BigInt &other) const { return (*this == other) || (*this < other); }
	bool operator >= (const BigInt &other) const { return (*this == other) || (*this > other); }
	friend std::ostream &operator << (std::ostream&, const BigInt&);
};
