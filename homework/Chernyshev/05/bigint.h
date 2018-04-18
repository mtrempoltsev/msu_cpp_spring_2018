// bigint.h

#pragma once


#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>


template<class T>
class Vector
{
private:
    constexpr static int START_SIZE = 8;

    size_t alloc = 0;
    size_t used = 0;
    T *data = nullptr;

    // Note that this is not true 'swap'
    void swap_or_copy(Vector &v)
    {
        alloc = v.alloc;
        used = v.used;
        std::swap(data, v.data);
    }

public:
    // Constructors
    explicit Vector(size_t size = START_SIZE)
    {
        data = new T[size]();
        alloc = size;
        used = 0;
    }

    // Copy constructors
    Vector (const Vector &v)
    {
        alloc = v.alloc;
        used = v.used;
        data = new T[alloc]();
        std::copy(v.data, v.data + alloc, data);
    }

    Vector (Vector &&v) noexcept
    {
        alloc = v.alloc;
        used = v.used;
        data = v.data;
        v.data = nullptr;
    }

    // operator =
    Vector &operator = (const Vector &v)
    {
        if (this != &v) {
            Vector(v).swap_or_copy(*this);
        }

        return *this;
    }

    Vector &operator = (Vector &&v)
    {
        swap_or_copy(v);
        return *this;
    }

    // reserve
    void reserve(size_t size)
    {
        if (size <= alloc) {
            return;
        }

        alloc = size;
        auto tmp = new T[alloc]();
        std::copy(data, data + used, tmp);
        delete[] data;
        data = tmp;
    }

    // resize
    void resize(size_t size)
    {
        if (size > alloc) {
            reserve(size);
        }
        used = size;
    }

    // push_back
    void push_back(const T &x)
    {
        if (used >= alloc) {
            reserve(2 * alloc);
        }

        data[used++] = x;
    }

    void push_back(T &&x)
    {
        if (used >= alloc) {
            reserve(2 * alloc);
        }

        data[used++] = std::move(x);
    }

    // insert
    void insert(T *p, const T &x)
    {
        if (data <= p && p <= data + used) {
            if (used >= alloc) {
                reserve(2 * alloc);
            }

            for (int *d = data + used; d > p; --d) {
                d[0] = d[-1];
            }
            *p = x;
            ++used;
        } else {
            throw std::out_of_range("iterator doesn't point to this Vector");
        }
    }

    // pop_back
    void pop_back()
    {
        --used;
    }

    // operator []
    T &operator [] (size_t i)
    {
        if (0 <= i || i < used) {
            return data[i];
        }
        throw std::out_of_range("index is incorrect");
    }

    T operator [] (size_t i) const
    {
        if (0 <= i || i < used) {
            return data[i];
        }
        throw std::out_of_range("index is incorrect");
    }

    //   Getters
    size_t size() const
    {
        return used;
    }

    // begin & end
    T *begin() const
    {
        return data;
    }

    T *begin()
    {
        return data;
    }

    T *end() const
    {
        return data + used;
    }

    T *end()
    {
        return data + used;
    }

    // back
    T back() const
    {
        if (used > 0) {
            return data[used - 1];
        }
        throw std::length_error("vector has zero length");
    }

    T &back()
    {
        if (used > 0) {
            return data[used - 1];
        }
        throw std::length_error("vector has zero length");
    }

    // Destructor
    ~Vector()
    {
        delete[] data;
    }
};


class BigInt
{
    // This constants for BigInt sign
    enum
    {
        positive = false,
        negative = true
    };
    constexpr static int BASE = 1'000'000'000;

    bool sign = positive;
    Vector<int> number;


    void delete_zeros()
    {
        while (number.size() > 1 && number.back() == 0) {
            number.pop_back();
        }

        if (*this == 0) {
            sign = positive;
        }
    }

public:
    // Constructor from std::string
    BigInt(const std::string &$number)
    {
        sign = positive;

        auto n = $number.size();
        if (n == 0) {
            return;
        }

        int start = 0;
        if ($number[0] == '-') {
            sign = negative;
            start = 1;
        }

        for (int i = n; i > start; i -= 9)
        {
            if (i - start < 9) {
                number.push_back(stoi($number.substr(start, i)));
            } else {
                number.push_back(stoi($number.substr(i - 9, 9)));
            }
        }
    }

    // Constructor from long long
    BigInt(long long $number = 0)
    {
        sign = positive;
        if ($number < 0) {
            sign = negative;
            $number = -$number;
        }

        do {
            number.push_back($number % BASE);
            $number /= BASE;
        } while ($number > 0);
    }

    // Copy constructors
    BigInt(const BigInt &a)
            : sign(a.sign), number(a.number)
    {
    }

    BigInt(BigInt &&a)
            : sign(a.sign), number(a.number)
    {
    }

    // operator =
    BigInt &operator = (const BigInt &b)
    {
        sign = b.sign;
        number = b.number;
        return *this;
    }

    BigInt &operator = (BigInt &&b)
    {
        sign = b.sign;
        number = std::move(b.number);
        return *this;
    }

    // Returns number of digits in number in 10^9 numeric system
    size_t size() const
    {
        return number.size();
    }

    bool operator < (const BigInt &a) const
    {
        const int n = size();
        const int m = a.size();

        if (n == 1 && m == 1 && number[0] == 0 && a.number[0] == 0) {
            return false;
        }

        if (sign == positive && a.sign == negative) {
            return false;
        }
        if (sign == negative && a.sign == positive) {
            return true;
        }

        bool is_less = true;
        if (n < m) {
            is_less = true;
        } else if (n == m) {
            bool are_equal = true;
            for (int i = n - 1; i >= 0; --i) {
                if (number[i] != a.number[i]) {
                    is_less = number[i] < a.number[i];
                    are_equal = false;
                    break;
                }
            }

            if (are_equal) {     // I return "false" here because these two numbers
                return false;    // are equal so (*this < a) and (a < *this) at the same time
            }
        } else {
            is_less = false;
        }

        if (sign == negative) {
            is_less = !is_less;
        }

        return is_less;
    }

