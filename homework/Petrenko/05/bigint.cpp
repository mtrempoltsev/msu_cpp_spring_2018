#include <iostream>
#include "bigint.h"

std::pair<uint8_t, bool> modulo_addc(uint8_t a, uint8_t b) {
    uint8_t ans = (a + b) % BigInt::base;
    return {ans, ans < a};
};

std::pair<uint8_t, bool> modulo_subb(uint8_t a, uint8_t b) {
    if(a < b)
        return {a + BigInt::base - b, true};
    else
        return {a - b, false};
};

void BigInt::widen() {
    uint8_t * new_data = new uint8_t[2 * max_size]();
    std::copy(data, data + real_size, new_data);
    delete[] data;
    data = new_data;
    max_size *= 2;
}

std::pair<BigInt, BigInt> BigInt::divmod(const BigInt & other) const {
    if(this->abs() < other.abs()) {
        return {0, this->negative ? other - *this : *this};
    }
    size_t power = this->real_size - other.real_size;
    BigInt dividend = this->abs();
    BigInt divisor = other.abs();
    BigInt div = 0, ctr;
    while(power != 0) {
        ctr = 0;
        BigInt divisor_pow = divisor.base_pow(power);
        while(dividend >= divisor_pow) {
            dividend -= divisor_pow;
            ++ctr;
        }
        div += ctr.base_pow(power);
        --power;
    }
    ctr = 0;
    while(dividend >= divisor) {
        dividend -= divisor;
        ++ctr;
    }
    div += ctr;
    div.negative = this->negative != other.negative;
    return {div, this->negative ? other - dividend : dividend};
}

BigInt::BigInt(int64_t v)
        : data(new uint8_t[BigInt::min_size]()),
          real_size(0),
          max_size(BigInt::min_size),
          negative(false)
{
    if(v < 0) {
        negative = true;
        v = -v;
    }
    while(v > 0) {
        data[real_size] = v % 100;
        v /= 100;
        ++real_size;
    }
}

BigInt::BigInt(const BigInt &other)
        : data(new uint8_t[other.max_size]()),
          real_size(other.real_size),
          max_size(other.max_size),
          negative(other.negative)
{
    std::copy(other.data, other.data + real_size, data);
}

BigInt::BigInt(BigInt && other)
        : data(other.data),
          real_size(other.real_size),
          max_size(other.max_size),
          negative(other.negative)
{
    other.data = nullptr;
}

BigInt::~BigInt() {
    delete[] data;
}

BigInt & BigInt::normalize() {
    while(real_size > 0 && data[real_size - 1] == 0) {
        real_size--;
    }
    if(real_size == 0) negative = false;
    return *this;
}

BigInt & BigInt::negate() {
    this->negative = !this->negative;
    return *this;
}

BigInt BigInt::abs() const {
    BigInt res(*this);
    res.negative = false;
    return res;
}

BigInt BigInt::base_pow(size_t power) const {
    if(power == 0) {
        return *this;
    } else {
        BigInt ret(*this);
        ret.max_size = ret.real_size = this->real_size + power;
        uint8_t * data = new uint8_t[ret.max_size]();
        for(size_t i = power; i < ret.max_size; ++i) {
            data[i] = this->data[i - power];
        }
        delete[] ret.data;
        ret.data = data;
        return ret;
    }
}

BigInt BigInt::operator-() const {
    BigInt ans(*this);
    return ans.negate();
}

