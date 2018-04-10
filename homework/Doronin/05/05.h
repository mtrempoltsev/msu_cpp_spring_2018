#include <iostream>
#include <cstring>
#pragma once
class BigInt
{
    bool sign = false;
    size_t point = 0;
    size_t size = 64;
    char* numb = nullptr;

    void alloc()
    {
        char* buff = new char[2*size];
        std::copy(numb, numb+point, buff);
        size *= 2;
        delete[] numb;
        numb = buff;
    }

    void push(char c)
    {
        numb[point++]=c;
        if(point == size)
            this->alloc();
    }

    void push_before(char c)
    {
        for(size_t i = point; i > 0; i--)
            numb[i] = numb[i-1];
        point++;
        if(point==size)
            this->alloc();
        numb[0] = c;
    }

    char pop()
    {
        return numb[--point];
    }

    void is_zero()
    {
        if(point == 1 && numb[0] == 0)
            sign = false;
    }

    void delete_zero()
    {
        for(size_t i = point-1; i != 0; i--)
        {
            if (numb[i] > 0)
                break;
            point--;
        }
    }

    char binSearch(const BigInt &dividend, const BigInt &divisor) const
    {
        char res = 0;
        char left = 0;
        char right = 10;

        while (left <= right)
        {
            char curr = (right + left) / 2;
            if (BigInt(curr) * divisor <= dividend)
            {
                res = curr;
                left = curr + 1;
            }
            else
                right = curr - 1;
        }
        return res;
    }

public:
    BigInt()
    :sign(false),
     point(0)
    {
        numb = new char[size];
        this->push(0);
    }

    BigInt(int64_t x)
    {
        numb = new char[size];
        if(x == 0)
        {
            sign = false;
            this->push(0);
            return;
        }

        if(x < 0)
        {
            sign = true;
            x *= -1;
        }

        while(x>0)
        {
            this->push(x%10);
            x /= 10;
        }

    }

    BigInt(const char* st, int len)
    {
        numb = new char[size];
        int i = 0;
        if(st[0] == '-')
        {
            sign = true;
            i = 1;
        }

        for(int j = len-1; j >= i; j--)
        {
            this->push(st[j]-'0');
        }
    }

    BigInt(BigInt&& value):
    sign(value.sign),
    point(value.point),
    size(value.size),
    numb(value.numb)
    {
        //value.numb = nullptr;
        value.numb = new char[size];
        value.push(0);
    }

    BigInt(const BigInt& big_int):
    size(big_int.size),
    point(big_int.point),
    sign(big_int.sign)
    {
        numb = new char[size];
        std::copy(big_int.numb, big_int.numb+big_int.point, numb);
    }

    ~BigInt()
    {
        delete [] numb;
    }

    bool operator==(const BigInt& value) const
    {
        if((point != value.point)||(sign != value.sign))
            return false;

        for(size_t i = 0; i < point; i++)
            if(numb[i] != value.numb[i])
                return false;

        return true;
    }

    bool operator!=(const BigInt& value) const
    {
        return !(*this==value);
    }

    BigInt& operator=(const BigInt& value)
    {
        if(this == &value)
            return *this;
        delete[] numb;
        size = value.size;
        sign = value.sign;
        point = value.point;
        numb = new char[size];
        std::copy(value.numb, value.numb + value.point, this->numb);
        return *this;
    }

    BigInt& operator=(BigInt&& value)
    {
        if(this == &value)
            return *this;

        size = value.size;
        sign = value.sign;
        point = value.point;

        delete[] numb;

        numb = value.numb;
        value.numb = nullptr;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& value)
    {
        if (value.sign)
            out << '-';
        for (size_t i = value.point-1; i != -1; i--)
            out << static_cast<char>('0' + value.numb[i]);
        return out;
    }

