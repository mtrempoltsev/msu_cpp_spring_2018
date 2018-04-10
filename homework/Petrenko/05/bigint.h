#ifndef SPHERE_01_C_HW05_BIGINT_H
#define SPHERE_01_C_HW05_BIGINT_H

#include <ostream>
#include <tuple>

class BigInt {
    static const size_t min_size = 21;
    static const size_t base = 100;

    uint8_t * data;
    size_t real_size;
    size_t max_size;
    bool negative;

    void widen();
    std::pair<BigInt, BigInt> divmod(const BigInt & other) const;
public:
    BigInt(int64_t v = 0);
    BigInt(const BigInt & other);
    BigInt(BigInt && other);

    ~BigInt();

    bool is_null() const;

    BigInt & normalize();

    BigInt & negate();
    BigInt abs() const;

    BigInt base_pow(size_t power) const; // for a given BigInt n returns n * base ^ power;

    BigInt operator-() const;

    bool operator==(const BigInt & other) const;
    bool operator!=(const BigInt & other) const;
    bool operator<=(const BigInt & other) const;
    bool operator>=(const BigInt & other) const;
    bool operator<(const BigInt & other) const;
    bool operator>(const BigInt & other) const;

    BigInt operator+(const BigInt & other) const;
    BigInt operator-(const BigInt & other) const;
    BigInt operator*(const BigInt & other) const;
    BigInt operator/(const BigInt & other) const;
    BigInt operator%(const BigInt & other) const;

    BigInt & operator=(const BigInt & other);
    BigInt & operator=(BigInt && other);
    BigInt & operator+=(const BigInt & other);
    BigInt & operator-=(const BigInt & other);
    BigInt & operator*=(const BigInt & other);
    BigInt & operator/=(const BigInt & other);
    BigInt & operator%= (const BigInt & other);

    const BigInt operator++(int);
    const BigInt operator--(int);
    BigInt & operator++();
    BigInt & operator--();

    friend std::ostream & operator<<(std::ostream & os, const BigInt & value);
    friend std::pair<uint8_t, bool> modulo_addc(uint8_t a, uint8_t b);
    friend std::pair<uint8_t, bool> modulo_subb(uint8_t a, uint8_t b);
};

#endif //SPHERE_01_C_HW05_BIGINT_H
