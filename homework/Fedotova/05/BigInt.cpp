#include "BigInt.h"
#include <iomanip>

BigInt::BigInt(): sign(false), size(1) {
    data = new unsigned long[size]();
    data[0] = 0;
}

BigInt::BigInt(const BigInt& x): sign(x.sign), size(x.size) {
    data = new unsigned long[size]();
    std::copy(x.data, x.data + size, data);
}

BigInt::BigInt(long x): sign(x < 0) {
    long a = x / (2 * !sign - 1);
    if (a >= NUMBER_SIZE) {
        size = 2;
        data = new unsigned long[size]();
        data[0] = a % NUMBER_SIZE;
        data[1] = a / NUMBER_SIZE;
    }
    else {
        size = 1;
        data = new unsigned long[size]();
        data[0] = a;
    }
}

BigInt::BigInt(BigInt&& x) {
    size = x.size;
    sign = x.sign;
    data = x.data;
    x.data = nullptr;
}

BigInt::~BigInt() {
    delete[] data;
}

BigInt& BigInt::operator=(const BigInt& x) {
    if (this == &x)
        return *this;
    delete[] data;
    sign = x.sign;
    size = x.size;
    data = new unsigned long[size]();
    std::copy(x.data, x.data + size, data);
    return *this;
}

BigInt& BigInt::operator=(BigInt&& x) {
    if (this == &x)
        return *this;
    delete[] data;
    sign = x.sign;
    size = x.size;
    data = x.data;
    x.data = nullptr;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const BigInt& x) {
    if (x.sign)
            out << '-';
    out << x.data[x.size - 1];
    for (int i = x.size - 2; i >= 0; i--) {
        out << std::setfill('0');
        out << std::setw(NUMBER_POR) << x.data[i];
    }
    return out;
}

BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    if (size == 1 && data[0] == 0)
        return tmp;
    tmp.sign = !tmp.sign;
    return tmp;
}

int BigInt::compare_abs(const BigInt& other) const {
    for (int i = size - 1; i >= 0; i--) {
        if (data[i] > other.data[i]) {
            return 1;
        }
        if (data[i] < other.data[i]) {
            return -1;
        }
    }
    return 0;
}

bool BigInt::operator==(const BigInt& other) const {
    if (size != other.size || sign != other.sign)
        return false;
    if (compare_abs(other) == 0)
        return true;
    return false;
}

bool BigInt::operator>=(const BigInt& other) const {
    if (sign && other.sign)
        return - *this < - other;
    if (sign && !other.sign)
        return false;
    if (!sign && other.sign)
        return true;
    if (size > other.size)
        return true;
    if (size < other.size)
        return false;
    if (compare_abs(other) >= 0)
        return true;
    return false;
}

bool BigInt::operator<=(const BigInt& other) const {
    if (sign && other.sign)
        return - *this > - other;
    if (sign && !other.sign)
        return true;
    if (!sign && other.sign)
        return false;
    if (size > other.size)
        return false;
    if (size < other.size)
        return true;
    if (compare_abs(other) <= 0)
        return true;
    return false;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !operator==(other);
}

bool BigInt::operator>(const BigInt& other) const {
    return !operator<=(other);
}

bool BigInt::operator<(const BigInt& other) const {
    return !operator>=(other);
}

void BigInt::adapt_sizes(size_t s) {
    if (s <= size)
        return;
    unsigned long *new_data = new unsigned long[s]();
    std::copy(data, data + size, new_data);
    delete[] data;
    data = new_data;
    size = s;
}

void BigInt::correct_size() {
    size_t s = 1;
    for (size_t i = 0; i < size; i++)
        if (data[i] != 0) {
            s = i + 1;
        }
    unsigned long *new_data = new unsigned long[s];
    std::copy(data, data + s, new_data);
    delete[] data;
    data = new_data;
    size = s;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (sign)
        return other - (-*this);
    if (other.sign)
        return *this - (-other);
    
    BigInt res, A(*this), B(other);
    A.adapt_sizes(B.size);
    B.adapt_sizes(A.size);
    size_t s = A.size;
    res.adapt_sizes(s + 1);
    
    unsigned long take = 0;
    for (int i = 0; i < s; i++) {
        res.data[i] = A.data[i] + B.data[i];
        res.data[i] += take;
        take = res.data[i] / NUMBER_SIZE;
        res.data[i] %= NUMBER_SIZE;
    }
    res.data[s] = take;
    
    res.correct_size();
    return res;
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (sign)
        return -(other + (-*this));
    if (other.sign)
        return *this + (-other);
    if (*this < other)
        return -(other - *this);
    
    BigInt res, A(*this), B(other);
    A.adapt_sizes(B.size);
    B.adapt_sizes(A.size);
    size_t s = A.size;
    res.adapt_sizes(s);
    
    unsigned long take = 0;
    for (int i = 0; i < s; i++) {
        B.data[i] += take;
        take = 0;
        if (A.data[i] < B.data[i]) {
            take = 1;
            A.data[i] += NUMBER_SIZE;
        }
        res.data[i] = A.data[i] - B.data[i];
    }
        
    res.correct_size();
    return res;
}

BigInt BigInt::operator*(const BigInt& other) const {
    if (sign)
        return -(other * (-*this));
    if (other.sign)
        return -(*this * (-other));
    
    BigInt res, A(*this), B(other), C;
    C.adapt_sizes(A.size + B.size);
    
    unsigned long take = 0;
    for (int i = 0; i < A.size; i++) {
        take = 0;
        for (size_t j = 0; j < B.size; j++) {
            C.data[i + j] = (A.data[i] * B.data[j] + take) % NUMBER_SIZE;
            take = (A.data[i] * B.data[j] + take) / NUMBER_SIZE;
        }
        C.data[i + B.size] = take;
        res = res + C;
        C = 0;
        C.adapt_sizes(A.size + B.size);
    }
        
    return res;
}

size_t bin_search(const BigInt& C, const BigInt& B) {
    unsigned long left = 0, right = NUMBER_SIZE - 1, mid;
    while (left < right) {
        mid = (right + left) / 2;
        if (B * (mid + 1) > C && B * mid <= C)
            return mid;
        else if (B * mid <= C) 
            left = mid + 1;
        else
            right = mid;
    }
    if (B * (left + 1) > C && B * left <= C)
        return left;
    else
        return -1;
}

BigInt BigInt::operator/(const BigInt& other) const {
    if (sign)
        return -((-*this) / other);
    if (other.sign)
        return -(*this / (-other));
    if (*this < other)
        return 0;
    
    BigInt res, A(*this), B(other), C;
    C.adapt_sizes(A.size);
    res.adapt_sizes(A.size - B.size + 1);
    size_t s = A.size - B.size + 1;
    size_t step = A.size - B.size ;
    for (size_t i = step; i < A.size; i++)
        C.data[i - step] = A.data[i];
    C.correct_size();
    if (C < B) {
        step--;
        C = C * NUMBER_SIZE + A.data[step];
    }
    
    unsigned long num;
    num = bin_search(C, B);
    res.data[step] = num;
    
    while (step > 0) {
        step--;
        C = (C - B * num) * NUMBER_SIZE + A.data[step];
        num = bin_search(C, B);
        res.data[step] = num;
    }
    res.correct_size();    
    return res;
}
