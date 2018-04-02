#pragma once
#include <iostream>

class BigInt
{
private:
    const static unsigned long NUMBER_SIZE = 1000000000;
    const static unsigned long NUMBER_POR = 9;
    
    size_t size;
    unsigned long *data;
    bool sign;
    
    int compare_abs(const BigInt& other) const;
    void adapt_sizes(size_t s);
    void correct_size();
    size_t bin_search(const BigInt& B) const;
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
