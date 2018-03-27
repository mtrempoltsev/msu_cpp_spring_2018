//#pragma once
#include <iostream>
#include <string>
class BigInt
{
    int *number;
    std::size_t length;
    std::size_t real_size;
    public:
    BigInt();
    BigInt(unsigned long long par);
    BigInt(const BigInt & par_BigInt);
    BigInt(BigInt&& par_delitable);
    ~BigInt();
    friend std::ostream& operator << (std::ostream& ot, const BigInt& X);
    friend std::istream& operator >> (std::istream& it, BigInt& X);
    void swap(BigInt &arg);
    BigInt& operator = (const BigInt & td);
    BigInt& operator = (BigInt && tp);
    void resize(std::size_t new_size);
    std::size_t get_real_size();
    friend const BigInt operator + (const BigInt & left, const BigInt & right);
    BigInt& operator += (const BigInt & td);
    friend const bool operator > (const BigInt & left, const BigInt & right);
    friend const bool operator < (const BigInt & left, const BigInt & right);
    friend const bool operator == (const BigInt & left, const BigInt & right);
    friend const bool operator != (const BigInt & left, const BigInt & right);
    friend const bool operator >= (const BigInt & left, const BigInt & right);
    friend const bool operator <= (const BigInt & left, const BigInt & right);
    friend const BigInt operator * (const BigInt & left, const BigInt & right);
    void shrink_to_fit();
    void check()
    {
        for (std::size_t i = 0; i < real_size; ++i)
            std::cout << number[i];
        std::cout << '\n';
    }
};