bool BigInt::operator==(const BigInt & other) const {
    size_t i = 0;
    for( ; i < std::min(this->real_size, other.real_size); ++i) {
        if(this->data[i] != other.data[i]) return false;
    }
    for(size_t j = i; j < this->real_size; ++j) {
        if(this->data[j] != 0) return false;
    }
    for(size_t j = i; j < other.real_size; ++j) {
        if(other.data[j] != 0) return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt & other) const {
    return !this->operator==(other);
}

bool BigInt::operator<=(const BigInt & other) const {
    if(this->negative != other.negative) {
        if(this->negative)
            return true;
        else
            return false;
    } else {
        if(this->negative) {
            if(this->real_size > other.real_size)
                return true;
            else if(this->real_size < other.real_size)
                return false;
            else {
                for(ssize_t i = this->real_size - 1; i >= 0 ; --i) {
                    if(this->data[i] > other.data[i])
                        return true;
                    else if(this->data[i] < other.data[i])
                        return false;
                }
                return this->data[0] >= other.data[0];
            }
        } else {
            if(this->real_size < other.real_size)
                return true;
            else if(this->real_size > other.real_size)
                return false;
            else {
                for(ssize_t i = this->real_size - 1; i >= 0; --i) {
                    if(this->data[i] < other.data[i])
                        return true;
                    else if(this->data[i] > other.data[i])
                        return false;
                }
                return this->data[0] <= other.data[0];
            }
        }
    }
}

bool BigInt::operator>=(const BigInt & other) const {
    return !this->operator<=(other) || this->operator==(other);
}

bool BigInt::operator<(const BigInt & other) const {
    return this->operator<=(other) && this->operator!=(other);
}

bool BigInt::operator>(const BigInt & other) const {
    return !this->operator<=(other);
}

BigInt BigInt::operator+(const BigInt & other) const {
    BigInt ans(*this);
    ans += other;
    return ans;
}

BigInt BigInt::operator-(const BigInt & other) const {
    BigInt ans(*this);
    ans -= other;
    return ans;
}

BigInt BigInt::operator*(const BigInt & other) const {
    BigInt ans(*this);
    ans *= other;
    return ans;
}

BigInt BigInt::operator/(const BigInt & other) const {
    BigInt ans(*this);
    ans /= other;
    return ans;
}

BigInt BigInt::operator%(const BigInt & other) const {
    BigInt ans(*this);
    ans %= other;
    return ans;
}

BigInt & BigInt::operator=(const BigInt & other) {
    if(&other == this)
        return *this;
    delete[] this->data;
    this->data = new uint8_t[other.real_size];
    std::copy(other.data, other.data + other.real_size, this->data);
    this->real_size = other.real_size;
    this->max_size = other.max_size;
    this->negative = other.negative;
    return * this;
}

BigInt & BigInt::operator=(BigInt && other) {
    if(&other == this)
        return *this;
    delete[] this->data;
    this->data = other.data;
    this->real_size = other.real_size;
    this->max_size = other.max_size;
    this->negative = other.negative;
    other.data = nullptr;
    return *this;
}

BigInt & BigInt::operator+=(const BigInt & other) {
    if(this->negative != other.negative)
        return this->operator-=(-other);

    if(std::max(this->real_size, other.real_size) + 1 >= this->max_size)
        this->widen();

    bool carry = false;
    bool new_carry;
    size_t i = 0;
    for(; i < std::min(this->real_size, other.real_size); ++i) {
        if(carry) {
            std::tie(this->data[i], new_carry) = modulo_addc(this->data[i], 1);
            carry = new_carry;
        }
        std::tie(this->data[i], new_carry) = modulo_addc(this->data[i], other.data[i]);
        carry = carry || new_carry;
    }
    for(size_t j = i; j < this->real_size; ++j) {
        if(carry)
            std::tie(this->data[j], carry) = modulo_addc(this->data[j], 1);
    }
    for(size_t j = i; j < other.real_size; ++j) {
        std::tie(this->data[j], carry) = modulo_addc(carry ? 1 : 0, other.data[j]);
    }
    this->real_size = std::max(this->real_size, other.real_size);
    if(carry) {
        this->data[this->real_size] = 1;
        this->real_size += 1;
    }
    return this->normalize();
}

BigInt & BigInt::operator-=(const BigInt & other) {
    if(this->negative != other.negative) {
        return this->operator+=(-other);
    }
    if(this->abs() < other.abs()) {
        *this = other.operator-(*this).negate();
        return *this;
    }
    size_t i = 0;
    bool borrow = false;
    bool new_borrow;
    for(; i < other.real_size; ++i) {
        if (borrow){
            std::tie(this->data[i], new_borrow) = modulo_subb(this->data[i], 1);
            borrow = new_borrow;
        }
        std::tie(this->data[i], new_borrow) = modulo_subb(this->data[i], other.data[i]);
        borrow = borrow || new_borrow;
    }
    for(; i < this->real_size; ++i) {
        std::tie(this->data[i], borrow) = modulo_subb(this->data[i], borrow ? 1 : 0);
    }
    return this->normalize();
}

BigInt & BigInt::operator*=(const BigInt & other) {
    if(this->is_null()) {
        return *this;
    } else if(other.is_null()) {
        this->real_size = 0;
        return *this;
    } else {
        size_t n = this->real_size, m = other.real_size;
        uint8_t *buff = new uint8_t[n + m]();
        for (size_t j = 0; j < m; ++j) {
            if (other.data[j] == 0) {
                buff[j] = 0;
                continue;
            }
            uint8_t k = 0;
            for (size_t i = 0; i < n; ++i) {
                uint16_t t = this->data[i] * other.data[j] + buff[i + j] + k;
                buff[i + j] = t % BigInt::base;
                k = t / BigInt::base;
            }
            buff[n + j] = k;
        }
        delete[] this->data;
        this->data = buff;
        this->negative = other.negative != this->negative;
        this->real_size = n + m;
        this->max_size = n + m;
        //this->normalize();
        return *this;
    }
}

BigInt & BigInt::operator/=(const BigInt & other) {
    return this->operator=(this->divmod(other).first);
}

BigInt & BigInt::operator%=(const BigInt & other) {
    return this->operator=(this->divmod(other).second);
}

const BigInt BigInt::operator++(int) {
    BigInt temp(*this);
    this->operator+=(1);
    return temp;
}

const BigInt BigInt::operator--(int) {
    BigInt temp(*this);
    this->operator-=(1);
    return temp;
}

BigInt & BigInt::operator++() {
    return this->operator+=(1);
}

BigInt & BigInt::operator--() {
    return this->operator-=(1);
}

std::ostream & operator<<(std::ostream & os, const BigInt & value) {
    if(value.real_size == 0)
        return os << '0';
    if(value.negative)
        os << '-';
    if(value.data[value.real_size - 1] >= 10)
        os << value.data[value.real_size - 1] / 10;
    os << value.data[value.real_size - 1] % 10;
    for(ssize_t i = value.real_size - 2; i >= 0; --i) {
        os << value.data[i] / 10 << value.data[i] % 10;
    }
    return os;
}

bool BigInt::is_null() const {
    return real_size == 0;
}
