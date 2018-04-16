#include <ostream>
using std::ostream;

const int BASE = 10;

class BigInt
{
        friend ostream &operator<< (ostream &, const BigInt &);
    private:
        int mr;
        int size_BI;
        char *ptr;
        int zn;
        char &operator[] (int);
        char operator[] (int) const;
        void change_sz(int);
        void shift();
    public:
        BigInt();
        BigInt(long long);
        BigInt(const BigInt&);
        BigInt& operator=(const BigInt&);
        ~BigInt();

        BigInt operator-() const;
        BigInt operator+ (const BigInt &) const;
        BigInt &operator+= (const BigInt &);
        BigInt operator- (const BigInt &) const;
        BigInt &operator-= (const BigInt &);
        BigInt operator* (int) const;
        BigInt operator* (const BigInt &) const;
        BigInt operator/ (const BigInt &) const;
        bool operator< (const BigInt &) const;
        bool operator> (const BigInt &) const;
        bool operator<= (const BigInt &) const;
        bool operator>= (const BigInt &) const;
        bool operator== (const BigInt &) const;
        bool operator!= (const BigInt &) const;
};

BigInt::BigInt()
{
    size_BI = 1;
    mr = 16;
    zn = 0;
    ptr = new char[16];
    ptr[0] = 0;
}

BigInt::BigInt(long long a)
{
    if(a < 0){
        a = -a;
        zn = 1;
    }else
        zn = 0;
    long long b = a;
    size_BI = 1;
    while(b >= BASE)
    {
        size_BI++;
        b /= BASE;
    }
    mr = 16;
    while(mr < size_BI)
        mr *= 2;
    ptr = new char[mr];
    for(int i = 0; i < size_BI; ++i){
        ptr[i] = a % BASE;
        a /= BASE;
    }
    for(int i = size_BI; i < mr; ++i)
        ptr[i] = 0;
}

BigInt::BigInt (const BigInt &copied)
{
    mr = copied.mr;
    size_BI = copied.size_BI;
    zn = copied.zn;
    ptr = new char[mr];
    for(int i = 0; i < mr; i++)
        ptr[i] = copied[i];
}

BigInt &BigInt::operator=(const BigInt &copied)
{
    delete [] ptr;
    size_BI = copied.size_BI;
    zn = copied.zn;
    mr = copied.mr;
    ptr = new char[mr];
    for(int i = 0; i < copied.mr; i++)
        ptr[i] = copied[i];
    return *this;
}

BigInt::~BigInt()
{
    delete [] ptr;
}

ostream &operator<< (ostream &out, const BigInt &obj)
{
    if(obj.zn == 1)
        out << '-';
    out << obj[obj.size_BI-1]-0;
    for(int i = obj.size_BI - 2; i >= 0; --i){
        out << obj[i]-0;
    }
    return out;
}

void BigInt::change_sz(int f)
{
    BigInt tmp = *this;
    if(f)
        mr *= 2;
    else
        mr /= 2;
    delete[] ptr;
    ptr = new char[mr];
    for(int i = 0; i < tmp.size_BI; ++i)
        ptr[i] = tmp.ptr[i];
    for(int i = tmp.size_BI; i < mr; ++i)
        ptr[i] = 0;
}

void BigInt::shift()
{
    if(size_BI == mr)
        change_sz(1);
    size_BI++;
    for(int i = size_BI - 1; i > 0; --i)
        ptr[i] = ptr[i - 1];
    ptr[0] = 0;
}

BigInt BigInt::operator-() const
{
    BigInt tmp = *this;
    if(*this != 0)
        tmp.zn ^= 1;
    return tmp;
}

char &BigInt::operator[] (int i)
{
    return ptr[i];
}

char BigInt::operator[] (int i) const
{
    return ptr[i];
}

BigInt BigInt::operator+ (const BigInt &right) const
{
    if(right == 0)
        return *this;
    if(zn == right.zn){
        if(size_BI < right.size_BI)
            return (right + *this);
        BigInt tmp = *this;
        int ost = 0;
        for(int i = 0; i < right.size_BI; ++i){
            tmp[i] += right[i] + ost;
            ost = tmp[i] / BASE;
            tmp[i] %= BASE;
        }
        int i = right.size_BI;
        while(ost != 0){
            if(i >= tmp.mr)
                tmp.change_sz(1);
            tmp[i] += ost;
            ost = tmp[i] / BASE;
            tmp[i] %= BASE;
            i++;
        }
        tmp.size_BI = (i < tmp.size_BI) ? tmp.size_BI : i;
        return tmp;
    }else
        return (*this - (-right));
}