BigInt::BigInt() : number(new int[1]), length(1), real_size(1)
{
    number[0] = 0;
}
BigInt::BigInt(unsigned long long par)
{
    if (par == 0) {
        BigInt a;
        *this = a;
        return;
    }
    unsigned long long temp = par;
    std::size_t number_of_ints = 0;
    while (temp) {
        ++number_of_ints;
        temp /= 10;
    }
    number = new int[number_of_ints];
    std::size_t i = 0;
    int *temp_mas = new int[number_of_ints];
    while (par) {
        temp_mas[i] = par % 10;
        ++i;
        par /= 10;
    }
    for (i = 0; i < number_of_ints; ++i) {
        number[i] = temp_mas[number_of_ints - 1 - i];
    }
    real_size = length = number_of_ints;
}
BigInt::~BigInt()
{
    delete[] number;
    number = nullptr;
    real_size = length = 0;
}
BigInt::BigInt(const BigInt & par_BigInt)
    :number(new int[par_BigInt.real_size])
    ,length(par_BigInt.length)
    ,real_size(par_BigInt.real_size)
{
    for (std::size_t i = 0; i < real_size; ++i)
        number[i] = par_BigInt.number[i];
}
BigInt::BigInt(BigInt&& par_delitable)
    :number(new int[par_delitable.real_size])
    ,length(par_delitable.length)
    ,real_size(par_delitable.real_size)
{
    for (std::size_t i = 0; i < real_size; ++i)
        number[i] = par_delitable.number[i];
    par_delitable.~BigInt();
}
std::ostream& operator << (std::ostream& ot, const BigInt& X)
{
    for (std::size_t i = X.real_size - X.length; i < X.real_size; ++i)
        ot << X.number[i];
    return ot;
}
std::istream& operator >> (std::istream& it, BigInt& X)
{
    std::string s;
    it >> s;
    X.length = X.real_size = s.size();
    X.number = new int[X.length];
    for (std::size_t i = 0; i < X.length; ++i)
        X.number[i] = s[i] - '0';
    return it;
}
void BigInt::swap(BigInt &arg)
{
    std::swap(number, arg.number);
    std::swap(length, arg.length);
    std::swap(real_size, arg.real_size);
}
BigInt& BigInt::operator = (BigInt const &td)
{
    if (this != &td) {
        BigInt(td).swap(*this);
    }
    return *this;
}
BigInt& BigInt::operator = (BigInt && tp)
{
    if (this != &tp) {
        BigInt(tp).swap(*this);
    }
    tp.~BigInt();
    return *this;
}
const bool operator > (const BigInt & left, const BigInt & right)
{
    if (left.length > right.length)
        return true;
    if (left.length < right.length)
        return false;
    for (std::size_t i = 0; i < left.length; ++i) {
        if (left.number[i] > right.number[i])
            return true;
        if (left.number[i] < right.number[i])
            return false;
    }
    return false;
}
const bool operator < (const BigInt & left, const BigInt & right)
{
    return right > left;
}
const bool operator == (const BigInt & left, const BigInt & right)
{
    if (!(left > right) && !(left < right))
        return true;
    return false;
}
const bool operator != (const BigInt & left, const BigInt & right)
{
    return !(left == right);
}
const bool operator >= (const BigInt & left, const BigInt & right)
{
    return !(left < right);
}
const bool operator <= (const BigInt & left, const BigInt & right)
{
    return !(left > right);
}
std::size_t BigInt::get_real_size()
{
    return this->real_size;
}
void BigInt::resize(std::size_t new_size)
{
    int *temp = new int[new_size];
    for (std::size_t i = 0; i < new_size; ++i) {
        if (i < this->length)
            temp[new_size - 1 - i] = this->number[this->real_size - 1 - i];
        else
            temp[new_size - 1 - i] = 0;
    }
    delete[] this->number;
    this->number = temp;
    this->real_size = new_size;
    if (this->length > this->real_size)
        this->length = this->real_size;
}
const BigInt operator+(const BigInt &left, const BigInt &right)
{
    BigInt temp1, temp2;
    if (left > right) {
        temp1 = left;
        temp2 = right;
    } else {
        temp1 = right;
        temp2 = left;
    }
    temp1.resize(temp1.real_size + 1);
    std::size_t l1 = temp1.real_size, l2 = temp2.real_size;
    for (std::size_t i = 0; i < l2; ++i) {
        temp1.number[l1 - 1 - i] += temp2.number[l2 - 1 - i];
        if (temp1.number[l1 - 1 - i] / 10 != 0) {
            temp1.number[l1 - 2 - i] += temp1.number[l1 - 1 - i] / 10;
            temp1.number[l1 - 1 - i] %= 10;
        }
    }
    if (temp1.number[0]) {
        temp1.length = temp1.real_size;
    } else {
        temp1.length = temp1.real_size - 1;
    }
    temp1.shrink_to_fit();
    return temp1;
}
BigInt& BigInt::operator += (const BigInt & td)
{
    *this = *this + td;
    return *this;
}
const BigInt operator * (const BigInt & left, const BigInt & right)
{
    BigInt temp;
    if (left == temp || right == temp)
        return temp;
    temp.resize(left.length + right.length);
    BigInt templ(left), tempr(right);
    templ.shrink_to_fit();
    tempr.shrink_to_fit();
    for (std::size_t i = 0; i < templ.length; ++i)
        for (std::size_t j = 0; j < tempr.length; ++j)
            temp.number[i + j] += templ.number[i] * tempr.number[j];
    temp.check();
    for (int i = temp.real_size - 1; i > 0; --i)
        temp.number[i] = temp.number[i - 1];
    temp.check();
    temp.number[0] = 0;
    for (int i = temp.real_size - 1; i > 0; --i) {
        temp.number[i - 1] += temp.number[i] / 10;
        temp.number[i] %= 10;
    }
    temp.check();
    if (!temp.number[0]) {
        temp.length = temp.real_size - 1;
        temp.resize(temp.real_size - 1);
    } else {
        temp.length = temp.real_size;
    }
    return temp;
}
void BigInt::shrink_to_fit()
{
    this->resize(this->length);
    this->real_size = this->length;
}
