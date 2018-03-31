
#pragma once
#include <iomanip>
#define BIN_SIZE 1000000000
#define BASE 9

class BigInt
{
private:
    size_t _bins_count;
    unsigned long *_bins;
    bool sign;

    int compare_abs(const BigInt& other) const;
    void adapt_sizes(size_t s);
    void correct_size();
public:
    BigInt();
    BigInt(const BigInt& other);
    BigInt(long other);
    BigInt(BigInt&& other);
    ~BigInt();

		friend std::ostream& operator<<(std::ostream& out, const BigInt& other);

    BigInt& operator=(const BigInt& other);
    BigInt& operator=(BigInt&& other);

		bool operator==(const BigInt& other) const;
		bool operator>=(const BigInt& other) const;
		bool operator<=(const BigInt& other) const;
		bool operator!=(const BigInt& other) const;
		bool operator>(const BigInt& other) const;
		bool operator<(const BigInt& other) const;

    BigInt operator-() const;
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
};

BigInt::BigInt(): sign(true), _bins_count(1) {
    _bins = new unsigned long[_bins_count]();
    _bins[0] = 0;
}

BigInt::BigInt(const BigInt& other): sign(other.sign), _bins_count(other._bins_count) {
    _bins = new unsigned long[_bins_count]();
    std::copy(other._bins, other._bins + _bins_count, _bins);
}

BigInt::BigInt(long other): sign(other > 0) {
    unsigned long long a = other *(2*sign - 1) ;
    if (a >= BIN_SIZE) {
        _bins_count = 2;
        _bins = new unsigned long[_bins_count]();
        _bins[0] = a % BIN_SIZE;
				std::cout << "constr  0 " << _bins[0]<< '\n';
        _bins[1] = a / BIN_SIZE;
				std::cout << "constr 1  " << _bins[1]<< '\n';
    }
    else {
        _bins_count = 1;
        _bins = new unsigned long[_bins_count]();
        _bins[0] = a;
    }
}

BigInt::BigInt(BigInt&& other) {
    _bins_count = other._bins_count;
    sign = other.sign;
    _bins = other._bins;
    other._bins = nullptr;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (!num.sign)
            out << '-';
    out << num._bins[num._bins_count - 1];
		//std::cout << "" << '\n';
		//std::cout << "bins  1" << "  "<<num._bins[1]<<'\n';
    for (int i = num._bins_count - 2; i >= 0; i--) {
        out << std::setfill('0');
        out << std::setw(BASE) <<  num._bins[i];
				//std::cout << "" << '\n';
				//std::cout << "bins  " << i<< "  "<<num._bins[i]<<'\n';
    }
    return out;
}

BigInt::~BigInt() {
    delete[] _bins;
}

BigInt& BigInt::operator=(const BigInt& other) {
    if (this == &other)
        return *this;
    delete[] _bins;
    sign = other.sign;
    _bins_count = other._bins_count;
    _bins = new unsigned long[_bins_count]();
    std::copy(other._bins, other._bins + _bins_count, _bins);
    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) {
    if (this == &other)
        return *this;
    delete[] _bins;
    sign = other.sign;
    _bins_count = other._bins_count;
    _bins = other._bins;
    other._bins = nullptr;
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    if (_bins_count == 1 && _bins[0] == 0)
        return tmp;
    tmp.sign = !tmp.sign;
    return tmp;
}

int BigInt::compare_abs(const BigInt& other) const {
    for (int i = _bins_count - 1; i >= 0; i--) {
        if (_bins[i] > other._bins[i]) {
            return 1;
        }
        if (_bins[i] < other._bins[i]) {
            return -1;
        }
    }
    return 0;
}

bool BigInt::operator==(const BigInt& other) const {
    if (_bins_count != other._bins_count || sign != other.sign)
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
    if (_bins_count > other._bins_count)
        return true;
    if (_bins_count < other._bins_count)
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
    if (_bins_count > other._bins_count)
        return false;
    if (_bins_count < other._bins_count)
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
    if (s <= _bins_count)
        return;
    unsigned long *new_data = new unsigned long[s]();
    std::copy(_bins, _bins + _bins_count, new_data);
    delete[] _bins;
    _bins = new_data;
    _bins_count = s;
}

void BigInt::correct_size() {
    size_t s = 1;
    for (size_t i = 0; i < _bins_count; i++)
        if (_bins[i] != 0) {
            s = i + 1;
        }
    unsigned long *new_data = new unsigned long[s];
    std::copy(_bins, _bins + s, new_data);
    delete[] _bins;
    _bins = new_data;
    _bins_count = s;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (sign)
        return other - (-*this);
    if (other.sign)
        return *this - (-other);

    BigInt res, A(*this), B(other);
    A.adapt_sizes(B._bins_count);
    B.adapt_sizes(A._bins_count);
    size_t s = A._bins_count;
    res.adapt_sizes(s + 1);

    unsigned long take = 0;
    for (int i = 0; i < s; i++) {
        res._bins[i] = A._bins[i] + B._bins[i];
        res._bins[i] += take;
        take = res._bins[i] / BIN_SIZE;
        res._bins[i] %= BIN_SIZE;
    }
    res._bins[s] = take;

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
    A.adapt_sizes(B._bins_count);
    B.adapt_sizes(A._bins_count);
    size_t s = A._bins_count;
    res.adapt_sizes(s);

    unsigned long take = 0;
    for (int i = 0; i < s; i++) {
        B._bins[i] += take;
        take = 0;
        if (A._bins[i] < B._bins[i]) {
            take = 1;
            A._bins[i] += BIN_SIZE;
        }
        res._bins[i] = A._bins[i] - B._bins[i];
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
    C.adapt_sizes(A._bins_count + B._bins_count);

    unsigned long take = 0;
    for (int i = 0; i < A._bins_count; i++) {
        take = 0;
        for (size_t j = 0; j < B._bins_count; j++) {
            C._bins[i + j] = (A._bins[i] * B._bins[j] + take) % BIN_SIZE;
            take = (A._bins[i] * B._bins[j] + take) / BIN_SIZE;
        }
        C._bins[i + B._bins_count] = take;
        res = res + C;
        C = 0;
        C.adapt_sizes(A._bins_count + B._bins_count);
    }

    return res;
}
