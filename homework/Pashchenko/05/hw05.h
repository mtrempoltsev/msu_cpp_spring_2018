#pragma once
#include <cstdint>

int64_t abs64(int64_t value)
{
    if(value < 0)
        return (value * (-1));
    return value;
}

class BigInt
{
    using digit = int8_t;
    using sign = bool;

    digit *data_;   // reversed data
    size_t len_;
    sign sgn_;  //  true := '+', false := '-'

public:
    explicit BigInt() : len_(1), sgn_(true), data_((digit*) malloc(sizeof(digit) * 1)) {*data_ = 0;}
    explicit BigInt(bool rand_size_mode, size_t n) : len_(n), sgn_(true), data_((digit*) malloc(sizeof(digit) * n)) {*data_ = 0;}

    BigInt(int64_t init)
    {
        size_t count = 0;
        int64_t abs_init = abs64(init);

        do
        {
            abs_init /= 10;
            count++;
        }
        while(abs_init > 0);

        len_ = count;
        data_ = (digit*) malloc(sizeof(digit) * count);
        abs_init = abs64(init);

        for(size_t i = 0; i < len_; i++)
        {
            data_[i] = digit(abs_init % 10);
            abs_init /= 10;
        }

        sgn_ = true;
        if(init < 0)
            sgn_ = false;
    }

    ~BigInt()
    {
        free(data_);
    }

    BigInt(const BigInt& copied) : len_(copied.len_), sgn_(copied.sgn_) //  copy constructor
    {
        data_ = (digit*) malloc(sizeof(digit) * len_);
        for(size_t i = 0; i < len_; ++i)
            data_[i] = copied.data_[i];
    }

    ////////////////////////////////////

    BigInt& operator=(const BigInt& copied) //  copy operator
    {
        if(*this == copied)
            return *this;

        free(data_);

        len_ = copied.len_;
        sgn_ = copied.sgn_;
        data_ = (digit*) malloc(sizeof(digit) * len_);
        for(size_t i = 0; i < len_; ++i)
            data_[i] = copied.data_[i];

        return *this;
    }

    BigInt& operator=(const int64_t& init)  //  convertion from int64_t
    {
        size_t count = 0;
        int64_t abs_init = abs64(init);

        while(abs_init > 0)
        {
            abs_init /= 10;
            count++;
        }

        len_ = count;
        data_ = (digit*) malloc(sizeof(digit) * len_);
        abs_init = abs64(init);

        for(size_t i = 0; i < len_; i++)
        {
            data_[i] = digit(abs_init % 10);
            abs_init /= 10;
        }

        sgn_ = true;
        if(init < 0)
            sgn_ = false;
    }

    //////////////////////////////////////////////////  сравнение

    bool operator==(const BigInt& other) const
    {
        if (sgn_ != other.sgn_)
            return false;

        for (size_t i = 0; i < len_; i++) {
            if (data_[i] != other.data_[i])
                return false;
        }
        return true;
    }

    bool operator!=(const BigInt& other) const
    {
        return !(*this == other);
    }

    bool less(const BigInt& other) const
    {
        if(len_ < other.len_)
            return true;
        if(len_ > other.len_)
            return  false;

        for(size_t i = other.len_; i > 0; i--)
        {
            if(data_[i - 1] > other.data_[i - 1])
                return false;
        }
        return true;
    }

