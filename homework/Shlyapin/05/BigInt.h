#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <cassert>

class BigInt
{
    short *number = nullptr;
    std::size_t length = 0;
    std::size_t real_size = 0;
    bool sign = false;
public:
    BigInt();
    BigInt(int64_t par);
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
    BigInt operator- () const;
    friend BigInt operator + (const BigInt & left, const BigInt & right);
    BigInt& operator += (const BigInt & td);
    friend BigInt operator- (const BigInt &left, const BigInt &right);
    BigInt& operator -= (const BigInt & td);
    friend BigInt operator * (const BigInt & left, const BigInt & right);
    BigInt& operator *= (const BigInt & td);
    //friend BigInt operator / (const BigInt &left, const BigInt &right)
    //{
      //  return BigInt(1);
    //}
    friend const bool operator > (const BigInt & left, const BigInt & right);
    friend const bool operator < (const BigInt & left, const BigInt & right);
    friend const bool operator == (const BigInt & left, const BigInt & right);
    friend const bool operator != (const BigInt & left, const BigInt & right);
    friend const bool operator >= (const BigInt & left, const BigInt & right);
    friend const bool operator <= (const BigInt & left, const BigInt & right);
    void shrink_to_fit();
    void check()
    {
        for (std::size_t i = 0; i < real_size; ++i)
            std::cout << number[i];
        std::cout << '\n';
    }
    void LevelUp();
    BigInt abs() const;
    friend BigInt operator / (const BigInt &a, const BigInt &b);
    void reverse();
    BigInt split(std::size_t sz);
    BigInt half() const;
};

