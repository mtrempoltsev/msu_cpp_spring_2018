#include<iostream>

namespace options
{
    constexpr int base = 10000;
    constexpr int numberOfDigitsInBase = 4;
}

class BigInt
{
    int sign_;
    int* bigNumber_;
    size_t size;
    BigInt(bool q, size_t size, int a = 0) : sign_(1), size(size_)
    {
        bigNumber_ = new int[size];
        for (size_t i = 0; i < size; i++)
            bigNumber_[i] = 0;
    }
public:
    BigInt() : sign_(1), bigNumber_((int*)malloc(sizeof(int))), size(1)
    {
        bigNumber_[0] = 0;
    }

    BigInt(int64_t a)
    {
        if (a >= 0)
            sign_ = 1;
        else
        {
            sign_ = -1;
            a = a * (-1);
        }
        int buf = a % options::base;
        bigNumber_ = new int;
        bigNumber_[0] = buf;
        a -= buf;
        a /= options::base;
        size = 1;
        while (a != 0)
        {
            buf = a % options::base;
            bigNumber_ = (int*)realloc(bigNumber_, sizeof(int) * (size + 1));
            bigNumber_[size] = buf;
            a -= buf;
            a /= options::base;
            size++;
        }
    }

    ~BigInt()
    {
        free(bigNumber_);
    }

    BigInt(const BigInt& a) : sign_(a.sign_), size(a.size)
    {
        bigNumber_ = new int[size];
        for (size_t i = 0; i < size; i++)
            bigNumber_[i] = a.bigNumber_[i];
    }

    BigInt& operator=(const BigInt& a)
    {
        if (this == &a)
            return *this;
        size = a.size;
        sign_ = a.sign_;
        free(bigNumber_);
        bigNumber_ = new int[size];
        for (size_t i = 0; i < size; i++)
            bigNumber_[i] = a.bigNumber_[i];
        return *this;
    }

    BigInt(BigInt &&a) : sign_(a.sign_), bigNumber_(a.bigNumber_), size(a.size)
    {
        a.size = 0;
        a.bigNumber_ = nullptr;
    }

    BigInt& operator=(BigInt &&a)
    {
        if (this == &a)
            return *this;
        size = a.size;
        sign_ = a.sign_;
        free(bigNumber_);
        bigNumber_ = a.bigNumber_;
        a.size = 0;
        a.bigNumber_ = nullptr;
        return *this;
    }

    bool isConsistent() const
    {
        if ((*this).bigNumber_ == nullptr)
            return false;
        return true;
    }

    bool operator==(const BigInt& b) const
    {
        if ((*this).sign_ != b.sign_)
            return false;
        if ((*this).size != b.size)
            return false;
        for (size_t i = 0; i < b.size; i++)
            if ((*this).bigNumber_[i] == b.bigNumber_[i])
                continue;
            else
                return false;
        return true;
    }

    bool operator!=(const BigInt& b) const
    {
        if (*this == b)
            return false;
        else
            return true;
    }

    bool operator<(const BigInt& b) const
    {
        if ((*this).sign_ < b.sign_)
            return true;
        if ((*this).sign_ > b.sign_)
            return false;
        if ((((*this).size < b.size) && (b.sign_ == 1)) || (((*this).size > b.size) && (b.sign_ == -1)))
            return true;
        if ((((*this).size > b.size) && (b.sign_ == 1)) || (((*this).size < b.size) && (b.sign_ == -1)))
            return false;
        if (b.sign_ == 1)
        {
            for (size_t i = b.size - 1; ((i < b.size) && (i >= 0)); i--)
            {
                if ((*this).bigNumber_[i] < b.bigNumber_[i])
                    return true;
                if ((*this).bigNumber_[i] == b.bigNumber_[i])
                    continue;
                else
                    return false;
            }
        }
        else
        {
            for (size_t i = b.size - 1; ((i < b.size) && (i >= 0)); i--)
            {
                if ((*this).bigNumber_[i] > b.bigNumber_[i])
                    return true;
                if ((*this).bigNumber_[i] == b.bigNumber_[i])
                    continue;
                else
                    return false;
            }
        }
    }

    bool operator>(const BigInt& b) const
    {
        return !((*this) < b) && !((*this) == b);
    }

    bool operator<=(const BigInt& b) const
    {
        return !((*this) > b);
    }

    bool operator>=(const BigInt& b) const
    {
        return !((*this) < b);
    }

    BigInt abs() const
    {
        BigInt result = (*this);
        result.sign_ = 1;
        return result;
    }

    BigInt operator+(const BigInt& b) const
    {
        if (!(*this).isConsistent())
            return 0;
        if (!b.isConsistent())
            return 0;
        BigInt result;
        if ((*this).sign_ * b.sign_ == -1)
        {
            if ((*this).abs() > b.abs())
            {
                result = (*this).abs() - b.abs();
                result.sign_ = (*this).sign_;
                return result;
            }
            if ((*this).abs() == b.abs())
            {
                return result;
            }
            else
            {
                result = b.abs() - (*this).abs();
                result.sign_ = b.sign_;
                return result;
            }
        }
        if ((*this).size >= b.size)
            result = *this;
        else
            result = b;
        int toNextDigit = 0;
        size_t i = 0;
        for (i; i < std::min((*this).size, b.size); i++)
        {
            int buf = (*this).bigNumber_[i] + b.bigNumber_[i] + toNextDigit;
            toNextDigit = buf / options::base;
            result.bigNumber_[i] = buf % options::base;
        }
        if (toNextDigit == 1)
            if ((*this).size == b.size)
            {
                result.size += 1;
                result.bigNumber_ = (int*)realloc(bigNumber_, sizeof(int));
                result.bigNumber_[result.size - 1] = 1;
            }
            else
                result.bigNumber_[i] += toNextDigit;
        return result;
    }