    bool operator>(const BigInt& value) const
    {
        if (sign != value.sign)
            return !sign;

        if (point < value.point)
            return sign;
        else if (point > value.point)
            return !sign;

        for (size_t i = point - 1; i != -1; i--)
        {
            if (numb[i] < value.numb[i])
                return sign;
            else if (numb[i] > value.numb[i])
                return !sign;
        }
        return false;
    }

    bool operator<(const BigInt& value) const
    {
        if (sign != value.sign)
            return sign;
        if (point > value.point)
            return sign;
        else if (point < value.point)
            return !sign;
        for (size_t i = point - 1; i != -1; i--)
        {
            if (numb[i] > value.numb[i])
                return sign;
            else if (numb[i] < value.numb[i])
                return !sign;
        }
        return false;
    }

    bool operator<=(const BigInt& value) const
    {
        return !(*this > value);
    }

    bool operator>=(const BigInt& value) const
    {
        return !(*this < value);
    }

    BigInt abs() const
    {
        BigInt buff = *this;
        buff.sign = false;
        return buff;
    }

    BigInt operator-() const
    {
        BigInt buff(*this);
        buff.sign = !sign;
        buff.is_zero();
        return buff;
    }

    BigInt operator+(const BigInt& value) const
    {
        if(sign != value.sign)
            return sign ? value - this->abs(): *this - value.abs();

        BigInt res(*this);
        for(size_t i = res.point; i < value.point; i++) //if res < val then add place
            res.push(0);
        char ost = 0;
        char sum = 0;
        for(size_t i = 0; i < value.point; i++)
        {
            sum = res.numb[i] + value.numb[i] + ost;
            res.numb[i] = sum%10;
            ost = sum/10;
        }
        for(size_t i = value.point; i < res.point; i++) //if res > val
        {
            sum = res.numb[i] + ost;
            res.numb[i] = sum%10;
            ost = sum/10;
        }
        if(ost > 0)
            res.push(ost);
        res.delete_zero();
        res.is_zero();
        return res;
    }

    BigInt operator-(const BigInt& value) const
    {

        if(sign != value.sign)
            return sign ? -(this->abs() + value): *this + value.abs();

        if(sign)
            return (value.abs() + *this);
        if(*this < value)
            return -(value - *this);

        BigInt res(*this);
        char ost = 0;
        char dx = 0;

        for(size_t i = 0; i < value.point; i++)
        {
            dx = numb[i] - value.numb[i] - ost;
            if(dx < 0)
            {
                res.numb[i] = dx + 10;
                ost = 1;
            }
            else
            {
                res.numb[i] = dx;
                ost = 0;
            }
        }
        for(size_t i = value.point; i < point; i++)
        {
            dx = numb[i] - ost;
            if(dx < 0)
            {
                res.numb[i] = dx + 10;
                ost = 1;
            }
            else
            {
                res.numb[i] = dx;
                ost = 0;
            }
        }
        res.delete_zero();
        res.is_zero();

        return res;
    }

    BigInt operator*(const BigInt& value) const
    {
        BigInt res;
        char ost = 0;
        char mult = 0;

        for(size_t i = 0; i < value.point; i++)
        {
            BigInt step;
            step.pop();
            ost = 0;
            for(size_t j = 0; j < i; j++)
                step.push(0);
            for(size_t j = 0; j < point; j++)
            {
                mult = numb[j]*value.numb[i] + ost;
                step.push(mult%10);
                ost = mult/10;
            }
            if(ost > 0)
                step.push(ost);
            res = res + step;

        }

        res.sign = (sign != value.sign);
        res.delete_zero();
        res.is_zero();
        return res;
    }


    BigInt operator/(const BigInt& value) const
    {
        BigInt res;
        BigInt step;
        step.pop();
        BigInt abs_number = value.abs();
        for (size_t i = 0; i < point; i++)
        {
            step.push_before(numb[point - 1 - i]);
            step.delete_zero();
            char div = binSearch(step, abs_number);
            res.push_before(div);
            step = step - abs_number * BigInt(div);
        }
        res.delete_zero();
        res.sign = (sign != value.sign);
        res.is_zero();
        return res;
    }
};
