#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <limits>
#include <sstream>

class BigInt {
public:
    BigInt() : module_capacity(2), module_length(0), sign(1) {
        module = new unsigned int[module_capacity]();
    }

    BigInt(int value) : module_capacity(2), module_length(1), sign(1) {
        module = new unsigned int[module_capacity]();
        if (value < 0) {
            value *= -1;
            sign = -1;
        }
        module[0] = static_cast<unsigned int>(value);
        if (value == 0)
            module_length = 0;
    }

    BigInt(unsigned int value) : module_capacity(2), module_length(1), sign(1) {
        module = new unsigned int[module_capacity]();
        module[0] = value;
        if (value == 0)
            module_length = 0;
    }

    BigInt(long value) : module_capacity(2), module_length(2), sign(1) {
        module = new unsigned int[module_capacity]();
        if (value < 0) {
            value *= -1;
            sign = -1;
        }
        module[0] = static_cast<unsigned int>(value & static_cast<unsigned int>(-1));
        module[1] = static_cast<unsigned int>(value >> 32);
        if (module[1] == 0)
            module_length = 1;
        if (value == 0)
            module_length = 0;
    }

    BigInt(long long value) : module_capacity(2), module_length(2), sign(1) {
        module = new unsigned int[module_capacity]();
        if (value < 0) {
            value *= -1;
            sign = -1;
        }
        module[0] = static_cast<unsigned int>(value & static_cast<unsigned int>(-1));
        module[1] = static_cast<unsigned int>(value >> 32);
        if (module[1] == 0)
            module_length = 1;
        if (value == 0)
            module_length = 0;
    }

    BigInt(const BigInt& other) {
        module_capacity = other.module_capacity;
        module_length = other.module_length;
        sign = other.sign;
        module = new unsigned int[module_capacity]();
        std::memcpy(module, other.module, sizeof(unsigned int) * module_capacity);
    }

    BigInt& operator=(const BigInt& other) {
        module_capacity = other.module_capacity;
        module_length = other.module_length;
        sign = other.sign;
        module = new unsigned int[module_capacity]();
        std::memcpy(module, other.module, sizeof(unsigned int) * module_capacity);
        return *this;
    }

    bool operator<(const BigInt& other) const {
        if (sign < other.sign)
            return true;
        else if (sign > other.sign)
            return false;

        if (module_length != other.module_length)
            return (module_length < other.module_length) ^ (sign < 0);

        for (size_t i = module_length;; --i) {
            if (module[i] != other.module[i])
                return (module[i] < other.module[i]) ^ (sign < 0);
            if (i == 0)
                break;
        }
        return false;
    }

    bool operator<=(const BigInt& other) const {
        if (sign < other.sign)
            return true;
        else if (sign > other.sign)
            return false;

        if (module_length != other.module_length)
            return (module_length < other.module_length) ^ (sign < 0);

        for (size_t i = module_length;; --i) {
            if (module[i] != other.module[i])
                return (module[i] < other.module[i]) ^ (sign < 0);
            if (i == 0)
                break;
        }
        return true;
    }

    bool operator>(const BigInt& other) const {
        return !(*this <= other);
    }

    bool operator>=(const BigInt& other) const {
        return !(*this < other);
    }

    bool operator==(const BigInt& other) const {
        if (module_length == 0 && other.module_length == 0)
            return true;
        if (sign != other.sign)
            return false;
        if (module_length != other.module_length)
            return false;
        for (size_t i = module_length - 1;; --i) {
            if (module[i] != other.module[i])
                return false;
            if (i == 0)
                break;
        }
        return true;
    }

    bool operator!=(const BigInt& other) const {
        return !(*this == other);
    }

    template <class T>
    bool operator<(T other) const {
        return *this < BigInt(other);
    }

    template <class T>
    bool operator<=(T other) const {
        return *this <= BigInt(other);
    }

    template <class T>
    bool operator>(T other) const {
        return *this > BigInt(other);
    }

    template <class T>
    bool operator>=(T other) const {
        return *this >= BigInt(other);
    }

    template <class T>
    bool operator==(T other) const {
        return *this == BigInt(other);
    }

    template <class T>
    bool operator!=(T other) const {
        return *this != BigInt(other);
    }

    BigInt& operator-() {
        if (*this != 0)
            sign *= -1;

        return *this;
    }

    BigInt& operator+=(const BigInt& other) {
        if (sign == other.sign) {
            while (module_capacity < other.module_length) {
                resize(module_capacity * 2);
            }
            unsigned long long change = 0;
            for (size_t i = 0; i < other.module_length; ++i) {
                change = change + module[i] + other.module[i];
                module[i] = change & static_cast<unsigned int>(-1);
                change >>= sizeof(unsigned int) * 8;
            }
            module_length = other.module_length;
            if (change > 0) {
                if (module_capacity == module_length)
                    resize(module_capacity * 2);
                module[module_length] = change;
                ++module_length;
            }
            ClearLeadingZeros();
        } else {
            sign *= -1;
            bool reverse = (*this < other) ^ (sign < 0);
            if (!reverse) {
                long long change = 0;
                for (size_t i = 0; i < other.module_length; ++i) {
                    change = change + module[i] - other.module[i];
                    module[i] = change >= 0 ? change : change + static_cast<unsigned int>(-1);
                    change = -(change < 0);
                }
            } else {
                sign *= -1;
                long long change = 0;
                while (module_capacity < other.module_length) {
                    resize(module_capacity * 2);
                }
                for (size_t i = 0; i < other.module_length; ++i) {
                    change = change - module[i] + other.module[i];
                    module[i] = change >= 0 ? change : change + static_cast<unsigned int>(-1);
                    change = -(change < 0);
                }
            }
            sign *= -1;
            ClearLeadingZeros();
        }
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        sign *= -1;
        *this += other;
        if (*this != 0)
            sign *= -1;
        return *this;
    }