    BigInt operator-()
    {
        if (!(*this).isConsistent())
            return 0;
        if ((size == 1) && (bigNumber_[0] == 0))
            return *this;
        (*this).sign_ *= -1;
        return *this;
    }

    BigInt operator-(const BigInt& b) const
    {
        if (!(*this).isConsistent())
            return 0;
        if (!b.isConsistent())
            return 0;
        BigInt result;
        if ((*this).sign_ * b.sign_ == -1)
        {
            result = (*this).abs() + b.abs();
            result.sign_ = (*this).sign_;
            return result;
        }
        BigInt bufBigInt;
        if ((*this).abs() == b.abs())
        {
            return result;
        }
        if ((*this).abs() > b.abs())
        {
            result = (*this);
            bufBigInt = b;
        }
        else
        {
            result = b;
            result.sign_ = b.sign_ * -1;
            bufBigInt = (*this);
        }
        int toNextDigit = 0;
        size_t i = 0;
        for (i; i < bufBigInt.size; i++)
        {
            int buf = result.bigNumber_[i] - bufBigInt.bigNumber_[i] + toNextDigit;
            if (buf < 0)
            {
                result.bigNumber_[i] = options::base + buf;
                int debug = buf - options::base;
                toNextDigit = debug / options::base;
            }
            else
                result.bigNumber_[i] = buf;
        }
        i = result.size - 1;
        while (result.size > 0)
        {
            if (result.bigNumber_[i] == 0)
                result.size--;
            else
                break;
            i--;
        }
        if (result.size == 0)
        {
            result.size = 1;
            return result;
        }
        result.bigNumber_ = (int*)realloc(result.bigNumber_, result.size * sizeof(int));
        return result;
    }

    BigInt operator*(const BigInt& b) const
    {
        if (!(*this).isConsistent())
            return 0;
        if (!b.isConsistent())
            return 0;
        if ((((*this).size == 1) && ((*this).bigNumber_[0] == 0)) || ((b.size == 1) && (b.bigNumber_[0] == 0)))
            return 0;
        BigInt result(true, (*this).size * b.size + 1, 0);
        for (size_t i = 0; i < b.size; i++)
        {
            size_t j = 0;
            int toNextDigit = 0;
            for (; j < (*this).size; j++)
            {
                result.bigNumber_[j + i] += toNextDigit;
                result.bigNumber_[j + i] += b.bigNumber_[i] * (*this).bigNumber_[j];
                toNextDigit = result.bigNumber_[j + i] / options::base;
                result.bigNumber_[j + i] %= options::base;
            }
            result.bigNumber_[j + i] += toNextDigit;
        }
        result.sign_ = (*this).sign_ * b.sign_;
        size_t i = result.size - 1;
        while (result.size > 0)
        {
            if (result.bigNumber_[i] == 0)
                result.size--;
            else
                break;
            i--;
        }
        result.bigNumber_ = (int*)realloc(result.bigNumber_, result.size * sizeof(int));
        return result;
    }

    BigInt operator*(int a) const
    {
        if (!(*this).isConsistent())
            return 0;
        BigInt buf(true, 1, 0);
        buf.bigNumber_[0] = a;
        return (*this) * buf;
    }

    BigInt operator/(const BigInt &b) const
    {
        if (!(*this).isConsistent())
            return 0;
        if (!b.isConsistent())
            return 0;
        BigInt result(true, (*this).size, 0);
        BigInt curValue(true, 1, 0);
        for (size_t i = (*this).size - 1; ((i < (*this).size) && (i >= 0)); i--)
        {
            curValue = curValue * options::base;
            curValue.bigNumber_[0] = (*this).bigNumber_[i];
            int x = 0;
            int l = 0, r = options::base;
            while (l <= r)
            {
                int m = (l + r) >> 1;
                BigInt cur = b.abs() * m;
                if (cur <= curValue)
                {
                    x = m;
                    l = m + 1;
                }
                else
                    r = m - 1;
            }
            result.bigNumber_[i] = x;
            curValue = curValue - b.abs() * x;
        }
        size_t i = result.size - 1;
        while (i > 0)
        {
            if (result.bigNumber_[i] == 0)
                result.size--;
            else
                break;
            i--;
        }
        result.bigNumber_ = (int*)realloc(result.bigNumber_, result.size * sizeof(int));
        if ((result.size == 1) && (result.bigNumber_[0] == 0))
            return 0;
        result.sign_ = (*this).sign_ * b.sign_;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& a)
    {
        if (a.sign_ == -1)
            out << "-";
        out << a.bigNumber_[a.size - 1];
        for (size_t i = a.size - 2; (i >= 0) && (i <= a.size - 1); i--)
        {
            if (a.bigNumber_[i] == 0)
                if (a.size == 1)
                {
                    out << "0";
                    return out;
                }
                else
                {
                    out << "0000";
                    continue;
                }
            int buf = a.bigNumber_[i];
            int secondBuf = options::base / 10;
            while ((buf / secondBuf) == 0)
            {
                out << "0";
                secondBuf /= 10;
            }
            out << a.bigNumber_[i];
        }
        return out;
    }
};

