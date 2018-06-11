#pragma once
#include <iostream>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <tuple>

int64_t abs64(int64_t value)
{
    if(value < 0)
        return (value * (-1));
    return value;
}

class BigInt {
    using digit = char;
    using sign = int;

    char *data_ = nullptr;     // reversed data
    size_t len_ = 0;
    mutable int sgn_ = 1;   // true := 1, false := -1

public:
    BigInt() : data_((digit*) malloc(sizeof(digit) * 2)), len_(1)
    {
        data_[0] = '0';
        data_[1] = '\0';
    }

    BigInt(int64_t init)
    {
        int64_t tmp = abs64(init);
        if (init < 0)
        {
            sgn_ = -1;
            init = abs64(init);
        }

        size_t count = 0;

        if (init == 0)
            count = 1;
        for (count; tmp != 0; count++)
            tmp /= 10;

        data_ = (digit*) malloc(sizeof(digit) * count + 1);

        sprintf(data_, "%lld", init);
        std::reverse(data_, data_ + count);

        data_[count] = '\0';
        len_ = count;
    }

    ~BigInt()
    {
        free(data_);
    }

    BigInt(const BigInt &other) //  copy constructor
    {
        data_ = (digit*) malloc(sizeof(digit) * other.len_ + 1);
        std::strcpy(data_, other.data_);

        data_[other.len_] = '\0';
        len_ = other.len_;
        sgn_ = other.sgn_;
    }

    BigInt &operator=(const BigInt &copied)  //  copy operator
    {
        if (this == &copied) return *this;
        delete[] data_;
        data_ = new char[copied.len_ + 1];
        std::strcpy(data_, copied.data_);
        len_ = copied.len_;
        sgn_ = copied.sgn_;
    }

    //////////////////////////////////////////////////  сравнение

    bool operator==(const BigInt &other) const
    {
        if (sgn_ != other.sgn_)
            return false;

        for (size_t i = 0; i < len_; i++) {
            if (data_[i] != other.data_[i])
                return false;
        }
        return true;
    }

    bool operator!=(const BigInt &other) const
    {
        return !(*this == other);
    }

    bool operator<(const BigInt &other) const
    {
        if (len_ < other.len_)
            return true;
        if (len_ > other.len_)
            return false;

        if (sgn_ < other.sgn_)
            return true;
        else if (sgn_ > other.sgn_)
            return false;

        if (*this == other)
            return false;

        if (sgn_ < 0)
        {
            sgn_ = 1;
            other.sgn_ = 1;

            bool res = *this > other;

            sgn_ = -1;
            other.sgn_ = -1;

            return res;
        }

        for (size_t i = len_; i > 0; i--)
        {
            if (data_[i - 1] > other.data_[i - 1])
                return false;
            else if (data_[i - 1] < other.data_[i - 1])
                return true;
        }
        return false;
    }

    bool operator<=(const BigInt& other) const
    {
        return (*this < other || *this == other);
    }

    bool operator>(const BigInt& other) const
    {
        return !(*this <= other);
    }

    bool operator>=(const BigInt& other) const
    {
        return !(*this < other);
    }

    /////////////////////////////////////////////////   arithmetic

    BigInt operator+(const BigInt &other) const
    {
        if (sgn_ * other.sgn_ < 0)
        {
            if (other.sgn_ < 0)
            {
                other.sgn_ = 1;
                auto tmp_res = *this - other;
                other.sgn_ = -1;

                return tmp_res;
            } else
            {
                sgn_ = 1;
                auto tmp_res = other - *this;
                sgn_ = -1;

                return tmp_res;
            }
        }

        size_t end_len_ = std::max(len_, other.len_);
        size_t min_len_ = std::min(len_, other.len_);

        auto tmp = (digit*) malloc(sizeof(digit) * end_len_ + 2);
        int passing_digit = 0;

        for (size_t i = 0; i < end_len_; ++i)
        {
            int a, b;

            if (i < len_)
                a = data_[i] - '0';
            else
                a = 0;

            if (i < other.len_)
                b = other.data_[i] - '0';
            else
                b = 0;

            int sum = a + b + passing_digit;
            tmp[i] = char(sum % 10) + '0';
            passing_digit = sum / 10;
        }

        auto res = BigInt();
        res.len_ = 0;
        free(res.data_);

        if (passing_digit > 0)
        {
            tmp[end_len_] = char(passing_digit) + '0';
            tmp[end_len_ + 1] = '\0';

            res.len_ = end_len_ + 1;
        } else
        {
            tmp[end_len_] = '\0';
            res.len_ = end_len_;
        }

        res.data_ = tmp;
        res.sgn_ = sgn_;

        return res;
    }