    bool operator<(const BigInt& other) const
    {
        if(sgn_ != other.sgn_)
            return sgn_ < other.sgn_;

        if(*this == other)
            return false;

        return less(other) == sgn_; //  less_out XAND sign
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

    BigInt abs_val(const BigInt &arg) const
    {
        BigInt abs_v = arg;
        abs_v.sgn_ = '+';
        return abs_v;
    }

    BigInt adder(const BigInt& other, sign sgn) const
    {
        BigInt tmp(true, std::max(len_, other.len_) + 1);

        for(size_t i = 0; i < len_; i++)
            tmp.data_[i] = data_[i];

        for(size_t i = len_; i < tmp.len_; i++)
            tmp.data_[i] = 0;

        digit passing_digit = 0;

        for(size_t i = 0; i < other.len_; i++)
        {
            digit part_sum = tmp.data_[i] + passing_digit + other.data_[i];
            if(part_sum > 9)
            {
                tmp.data_[i] = digit(part_sum % 10);
                passing_digit = 1;
            } else
            {
                tmp.data_[i] = part_sum;
                passing_digit = 0;
            }
        }

        tmp.data_[tmp.len_ - 1] = passing_digit;
        tmp.sgn_ = sgn;

        BigInt tmp2 = remove_end_zeros(tmp);
        return tmp2;
    }

    BigInt remove_end_zeros(BigInt& value) const
    {
        if(value.len_ == 1)
            return value;

        if(value.data_[value.len_ - 1] == 0)
        {
            BigInt tmp(true, value.len_ - 1);
            tmp.sgn_ = value.sgn_;

            //std::cout << "jojo " << tmp.len_ << std::endl;

            for(size_t i = 0; i < tmp.len_; i++)
                tmp.data_[i] = value.data_[i];

            return remove_end_zeros(tmp);
        }
        return value;
    }

    BigInt operator+(const BigInt &other) const
    {
        //bool abs_l_greater = (abs_val(*this) > abs_val(other));

        if(sgn_ == other.sgn_)
        {
            return adder(other, sgn_);
        } else
        {
            if(*this > other)
                return (*this - abs_val(other));
            else
                return (other - abs_val(*this));
        }
    }

    BigInt subtractor(const BigInt& other, sign sgn) const
    {
        BigInt tmp(true, std::max(len_, other.len_) + 1);
        BigInt tmp_other(true, std::max(len_, other.len_) + 1);

        for(size_t i = 0; i < len_; i++)    //  *this and other to be same length
            tmp.data_[i] = data_[i];
        for(size_t i = len_; i < tmp.len_; i++)
            tmp.data_[i] = 0;

        for(size_t i = 0; i < other.len_; i++)  //  *this and other to be same length
            tmp_other.data_[i] = other.data_[i];
        for(size_t i = other.len_; i < tmp_other.len_; i++)
            tmp_other.data_[i] = 0;

        digit passing_digit = 0;

        for(size_t i = 0; i < tmp.len_; i++)
        {
            digit part_diff = tmp.data_[i] - passing_digit - tmp_other.data_[i];

            if(part_diff < 0)
            {
                tmp.data_[i] = digit(part_diff + 10);
                passing_digit = 1;
            } else
            {
                tmp.data_[i] = part_diff;
                passing_digit = 0;
            }
        }

        BigInt tmp2 = remove_end_zeros(tmp);
        tmp2.data_[tmp2.len_ - 1] -= passing_digit;
        tmp2.sgn_ = sgn;

        tmp = remove_end_zeros(tmp2);
        return tmp;
    }

    BigInt operator-(const BigInt &other) const
    {
        bool abs_l_more_or_equal = (abs_val(*this) >= abs_val(other));

        if(abs_l_more_or_equal)
        {
            if(sgn_ && other.sgn_)  //  Greater_abs positive - positive => guaranteed to be pos
                return subtractor(other, true);
            if(sgn_ && !other.sgn_) //  Greater_abs positive - negative => guaranteed to be pos
                return adder(abs_val(other), true);   // <=> positive + positive
            if(!sgn_ && other.sgn_) //  Greater_abs negative - positive => guaranteed to be neg
                return other.adder(abs_val(*this), false);   // <=> negative - negative
            if(!sgn_ && !other.sgn_)    //  Greater_abs negative - negative => guaranteed to be neg
                return abs_val(*this).subtractor(abs_val(other), false);
        } else
        {
            if(sgn_ && other.sgn_)  //  positive - greater_abs positive => guaranteed to be neg
                return other.subtractor(*this, false);
            if(sgn_ && !other.sgn_) //  positive - greater_abs negative => guaranteed to be pos
                return adder(abs_val(other), true);   // <=> positive + positive
            if(!sgn_ && other.sgn_) //  negative - greater_abs positive => guaranteed to be neg
                return other.adder(abs_val(*this), false);   // <=> negative - negative
            if(!sgn_ && !other.sgn_)    //  negative - greater_abs negative => guaranteed to be pos
                return abs_val(other).subtractor(abs_val(*this), true);
        }
    }

    BigInt operator-() const
    {
        BigInt new_value = *this;
        if(*this != 0)
            new_value.sgn_ = !(this->sgn_);

        return new_value;
    }

    BigInt operator*(const BigInt& other) const //  ЗАГЛУШКА
    {
        return other;
    }

    BigInt operator/(const BigInt& other) const //  ЗАГЛУШКА
    {
        return other;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
};

std::ostream& operator<<(std::ostream& out, const BigInt& value)
{
    if(!value.sgn_ && value != (BigInt(-10) - BigInt(-10))) // avoiding -0
        out << '-';
    for(size_t i = value.len_; i > 0; i--)
        out << int(value.data_[i - 1]);
    return out;
}
