#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <utility>
#include <ostream>
#include <iostream>
#include <algorithm>

class BigInt {
public:
    BigInt()
        : sign(0)
        , length(0)
        , dataSize(0)
        , data(nullptr) {
    }

    BigInt(const long long &x) {
        if (x == 0) {
            resize(1);
            data[0] = 0;
            sign = 0;
            length = 1;
        } else {
            sign = (x < 0 ? -1 : 1);
            resize(1);
            length = 0;
            long long y = std::abs(x);
            while (y > 0) {
                if (length == dataSize) {
                    resize(dataSize * 2);
                }
                data[length] = y % 10;
                y /= 10;
                ++length;
            }
        }
    }

    BigInt(const BigInt& other) {
        sign = other.sign;
        length = other.length;
        dataSize = other.dataSize;
        data = (int8_t*) calloc(dataSize, sizeof(int8_t));
        memcpy(data, other.data, length);
    }

    BigInt(BigInt&& other) 
        : sign(std::move(other.sign))
        , length(std::move(other.length))
        , dataSize(std::move(other.dataSize))
        , data(std::move(other.data)) {
    }

    BigInt abs(const BigInt& x) const {
        BigInt answer(x);
        if (answer.sign < 0) {
            answer.sign = 1;
        }
        return answer;
    }

    BigInt& operator=(const BigInt& other) {
        sign = other.sign;
        length = other.length;
        dataSize = other.dataSize;
        data = (int8_t*) calloc(dataSize, sizeof(int8_t));
        memcpy(data, other.data, length);
        return *this;
    }

    BigInt& operator=(BigInt&& other) {
        sign = std::move(other.sign);
        length = std::move(other.length);
        dataSize = std::move(other.dataSize);
        data = std::move(other.data);
        return *this;
    }