    BigInt operator-(const BigInt &other) const
    {
        if (sgn_ * other.sgn_ < 0)
        {
            if (other.sgn_ < 0)
            {
                other.sgn_ = 1;
                auto tmp_res = *this + other;
                other.sgn_ = -1;

                return tmp_res;
            } else if (sgn_ < 0)
            {
                other.sgn_ = -1;
                auto tmp_res = *this + other;
                other.sgn_ = 1;

                return tmp_res;
            }
        }

        char *first_numb = nullptr;
        char *second_numb = nullptr;
        int res_sgn_ = 0;

        std::tie(first_numb, second_numb, res_sgn_) = this->cons(other);
        size_t second_len_ = std::min(len_, other.len_);
        size_t end_len_ = std::max(len_, other.len_);

        auto res_data_ = (digit*) malloc(sizeof(digit) * end_len_ + 1);
        auto res = BigInt();
        res.len_ = 0;
        free (res.data_);

        if (res_sgn_ == 0)
        {
            res_data_[0] = '0';
            res_data_[1] = '\0';
            res.data_ = res_data_;
            res.sgn_ = 1;
            res.len_ = 1;
            return res;
        }

        int passing_digit = 0;
        for (size_t i = 0; i < end_len_; ++i)
        {
            int sub;
            if (i < second_len_)
                sub = second_numb[i] - '0';
            else
                sub = 0;
            int dif = first_numb[i] - '0' - sub;
            if (dif < 0)
            {
                if (passing_digit == 0)
                    passing_digit = 10;
                else
                    passing_digit = 9;
                dif += passing_digit;
            } else if(dif > 0 && passing_digit > 0)
            {
                dif -= 1;
                passing_digit = 0;
            } else if (passing_digit != 0)
            {
                passing_digit = 9;
                dif += passing_digit;
            }

            res_data_[i] = char(dif + '0');
        }

        size_t last_sig_char = end_len_ - 1;

        for (last_sig_char; res_data_[last_sig_char] == '0' && last_sig_char > 0; --last_sig_char);
        res_data_[last_sig_char + 1] = '\0';
        res.data_ = res_data_;
        res.sgn_ = res_sgn_;
        res.len_ = last_sig_char + 1;

        return res;
    }

    std::tuple<char *, char *, int> cons(const BigInt &other) const
    {
        if (other.len_ > len_)
            return std::make_tuple(other.data_, data_, sgn_ * -1);
        else if (other.len_ < len_)
            return std::make_tuple(data_, other.data_, sgn_);
        for (size_t i = len_; i > 0; --i)
        {
            if (data_[i - 1] < other.data_[i - 1])
                return std::make_tuple(other.data_, data_, sgn_ * -1);
            else if (data_[i - 1] > other.data_[i - 1])
                return std::make_tuple(data_, other.data_, sgn_);
        }
        return std::make_tuple(data_, other.data_, 0);
    }


    BigInt operator-() const
    {
        if (data_[len_ - 1] == '0')
            return BigInt(*this);

        auto new_value = BigInt(*this);
        new_value.sgn_ *= -1;
        return new_value;
    }