    template <class T>
    BigInt& operator+=(T other) {
        return *this += BigInt(other);
    }

    template <class T>
    BigInt& operator-=(T other) {
        return *this -= BigInt(other);
    }

    BigInt operator+(const BigInt& other) const {
        BigInt result(*this);
        result += other;
        return result;
    }

    BigInt operator-(const BigInt& other) const {
        BigInt result(*this);
        result -= other;
        return result;
    }

    BigInt& operator*=(const BigInt& other) {
        int result_sign = sign * other.sign;
        BigInt result;
        result.resize(module_length + other.module_length);
        result.sign = result_sign;
        for (size_t i = 0; i < module_length; ++i) {
            unsigned long long addition = 0;
            size_t j;
            for (j = 0; j < other.module_length; ++j) {
                unsigned long long product = static_cast<unsigned long long>(module[i]) * other.module[j] + addition;
                unsigned long long sum = result.module[i + j] + (product & static_cast<unsigned int>(-1));
                result.module[i + j] = sum & static_cast<unsigned int>(-1);
                addition = (sum >> 32) + (product >> 32);
            }
            while (addition != 0) {
                unsigned long long sum = result.module[i + j] + addition;
                result.module[i + j] = sum & static_cast<unsigned int>(-1);
                addition = sum >> 32;
                ++j;
            }
        }
        *this = result;
        ClearLeadingZeros();
        return *this;
    }

    BigInt operator*(const BigInt& other) const {
        BigInt result(*this);
        result *= other;
        return result;
    }

    template <class T>
    BigInt& operator*=(T other) {
        return *this *= BigInt(other);
    }

    BigInt& operator/=(const BigInt& other);

    BigInt operator/(const BigInt& other) const {
        BigInt result(*this);
        result /= other;
        return result;
    }

    void resize(size_t new_size) {
        auto new_module = new unsigned int[new_size]();
        std::memcpy(new_module, module, sizeof(unsigned int) * module_capacity);
        delete []module;
        module = new_module;
        module_capacity = new_size;
        ClearLeadingZeros();
    }


    ~BigInt() {
        delete []module;
    }

private:
    void ClearLeadingZeros() {
        size_t i = module_capacity;
        module_length = module_capacity;
        while (i > 0 && module[--i] == 0)
            module_length = i;
        if (module_length == 0) {
            sign = 1;
        }
    }

    unsigned int* module;
    size_t module_capacity;
    size_t module_length;
    int sign;
    friend std::ostream& operator<<(std::ostream& out, const BigInt& number);
};


BigInt operator*(unsigned int x, const BigInt& y) {
    auto result = y;
    result *= x;
    return result;
}


BigInt operator*(const BigInt& y, unsigned int x) {
    auto result = y;
    result *= x;
    return result;
}

BigInt& BigInt::operator/=(const BigInt& other) {
    int result_sign = sign * other.sign;
    sign = other.sign;
    BigInt result;
    while ((*this >= other && sign > 0) || (*this <= other && sign < 0)) {
        result *= static_cast<long long>(1) << 32;
        result += (module[module_length - 1] / other.module[other.module_length - 1]);
        *this -= (module[module_length - 1] / other.module[other.module_length - 1]) * other;
        if (module_length == 0)
            break;
        sign = other.sign;
    }
    *this = result;
    sign = result_sign;
    ClearLeadingZeros();
    return *this;
}

class DummyBigInt {
public:
    DummyBigInt() : data(1, '0') {}

    void operator +=(const DummyBigInt& x) {
        auto value = x.data;
        if (value.size() > data.size())
            data.resize(value.size(), '0');
        int change = 0;
        for (size_t i = 0; i < value.size(); ++i) {
            change = change + (data[i] - '0') + (value[i] - '0');
            data[i] = '0' + change % 10;
            change /= 10;
        }
        for (size_t i = value.size(); change != 0; ++i) {
            if (i >= data.size())
                data.push_back('0');
            change = change + (data[i] - '0');
            data[i] = '0' + change % 10;
            change /= 10;
        }
    }

    void operator+=(unsigned int x) {
        DummyBigInt tmp;
        tmp.data = std::to_string(x);
        std::reverse(tmp.data.begin(), tmp.data.end());
        *this += tmp;
    }


    void shift() {
        DummyBigInt tmp;
        for (size_t i = 0; i < 32; ++i) {
            tmp.data = data;
            *this += tmp;
        }
    }

    std::string data;
};

std::ostream& operator<<(std::ostream& out, const BigInt& number) {
    if (number.sign < 0)
        out << '-';
    size_t i = number.module_capacity - 1;
    DummyBigInt dummy;
    for (;; --i) {
        dummy.shift();
        dummy += number.module[i];
        if (i == 0)
            break;
    }
    std::reverse(dummy.data.begin(), dummy.data.end());
    out << dummy.data;
    return out;
}