    bool operator!=(const BigInt& other) const {
        if (sign != other.sign) {
            return true;
        }
        if (length != other.length) {
            return true;
        }
        for (uint32_t i = 0; i < length; ++i) {
            if (data[i] != other.data[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const BigInt& other) const {
        return !operator!=(other);
    }

    bool operator<=(const BigInt& other) const {
        if (sign < other.sign) {
            return true;
        }
        if (sign > other.sign) {
            return false;
        }        
        if (length < other.length) {
            return true;
        }
        if (length > other.length) {
            return false;
        }
        for (uint32_t i = length; i > 0; --i) {
            if (data[i - 1] * sign < other.data[i - 1] * other.sign) {
                return true;
            }
            if (data[i - 1] * sign > other.data[i - 1] * other.sign) {
                return false;
            }
        }
        return true;
    }

    bool operator>=(const BigInt& other) const {
        if (sign < other.sign) {
            return false;
        }
        if (sign > other.sign) {
            return true;
        }        
        if (length < other.length) {
            return false;
        }
        if (length > other.length) {
            return true;
        }
        for (uint32_t i = length; i > 0; --i) {
            if (data[i - 1] * sign < other.data[i - 1] * other.sign) {
                return false;
            }
            if (data[i - 1] * sign > other.data[i - 1] * other.sign) {
                return true;
            }
        }
        return true;
    }

    bool operator<(const BigInt& other) const {
        return !operator>=(other);
    }

    bool operator>(const BigInt& other) const {
        return !operator<=(other);
    }

    BigInt operator-() const {
        BigInt answer(*this);
        answer.sign *= -1;
        return answer;
    }

    BigInt operator+(const BigInt& other) const {
        if (sign == 0) {
            BigInt answer(other);
            return answer;
        }
        if (other.sign == 0) {
            BigInt answer(*this);
            return answer;
        }
        if (sign == other.sign) {
            BigInt answer(*this), second(other);
            sum(answer, second);
            return answer;
        } else {
            BigInt a(abs(*this));
            BigInt b(abs(other));
            if (a >= b) {
                minus(a, b);
                if (a.sign != 0) {
                    a.sign = sign;
                }
                return a;
            } else {
                minus(b, a);
                if (b.sign != 0) {
                    b.sign = other.sign;
                }
                return b;
            }
        }
    }

    BigInt operator-(const BigInt& other) const {
        return operator+(-other);
    }

    BigInt operator*(const BigInt& other) const {
        BigInt answer(0);
        if ((*this) == 0 || other == 0) {
            return answer;
        }
        answer.sign = sign * other.sign;
        answer.resize(length + other.length);
        answer.length = length + other.length - 1;
        for (uint32_t i = 0; i < length; ++i) {
            int t = 0;
            for (uint32_t j = 0; j < other.length; ++j) {
                t += answer.data[i + j] + data[i] * other.data[j];
                answer.data[i + j] = t % 10;
                t /= 10;
            }
            uint32_t j = i + other.length;
            while (t > 0) {
                if (answer.length <= j) {
                    if (answer.length == answer.dataSize) {
                        answer.resize(answer.dataSize * 2);
                    }
                    ++answer.length;
                }
                t += answer.data[j];
                answer.data[j] = t % 10;
                t /= 10;
                ++j;
            }
        }
        return answer;
    }

    BigInt operator/(const BigInt& other) const {
        if (abs(*this) < abs(other)) {
            BigInt answer(0);
            return answer;
        }
        if (other == 0) {
            return 0;
        }
        BigInt a(*this), b, c;

        a.sign = 1;

        b.sign = 1;
        b.length = length;
        b.dataSize = dataSize;
        b.data = (int8_t*) calloc(length, sizeof(int8_t));
        memcpy(b.data + length - other.length, other.data, other.length);
        
        c.sign = sign * other.sign;
        c.length = length - other.length + 1;
        c.dataSize = c.length;
        c.data = (int8_t*) calloc(c.length, sizeof(int8_t));
        
        for (uint32_t i = 0; i < c.length; ++i) {
            while (a >= b) {
                BigInt d(a - b);
                a = d;
                ++c.data[c.length - i - 1];
            }
            for (uint32_t j = 1; j < b.length; ++j) {
                b.data[j - 1] = b.data[j];
            }
            --b.length;
        }
        while (c.length > 1 && c.data[c.length - 1] == 0) {
            --c.length;
        }
        if (c.length == 1 && c.data[0] == 0) {
            c.sign = 0;
        }
        if (c.length * 2 <= c.dataSize) {
            c.resize(c.dataSize);
        }
        return c;
    }

    BigInt operator%(const BigInt& other) const {
        return ((*this) - ((*this) / other) * other);
    }
private:
    int32_t sign;
    uint32_t length;
    uint32_t dataSize;
    int8_t* data = nullptr;
    
    void resize(uint32_t newSize) {
        int8_t* newData = (int8_t*) calloc(newSize, sizeof(int8_t));
        if (data != nullptr) {
            memcpy(newData, data, length);
            myFree(data);
        }
        dataSize = newSize;
        data = newData;
    }

    void myFree(int8_t* data) {
        if (data != nullptr) {
            free(data);
        }
    }

    void sum(BigInt& a, BigInt& b) const {
        if (b.dataSize > a.dataSize) {
            a.resize(b.dataSize);
        }
        a.length = std::max(a.length, b.length);
        a.resize(a.length);
        b.resize(a.length);
        int8_t t = 0;
        for (uint32_t i = 0; i < a.length; ++i) {
            t += a.data[i] + b.data[i];
            a.data[i] = t % 10;
            t /= 10;
        }
        if (t > 0) {
            if (a.dataSize == a.length) {
                a.resize(a.dataSize * 2);
                a.data[a.length] = t;
                ++a.length;
            }
        }
    }

    BigInt minus(BigInt& a, BigInt& b) const {
        a.length = std::max(a.length, b.length);
        a.resize(a.length);
        b.resize(a.length);
        int8_t t = 0;
        for (uint32_t i = 0; i < a.length; ++i) {
            t += a.data[i] - b.data[i];
            if (t < 0) {
                t += 10;
                a.data[i] = t;
                t = -1;
            } else {
                a.data[i] = t;
                t = 0;
            }
        }
        while (a.length > 1 && a.data[a.length - 1] == 0) {
            --a.length;
        }
        if (a.length == 1 && a.data[0] == 0) {
            a.sign = 0;
        }
        uint32_t s = a.dataSize;
        while (a.length * 2 <= s) {
            s /= 2;
        }
        if (a.dataSize != s) {
            a.resize(s);
        }
        a.resize(s);
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
};

std::ostream& operator<<(std::ostream& out, const BigInt& value) {
    if (value.sign == 0) {
        out << 0;
    } else {
        if (value.sign < 0) {
            out << "-";
        }
        for (uint32_t i = value.length; i > 0; --i) {
            out << static_cast<int>(value.data[i - 1]);
        }
    }
    return out;
}