    BigInt operator*(const BigInt &other) const
    {
        size_t end_len_ = len_ + other.len_;
        auto res = BigInt();
        res.len_ = 0;
        free(res.data_);

        res.data_ = (digit*) malloc(sizeof(digit) * end_len_ + 2);
        std::fill(res.data_, res.data_ + end_len_ + 1, '0');
        res.data_[end_len_ + 1] = '\0';
        res.len_ = end_len_ + 1;

        for (size_t i = 0; i < other.len_; ++i)
        {
            int curr_dig = other.data_[i] - '0';
            auto tmp = new char[len_ + 2 + i];
            int remind = 0;
            for (size_t q = 0; q < len_ + 1 + i; ++q)
                tmp[q] = '0';

            for (size_t j = i; j < len_ + i; ++j)
            {
                int mul = (data_[j - i] - '0') * curr_dig + remind;
                auto tmp_dig = char(mul % 10 + '0');
                remind = mul / 10;
                tmp[j] = tmp_dig;
            }
            if (remind > 0)
                tmp[len_ + i] = char(remind + '0');

            auto tmp_obj = BigInt();
            tmp_obj.len_ = 0;
            free(tmp_obj.data_);
            tmp_obj.data_ = tmp;
            tmp_obj.len_ = len_ + i + 1;
            tmp_obj.data_[tmp_obj.len_] = '\0';
            res = res + tmp_obj;
        }
        for (res.len_; res.data_[res.len_ - 1] == '0' && res.len_ > 1; --res.len_);
        res.data_[res.len_] = '\0';
        if (res.data_[res.len_ - 1] == '0')
            res.sgn_ = 1;
        else
            res.sgn_ = sgn_ * other.sgn_;

        return res;
    }

    BigInt operator/(const BigInt &other) const
    {

        if (len_ < other.len_ || other.data_[other.len_ - 1] == '0')
            return BigInt(0);

        int this_sgn_ = sgn_;
        int other_sgn_ = other.sgn_;
        sgn_ = 1;
        other.sgn_ = 1;

        if (*this < other)
        {
            sgn_ = this_sgn_;
            other.sgn_ = other_sgn_;
            return BigInt(0);
        }

        auto curr_divider = BigInt(0);
        auto res = BigInt();
        res.len_ = 0;
        free(res.data_);
        res.data_ = new char[len_ + 1];

        size_t curr_not_taken = len_;
        bool fin_flag = false;
        bool first_time = true;

        while(true)
        {
            int counter = 0;
            while (num(curr_divider, other) == -1)
            {
                if (curr_not_taken == 0)
                {
                    fin_flag = true;
                    break;
                }
                if (counter >= 1 && !first_time)
                {
                    res.data_[res.len_] = '0';
                    res.len_++;
                }
                int curr_dig = data_[curr_not_taken - 1] - '0';
                curr_divider = curr_divider * 10;
                curr_divider = curr_divider + curr_dig;

                --curr_not_taken;
                counter++;
            }
            first_time = false;
            if (fin_flag)
            {
                if (counter > 0)
                {
                    res.data_[res.len_] = '0';
                    res.len_++;
                }
                break;
            }

            auto curr_mul = BigInt(0);
            int curr_numb = 0;
            while (num(curr_divider, curr_mul) >= 0)
            {
                curr_mul = curr_mul + other;
                ++curr_numb;
            }
            curr_mul = curr_mul - other;
            --curr_numb;

            curr_divider = curr_divider - curr_mul;

            res.data_[res.len_] = char(curr_numb + '0');
            res.len_++;
        }
        std::reverse(res.data_, res.data_ + res.len_);
        res.data_[res.len_] = '\0';
        res.sgn_ = other_sgn_ * this_sgn_;

        other.sgn_ = other_sgn_;
        sgn_ = this_sgn_;

        return res;
    }

    static int num(const BigInt &first, const BigInt &second)
    {
        if (first.len_ > second.len_)
            return 1;
        else if (first.len_ < second.len_)
            return -1;
        for (size_t i = first.len_; i > 0; --i)
        {
            if (first.data_[i - 1] < second.data_[i - 1])
                return -1;
            else if (first.data_[i - 1] > second.data_[i - 1])
                return 1;
        }
        return 0;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
};

std::ostream& operator<<(std::ostream& out, const BigInt& value)
{
    auto buf = (char*) malloc(sizeof(char) * value.len_ + 1);
    std::reverse_copy(value.data_, value.data_ + value.len_, buf);
    if (value.sgn_ < 0)
        out << '-';

    buf[value.len_] = '\0';
    out << buf;

    free(buf);
    return out;
}
