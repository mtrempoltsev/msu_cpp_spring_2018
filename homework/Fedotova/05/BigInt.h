#pragma once
#include <iostream>

#define NUMBER_SIZE 1000000000
#define NUMBER_POR 9

class BigInt
{
private:
    size_t size;
    unsigned long *data;
    bool sign;
    
    int compare_abs(const BigInt& other) const;
    void adapt_sizes(size_t s);
    void correct_size();
public:
    BigInt();
    BigInt(const BigInt& x);
    BigInt(long x);
    BigInt(BigInt&& x);
    ~BigInt();
    
    BigInt& operator=(const BigInt& x);
    BigInt& operator=(BigInt&& x);
    
    friend std::ostream& operator<<(std::ostream& out, const BigInt& x);
    
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator-() const;
    
    bool operator==(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
};