BigInt::BigInt() : number(new short[1]), length(1), real_size(1)
{
    number[0] = 0;
}
BigInt::BigInt(int64_t par) : sign(par < 0)
{
    if (par == 0) {
        //BigInt a;
        *this = BigInt();//a;
        return;
    }
    unsigned long long temp = std::abs(par);
    std::size_t number_of_ints = 0;
    while (temp) {
        ++number_of_ints;
        temp /= 10;
    }
    number = new short[number_of_ints];
    std::size_t i = 0;
    short *temp_mas = new short[number_of_ints];
    temp = std::abs(par);
    while (temp) {
        temp_mas[i] = temp % 10;
        ++i;
        temp /= 10;
    }
    for (i = 0; i < number_of_ints; ++i) {
        number[i] = temp_mas[number_of_ints - 1 - i];
    }
    real_size = length = number_of_ints;

    /*std::string s = std::to_string(std::abs(par));
    real_size = length = s.length();
    number = new short[length];
    for (std::size_t i = 0; i < s.length(); ++i) {
        number[i] = s[i];
    }*/
}
BigInt::~BigInt()
{
    try {
        delete[] number;
    } catch (...) {
        std::cerr << "!!!ERROR!!!\n";
        assert(0);
    }
    number = nullptr;
    real_size = length = 0;
}
BigInt::BigInt(const BigInt & par_BigInt)
    :number(new short[par_BigInt.real_size])
    ,length(par_BigInt.length)
    ,real_size(par_BigInt.real_size)
    ,sign(par_BigInt.sign)
{
    for (std::size_t i = 0; i < real_size; ++i)
        number[i] = par_BigInt.number[i];
    this->shrink_to_fit();
}
BigInt::BigInt(BigInt&& par_delitable) :
    //    :number(new short[par_delitable.real_size])
    length(par_delitable.length)
    ,real_size(par_delitable.real_size)
    ,sign(par_delitable.sign)
{
    //    for (std::size_t i = 0; i < real_size; ++i)
    //        number[i] = par_delitable.number[i];
    //    par_delitable.~BigInt();
    std::swap(number, par_delitable.number);
}
std::ostream& operator << (std::ostream& ot, const BigInt& X)
{
    if (X.sign) ot << '-';
    for (std::size_t i = X.real_size - X.length; i < X.real_size; ++i)
        ot << X.number[i];

    /*for (std::size_t i = X.real_size - X.length; i < X.real_size; ++i)
      X.number[i] += '0';
      ot << X.number + X.real_size - X.length;
      for (std::size_t i = X.real_size - X.length; i < X.real_size; ++i)
      X.number[i] -= '0';*/
    return ot;
}
std::istream& operator >> (std::istream& it, BigInt& X)
{
    std::string s;
    it >> s;
    if (s[0] == '-')
        X.sign = true;
    else
        X.sign = false;
    X.length = X.real_size = s.size() - X.sign;
    delete[] X.number;
    X.number = new short[X.length];
    for (std::size_t i = 0; i < X.length; ++i)
        X.number[i] = s[i + X.sign] - '0';
    return it;
}
void BigInt::swap(BigInt &arg)
{
    std::swap(number, arg.number);
    std::swap(length, arg.length);
    std::swap(real_size, arg.real_size);
    std::swap(sign, arg.sign);
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
        tp.swap(*this);
    }
    //tp.~BigInt();
    return *this;
}
const bool operator > (const BigInt & left, const BigInt & right)
{
    if (left.sign != right.sign) {
        /*       if (left.sign) {
                 return false;
                 } else {
                 return true;
                 }*/
        return !left.sign;
    }
    bool res;
    if (left.length > right.length) {
        res = true;
        return left.sign ? !res : res;
    } else if (left.length < right.length) {
        res = false;
        return left.sign ? !res : res;
    } else {
        for (std::size_t i = 0; i < left.length; ++i) {
            if (left.number[i] > right.number[i]) {
                res = true;
                return left.sign ? !res : res;
            }
            if (left.number[i] < right.number[i]) {
                res = false;
                return left.sign ? !res : res;
            }
        }
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
    if (new_size == real_size) return;
    if (new_size == 0) {
        *this = BigInt();
        return;
    }
    short *temp = new short[new_size];
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
BigInt BigInt::operator- () const
{
    //this->sign = !this->sign;
    BigInt tmp(*this);
    tmp.sign = (tmp == BigInt(0)) ? tmp.sign : !tmp.sign;
    return tmp;
}
BigInt operator+(const BigInt &left, const BigInt &right)
{
//    std::cout << "Gone into +\n"; fflush(stdout);
    if (left.sign == right.sign) {
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
    } else {
        if (left.sign) {
            return right - (-left);
        } else {
            return left - (-right);
        }
    }
}
BigInt& BigInt::operator += (const BigInt & td)
{
    *this = *this + td;
    return *this;
}
BigInt operator- (const BigInt &left, const BigInt &right)
{
//    std::cout << "Gone into -\n"; fflush(stdout);
    if (left == right) {
//        std::cout << "==\n";
        return BigInt(0);
    }
    if (right.sign) {
        return left + (-right);
    }
    if (left.sign) {
        return -(-left + right);
    }
    if (left < right) {
        return -(right - left);
    }
    BigInt res(left);
    /*for (std::size_t i = res.real_size - 1; i >= res.real_size - right.length; --i) {
        int tmp = res.number[i] - right.number[i];
        if (tmp >= 0) {
            res.number[i] = tmp;
        } else {
            res.number[i] = tmp + 10;
            std::size_t j = i - 1;
            for (; res.number[j] == 0; --j) {
                res.number[j] = 9;
            }
            --res.number[j];
        }
        if (!i) {
            break;
        }
    }*/
    std::size_t rl = right.real_size;
    std::size_t ss = res.real_size;
    for (std::size_t i = 1; i <= right.length; ++i) {
        short tmp = res.number[ss - i] - right.number[rl - i];
        if (tmp >= 0) {
            res.number[ss - i] = tmp;
        } else {
            res.number[ss - i] = tmp + 10;
            std::size_t j = i + 1;
            for (; res.number[ss - j] == 0; ++j) {
                res.number[ss - j] = 9;
            }
            --res.number[ss - j];
        }
        /*if (!i) {
            break;
        }*/
    }
    //    std::size_t len = 0;
    for (std::size_t i = 0; i < res.real_size && res.number[i] == 0; ++i, --res.length) {};
    res.shrink_to_fit();
    //res.resize(res.length - len);
    return res;
}
BigInt& BigInt::operator -= (const BigInt & td)
{
    *this = *this - td;
    return *this;
}
BigInt operator * (const BigInt & left, const BigInt & right)
{
    BigInt temp;
    if (left == temp || right == temp)
        return temp;
    temp.sign = left.sign != right.sign;
    temp.resize(left.length + right.length);
    BigInt templ(left), tempr(right);
    templ.shrink_to_fit();
    tempr.shrink_to_fit();
//    std::cout << "cjeck: " << templ << ", " << tempr << std::endl;
    for (std::size_t i = 0; i < templ.length; ++i)
        for (std::size_t j = 0; j < tempr.length; ++j)
            temp.number[i + j] += templ.number[i] * tempr.number[j];
    //temp.check();
    for (std::size_t i = temp.real_size - 1; i > 0; --i)
        temp.number[i] = temp.number[i - 1];
    //temp.check();
    temp.number[0] = 0;
    for (std::size_t i = temp.real_size - 1; i > 0; --i) {
        temp.number[i - 1] += temp.number[i] / 10;
        temp.number[i] %= 10;
    }
    //temp.check();
    if (!temp.number[0]) {
        temp.length = temp.real_size - 1;
        temp.resize(temp.real_size - 1);
    } else {
        temp.length = temp.real_size;
    }
    return temp;
}
BigInt& BigInt::operator *= (const BigInt & td)
{
    *this = *this * td;
    return *this;
}
void BigInt::shrink_to_fit()
{
    if (length != real_size) {
        this->resize(this->length);
        this->real_size = this->length;
    }
}


void BigInt::LevelUp()
{
    for (int i = length;i>=1;i--)
        number[i] = number[i-1];
    if (number[length])
        length++;
}

BigInt BigInt::abs () const
{
    if (this->sign) {
        return -(*this);
    }
    return *this;
}

/*BigInt operator / (const BigInt &a, const BigInt &b)
{
    if (a.abs() < b.abs()) {
        return BigInt();
    } else if (a.abs() < 2 * b.abs()) {
        return a.sign == b.sign ? BigInt(1) : BigInt(-1);
    }
    BigInt res, curValue, ta(a), tb(b);
    ta.reverse();
    tb.reverse();
    for (int i = ta.length-1; i>=0; i--)
    {
        curValue.LevelUp(); // * osn
        curValue.number[0] = a.number[i];
        // подбираем максимальное число x, такое что b * x <= curValue
        int x = 0;
        int l = 0, r = 10;
        while (l <= r)
        {
            int m = (l + r) >> 1;
            BigInt cur = tb * m;
            if (cur <= curValue)
            {
                x = m;
                l = m+1;
            }
            else
                r = m-1;
        }
        res.number[i] = x;
        curValue = curValue - tb * x;
    }
    // избавляемся от лидирующих нулей
    int pos = ta.length;
    while (pos>=0 && !res.number[pos])
        pos--;
    res.length = pos+1;

    res.reverse();
    res.sign = a.sign != b.sign;
    res.real_size = ta.length;
    res.shrink_to_fit();

    return res;
}*/
void BigInt::reverse()
{
    for (std::size_t i = 0; i < real_size / 2; ++i) {
        number[i] ^= number[real_size - 1 - i];
        number[real_size - 1 - i] ^= number[i];
        number[i] ^= number[real_size - 1 - i];
    }
}
////////////////////////////////////////////////////////////////////

BigInt BigInt::split(std::size_t sz)
{
//    this->shrink_to_fit();
    if (sz >= this->real_size) {
        BigInt res = std::move(*this);
        this->real_size = this->length = 0;
        return res;
    }
    BigInt res;
    res.length = res.real_size = sz;
    try {
        res.number = new short[sz];
    } catch (...) {
        assert(0);
    }
    for (std::size_t i = this->real_size - this->length; i < this->real_size; ++i) {
        res.number[i] = this->number[i];
    }
    this->resize(this->length - sz);
    return res;
}

/*BigInt operator / (const BigInt &a, const BigInt &b)
{
    
    BigInt res, ta(a.abs()), tb(b.abs());
    if (ta < tb) {
        return BigInt();
    } else if (ta < 2 * tb) {
        return a.sign == b.sign ? BigInt(1) : BigInt(-1);
    } else if (tb == 1){
//        std::cout << '!';
        return b.sign ? -a : a;
    }
    res.sign = a.sign != b.sign;
//    std::cout << '!'; fflush(stdout);
    BigInt cr = ta.split(b.length);
//    std::cout << '!'; fflush(stdout);
    if (cr < tb) {
        cr = cr * 10 + ta.split(1);
//        std::cout << '?'; fflush(stdout);
    }
//    std::cout << ta;
    unsigned int q;
    std::size_t L = ta.length + 1;
//    std::cout << '!' << L << '!';
    for (std::size_t i = 0; i < L; ++i) {
//        std::cout << '.'; fflush(stdout);
        if (cr >= tb) {
            for (q = 1; tb * q <= cr; q += 1) {};
//            res = res * 10 + --q;
            cr -= tb * --q;
        } else {
            q = 0;
        }
        if (ta.number) {
//            std::cout << std::endl << ta << std::endl;
            cr = cr * 10 + ta.split(1);
        }
        res = res * 10 + q;
//        std::cout << std::endl << res << ' ' << q << std::endl;
    }// while (ta.number || cr >= tb);
    return res;
}*/

BigInt BigInt::half() const
{
    BigInt res(*this);
    for (std::size_t i = 0; i < res.real_size; ++i) {
        if ((res.number[i] & 1) == 0 || i + 1 == res.real_size) {
            res.number[i] /= 2;
        } else {
            res.number[i + 1] += 10;
            res.number[i] /= 2;
        }
    }
    if (res.length > 1 && !res.number[0]) {
        res.length--;
        res.shrink_to_fit();
    }
    return res;
}

BigInt operator / (const BigInt &a, const BigInt &b)
{
    if (a == BigInt()) {
        return BigInt();
    } else if (b == BigInt()) {
        throw -1;
    }
    BigInt res, ta(a.abs()), tb(b.abs());
    if (ta < tb) {
        return BigInt();
    } else if (ta < 2 * tb) {
        return a.sign == b.sign ? BigInt(1) : BigInt(-1);
    } else if (tb == 1){
        return b.sign ? -a : a;
    }
    
    BigInt left, right(ta);
    res = (left + right).half();
//    std::cout << '\n' << res << '\n';
    while (res * tb > ta || ta - res * tb >= tb) {
        if (res * tb > ta) {
            right = res;
        } else {
            left = res;
        }
        res = (left + right).half();
//        std::cout << '\n' << res << '\n';
    }
    res.sign = a.sign != b.sign;
    return res;
}