BigInt &BigInt::operator+= (const BigInt &right)
{
    *this = *this + right;
    return *this;
}

BigInt BigInt::operator- (const BigInt &right) const
{
    if(right == 0)
        return *this;
    if(zn == right.zn){
        if(*this == right)
            return 0;
        if((!zn) == (*this < right))
            return -(right - *this);
        BigInt tmp = *this;
        int ost = 0;
        for(int i = 0; i < right.size_BI; ++i){
            tmp[i] -= right[i] + ost;
            ost = 0;
            while(tmp[i] < 0){
                ost++;
                tmp[i] += BASE;
            }
        }
        int i = right.size_BI;
        tmp[i] -= ost;
        while(tmp[i] < 0){
            tmp[i] += BASE;
            ost = 1;
            i++;
            tmp[i] -= ost;
        }
        while(tmp[tmp.size_BI-1] == 0 && tmp.size_BI != 1)
            tmp.size_BI--;
        while(tmp.size_BI < (tmp.mr / 2) && tmp.mr != 32)
            tmp.change_sz(0);
        return tmp;
    }else
        return (*this + (-right));
}

BigInt &BigInt::operator-= (const BigInt &right)
{
    *this = *this - right;
    return *this;
}

BigInt BigInt::operator* (int right) const //right <= BASE
{
    BigInt tmp = *this;
    if(right == 0 || tmp == 0)
        return 0;
    if(right < 0){
        tmp.zn ^= 1;
        right = -right;
    }
    int ost = 0;
    for(int i = 0; i < tmp.size_BI; ++i){
        tmp[i] *= right;
        tmp[i] += ost;
        ost = tmp[i] / BASE;
        tmp[i] %= BASE;
    }
    int i = tmp.size_BI;
    while(ost != 0){
        if(i >= tmp.mr)
            tmp.change_sz(1);
        tmp[i] += ost;
        ost = tmp[i] / BASE;
        tmp[i] %= BASE;
        i++;
    }
    tmp.size_BI = (i < tmp.size_BI) ? tmp.size_BI : i;
    return tmp;
}

BigInt BigInt::operator* (const BigInt &right) const
{
    if(right == 0 || *this == 0)
        return 0;
    BigInt tmp(0), k, pr = *this;
    pr.zn = 0;
    for(int i = 0; i < right.size_BI; ++i){
        k = pr * right[i];
        for(int j = 0; j < i; ++j){
            k.shift();
        }
        tmp += k;
    }
    tmp.zn = zn ^ right.zn;
    return tmp;
}

BigInt BigInt::operator/ (const BigInt &right) const
{
    if(*this == 0)
        return 0;
    BigInt otv(0), del = *this, rig = right;
    rig.zn = 0;
    del.zn = 0;
    while(del >= rig){
        BigInt tmp(rig), sh_tmp(rig), tmp_otv(1);
        int j = 0;
        sh_tmp.shift();
        while(del > sh_tmp){
            tmp = sh_tmp;
            tmp_otv.shift();
            sh_tmp.shift();
        }
        while(del >= tmp){
            del -= tmp;
            ++j;
        }
        otv += tmp_otv * j;
    }
    otv.zn = zn ^ right.zn;
    if(-otv == 0)
        otv.zn = 0;
    return otv;
}

bool BigInt::operator== (const BigInt &right) const
{
    if(this == &right)
        return 1;
    else{
        if((zn == right.zn) && (size_BI == right.size_BI)){
            for(int i = 0; i < size_BI; ++i)
                if(ptr[i] != right[i])
                    return 0;
        }else
            return 0;
    }
    return 1;
}

bool BigInt::operator< (const BigInt &right) const
{
    if(*this == right)
        return 0;
    if(zn > right.zn)
        return 1;
    if(zn < right.zn)
        return 0;
    if (size_BI > right.size_BI)
        return 0 ^ zn;
    else
    if(size_BI < right.size_BI)
        return 1 ^ zn;
    for(int i = size_BI - 1; i >= 0; --i)
        if(ptr[i] > right[i])
            return 0 ^ zn;
        else if(ptr[i] < right[i])
            return 1 ^ zn;
    return 0;
}

bool BigInt::operator> (const BigInt &right) const
{
    if(*this == right)
        return 0;
    return !(*this < right);
}

bool BigInt::operator>= (const BigInt &right) const
{
    if(*this == right)
        return 1;
    return (*this > right);
}

bool BigInt::operator<= (const BigInt &right) const
{
    if(*this == right)
        return 1;
    return (*this < right);
}

bool BigInt::operator!=(const BigInt &right) const
{
    return !(*this == right);
}