    bool operator > (const BigInt &a) const
    {
        return a < *this;
    }

    bool operator == (const BigInt &a) const
    {
        return !(*this < a || a < *this);
    }

    bool operator <= (const BigInt &a) const
    {
        return !(*this > a);
    }

    bool operator >= (const BigInt &a) const
    {
        return !(*this < a);
    }

    bool operator != (const BigInt &a) const
    {
        return !(*this == a);
    }

    BigInt operator - () const
    {
        BigInt result = *this;

        if (sign == positive) {
            result.sign = negative;
        } else {
            result.sign = positive;
        }

        return result;
    }

    BigInt operator + (const BigInt &a) const
    {
        if (sign == a.sign) {
            BigInt result;

            result.number.resize(0);
            result.sign = sign;

            int carry = 0;
            int n = size();
            int m = a.size();

            for (int i = 0; i < std::max(n, m) || carry; ++i) {
                int cur_digit = carry;
                cur_digit += i < n ? number[i] : 0;
                cur_digit += i < m ? a.number[i] : 0;

                carry = cur_digit >= BASE;
                if(carry) {
                    cur_digit -= BASE;
                }

                result.number.push_back(cur_digit);
            }

            return result;
        } else {
            if (sign == negative) {
                return a - (-(*this));
            } else {
                return *this - (-a);
            }
        }
    }

    BigInt operator - (const BigInt &a) const
    {
        if (*this == a) {
            return 0;
        }

        if (sign == a.sign) {
            if (a.sign == negative) {
                return (-a) - (-(*this));
            }

            BigInt result;
            result.number.resize(0);

            BigInt fir = *this;
            BigInt sec = a;
            if (fir < sec) {
                std::swap(fir, sec);
                result.sign = negative;
            }

            int carry = 0;
            int n = fir.size();
            int m = sec.size();

            for (int i = 0; i < n || i < m; ++i) {
                int cur_digit = i < n ? fir.number[i] : 0;
                cur_digit -= i < m ? sec.number[i] : 0;
                cur_digit -= carry;

                carry = cur_digit < 0;
                if (carry) {
                    cur_digit += BASE;
                }

                result.number.push_back(cur_digit);
            }

            result.delete_zeros();

            return result;
        } else {
            if (sign == negative) {
                return -((-(*this)) + a);
            } else {
                return *this + (-a);
            }
        }
    }

    BigInt operator * (const BigInt &a) const
    {
        BigInt result;
        result.number.resize(size() + a.size());

        if (sign != a.sign) {
            result.sign = negative;
        }

        int n = size();
        int m = a.size();

        for (int i = 0; i < n; ++i) {
            for (int j = 0, carry = 0; j < m || carry; ++j) {
                long long cur = result.number[i + j] + carry;
                if (j < m) {
                    cur += 1LL * number[i] * a.number[j];
                }
                result.number[i + j] = cur % BASE;
                carry = cur / BASE;
            }
        }

        result.delete_zeros();

        return result;
    }

    BigInt operator / (const BigInt &a) const
    {
        BigInt result;
        result.number.resize(0);

        if (sign != a.sign) {
            result.sign = negative;
        }

        BigInt sec = a;
        sec.sign = positive;

        int n = size();

        BigInt cur_value;
        cur_value.number.resize(0);

        for (int i = n - 1; i >= 0; --i) {
            cur_value.number.insert(cur_value.number.begin(), number[i]);
            cur_value.delete_zeros();

            int div_left = 0, div_right = BASE;

            while (div_right - div_left > 1) {
                int div_middle = (div_left + div_right) / 2;

                if (sec * div_middle <= cur_value) {
                    div_left = div_middle;
                } else {
                    div_right = div_middle;
                }
            }

            cur_value = cur_value - sec * div_left;

            result.number.push_back(div_left);
        }

        std::reverse(result.number.begin(), result.number.end());
        result.delete_zeros();

        return result;
    }

    BigInt operator % (const BigInt &a) const
    {
        return *this - a * (*this / a);
    }

    friend std::istream &operator >> (std::istream &in, BigInt &a);
    friend std::ostream &operator << (std::ostream &out, const BigInt &a);
    friend BigInt abs(const BigInt &a);
    friend BigInt pow(const BigInt &a, unsigned n);
};

std::istream &operator >> (std::istream &in, BigInt &a)
{
    std::string tmp;
    in >> tmp;
    a = BigInt(tmp);

    return in;
}

std::ostream &operator << (std::ostream &out, const BigInt &a)
{
    if (a.size() == 0) {
        return out;
    }

    if (a.sign == BigInt::negative) {
        out << "-";
    }

    out << a.number.back();
    if (a.size() >= 2) {
        for (int i = a.size() - 2; i >= 0; --i) {
            out << std::setw(9) << std::setfill('0') << a.number[i];
        }
    }
    return out;
}

BigInt abs(const BigInt &a)
{
    BigInt result = a;
    result.sign = BigInt::positive;

    return result;
}

BigInt pow(const BigInt &a, unsigned n)
{
    if (n == 0) {
        return 1;
    }
    
    BigInt tmp = pow(a, n / 2);

    return tmp * tmp * (n % 2 ? a : 1);
}
