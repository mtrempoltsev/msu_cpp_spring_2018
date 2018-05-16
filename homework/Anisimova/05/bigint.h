#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <utility>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <sstream>

class BigInt {

private:

    int64_t* data = nullptr;
    size_t size;
    int sign;

    void myFree(int64_t* data) {
        if (data != nullptr) {
            delete []data;
        }
    }
    
    void resize(size_t newSize) {
        int64_t* newData = (int64_t*) calloc(newSize, sizeof(int64_t));
        if (data != nullptr) {
            memcpy(newData, data, size);
            myFree(data);
        }
        size = newSize;
        data = newData;
    }

    void resize2(size_t z) {
        int64_t* newData = (int64_t*) calloc(size-z, sizeof(int64_t));
        if (data != nullptr) {
            std::copy(data+z, data + size, newData);
            delete []data;
        }
        size = size-z;
        data = newData;
    }

    void adapt_sizes(size_t s) {
        if (s <= size)
            return;
        int64_t* newData = (int64_t*) calloc(s, sizeof(int64_t));
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        size = s;
    }

    void adapt_sizes_dev(size_t s) {
        int64_t* newData = (int64_t*) calloc(s, sizeof(int64_t));
        std::copy(data, data + s, newData);
        delete[] data;
        data = newData;
        size = s;
    }

    void adapt_sizes_mult(size_t i, int64_t d) {
        int64_t* newData = (int64_t*) calloc(size+1, sizeof(int64_t));
        newData[0]=(data[size-i]+d)/10;
        newData[1]=(data[size-i]+d)%10;
        if (data != nullptr)
        {
            std::copy(data+1, data + size, newData+2);
            delete[] data;
        }
        size = size+1;
        data = newData;
    }

    void adapt_sizes_mult_1(size_t i, int64_t d) {
        int64_t* newData = (int64_t*) calloc(size+1, sizeof(int64_t));
        newData[0]=d;
        if (data != nullptr)
        {
            std::copy(data, data + size, newData+1);
            delete[] data;
        }
        size = size+1;
        data = newData;
    }

    void adapt_sizes_mult_10(size_t i, size_t max_s) {
        int64_t* newData = (int64_t*) calloc(size+max_s-i, sizeof(int64_t));
        if (data != nullptr)
        {
            std::copy(data, data + size, newData);
            delete []data;
        }
        if(i!=max_s)
        {
            newData[size+max_s-i-1]=0;
        }

        size = size+max_s-i;
        data = newData;
    }

    BigInt abs(const BigInt& x) const {
        BigInt answer(x);
        if (answer.sign < 0) {
            answer.sign = 1;
        }
        return answer;
    }



public:
    BigInt()
        : sign(0)
        , size(0)
        , data(nullptr) {
    }

    BigInt(const long long &x) {
        if (x == 0) {
            resize(1);
            data[0] = 0;
            sign = 0;
            size = 1;
        } else {
            sign = (x < 0 ? -1 : 1);
            std::ostringstream ost;
            int i;
            long long y = std::abs(x);
            ost << y;
            size=ost.str().size();
            resize(size);
            for(i=size;i>0;i--)
            {
                data[i-1]=y % 10;
                y /=10;
            }
        }
    }

    BigInt(const BigInt& other) {
        sign = other.sign;
        size = other.size;
        data = (int64_t*) calloc(size, sizeof(int64_t));
        std::copy(other.data, other.data + size, data);
    }


    BigInt(BigInt&& other)
        : sign(std::move(other.sign))
        , size(std::move(other.size))
        , data(std::move(other.data)) {
    }

    bool operator!=(const BigInt& other) const {
        if (sign != other.sign) {
            return true;
        }
        if (size != other.size) {
            return true;
        }
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const BigInt& other) const {
        return !operator!=(other);
    }

    BigInt& operator=(const BigInt& other) {
        sign = other.sign;
        size = other.size;
        myFree(data);
        data = (int64_t*) calloc(size, sizeof(int64_t));
        std::copy(other.data, other.data + size, data);
        return *this;
    }

    BigInt& operator=(BigInt&& other) {
        sign = std::move(other.sign);
        size = std::move(other.size);
        data = std::move(other.data);
        return *this;
    }

    bool operator<=(const BigInt& other) const {
        if (sign < other.sign) {
            return true;
        }
        if (sign > other.sign) {
            return false;
        }
        if (size < other.size) {
            return true;
        }
        if (size > other.size) {
            return false;
        }
        for (size_t i = 0; i <size; i++) {
            if (data[i] * sign < other.data[i] * other.sign) {
                return true;
            }
            if (data[i] * sign > other.data[i] * other.sign) {
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
        if (size < other.size) {
            return false;
        }
        if (size > other.size) {
            return true;
        }
        for (size_t i = 0; i <size; i++) {
            if (data[i] * sign < other.data[i] * other.sign) {
                return false;
            }
            if (data[i] * sign > other.data[i] * other.sign) {
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


    BigInt operator-(const BigInt& other) const {
        size_t z=0;
        size_t i=0;
        BigInt tmp, a(*this), b(other);
        if(a.sign==b.sign)
        {
            if(abs(a)==abs(b))
                return 0;
            if(abs(a) <abs(b))
            {
                tmp=a;
                a=b;
                b=tmp;
                a.sign=a.sign*(-1);
            }

            for(i=b.size;i>0 ;i--)
            {
                if(z!=0)
                    a.data[a.size-(b.size-i)-1]-=1;
                if((a.data[a.size-(b.size-i)-1]=a.data[a.size-(b.size-i)-1]-b.data[i-1])<0)
                {
                    a.data[a.size-(b.size-i)-1]+=10;
                    z=1;
                }
                else
                {
                    z=0;
                }
            }
            if(z!=0)
            {
                while((a.data[a.size-(b.size-i)-1]=a.data[a.size-(b.size-i)-1]-1)<0)
                {
                    a.data[a.size-(b.size-i)-1]+=10;
                    i--;
                }
            }
            z=0;
            for(i=0;i<a.size;i++)
            {
                if(a.data[i]==0)
                {
                    z++;
                }
                else
                {
                    break;
                }

            }
            a.resize2(z);
            return a;

        }
        else
        {
            return operator+(-other);

        }
        return a;
    }

    BigInt operator-() const {
        BigInt tmp(*this);
        if (size == 1 && data[0] == 0)
            return tmp;
        tmp.sign = (-1)*tmp.sign;
        return tmp;
    }

    BigInt operator+(const BigInt& other) const {
        BigInt tmp, a(*this), b(other);
        if (sign == 0) {
            return b;
        }
        if (other.sign == 0) {
            return a;
        }
        if (a.sign == b.sign) {
            size_t i=0;
            int64_t d=0;
            if(abs(a) <abs(b))
            {
                tmp=a;
                a=b;
                b=tmp;
            }
            for(i=0;i<b.size;i++)
            {
                if(d!=0)
                {
                    a.data[a.size-i-1]+=d;
                }
                d=a.data[a.size-i-1]+b.data[b.size-i-1];
                a.data[a.size-i-1]=d % 10;
                d /=10;
            }
            if(d!=0)
            {
                if(a.size!=b.size)
                {
                    if(a.data[a.size-i-1]+d>=10)
                    {
                        while((a.data[a.size-i-1]=a.data[a.size-i-1]+d)>=10)
                        {
                            d=a.data[a.size-i-1]/10;
                            a.data[a.size-i-1]=a.data[a.size-i-1]%10;
                            i++;
                            if(a.size-i==0)
                                break;
                        }

                        if(a.size-i==0 && d!=0)
                        {
                            a.adapt_sizes_mult_1(i,d);
                        }

                    }
                    else
                    {
                        a.data[a.size-i-1]+=d;
                    }

                }
                else
                {
                    a.adapt_sizes_mult_1(i,d);
                }

            }
            return a;
        }
        else
        {
            return operator-(-other);
        }
        return a;
    }

    BigInt operator*(const BigInt& other) const {
        BigInt res(0), tmp(0), a(*this), b(other);
        size_t i=0,j=0;
        int64_t z=0, s=0;
        if (a == 0 || b == 0) {
            return res;
        }
        if(a.size <(b.size))
        {
            tmp=a;
            a=b;
            b=tmp;
        }
        res.sign=1;
        for(i=b.size;i>0;i--)
        {
            tmp=0;
            tmp.sign=1;
            tmp.adapt_sizes(a.size);
            for(j=a.size;j>0;j--)
            {
                tmp.data[j-1]=(a.data[j-1]*b.data[i-1])%10;
                if(z!=0)
                {
                    if(tmp.data[j-1]+z>=10)
                    {
                        s=(tmp.data[j-1]+z);
                        tmp.data[j-1]=s%10;
                        z=s/10;
                    }
                    else
                    {
                        tmp.data[j-1]=tmp.data[j-1]+z;
                        z=0;
                    }

                }
                z+=(a.data[j-1]*b.data[i-1])/10;
            }
            if(z!=0)
            {
                tmp.adapt_sizes_mult_1(0,z);
                z=0;
            }
            tmp.adapt_sizes_mult_10(i, b.size);
            res=res+tmp;
        }
        res.sign = a.sign * b.sign;
        return res;
    }


    BigInt operator/(const BigInt& other) const {
        BigInt a(*this), b(other), c(0), res;
        if (abs(*this) < abs(other)) {
            return c;
        }
        if (b == 0) {
            return 0;
        }
        int64_t s=0, sr=0, z=0;
        size_t i=0, j=0, k=0, t=0;
        size_t f=0;
        res.sign=a.sign*b.sign;
        a.sign = 1;
        b.sign = 1;
        c.sign=1;
        res.adapt_sizes(a.size-b.size+1);
        for(j=0;j<a.size;j++)
        {
            c.data[j]=a.data[j];
            if(c>=b)
                break;
            else
            {
                c.adapt_sizes(c.size+1);
            }
        }
        if(c.size==a.size)
            f=1;
        for(s=1;s<10;s++)
        {
            if(b*s<=c && b*(s+1)>c)
                break;
        }
        res.data[k]=s;
        res.size=size-c.size+1;
        sr=s;
        for(t=0;t<a.size-j-1;t++)
        {
            s=s*10;
        }
        for(t=c.size;t<a.size;t++)
        {
            if(a.data[t]==0)
            {
                z++;
            }
            else
            {
                break;
            }

        }
        c=c-b*sr;
        a=a-b*s;
        k++;
        if(a<b)
        {
            if(f==1)
            {
                res.adapt_sizes_dev(k);
                return res;
            }
        }
        t=0;
        for(i=1;i<res.size;i++)
        {
            if(a<b)
            {
                res.data[k]=0;
                k++;
                break;
            }
            if(z!=0 && c==0)
            {
                for(t=0;t<z;t++)
                {
                    res.data[k]=0;
                    k++;
                    i=i+1;
                }
            }
            if(c==0)
            {
                c=a.data[c.size-1];
            }
            else
            {
                c.adapt_sizes(c.size+1);
                c.data[c.size-1]=a.data[c.size-1];
            }
            if(c<b)
            {
                res.data[k]=0;
                k++;
            }
            else
            {
                for(s=1;s<10;s++)
                {
                    if(b*s<=c && b*(s+1)>c)
                        break;
                }
                res.data[k]=s;
                k++;
                sr=s;
                for(t=0;t<a.size-c.size;t++)
                {
                    s=s*10;
                }
                z=0;
                for(t=c.size;t<a.size;t++)
                {
                    if(a.data[t]==0)
                    {
                        z++;
                    }
                    else
                    {
                        break;
                    }
                }
                a=a-b*s;
                c=c-b*sr;
            }
        }

        return res;
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
        for (size_t i = 0; i < value.size; i++) {
            out << static_cast<int>(value.data[i]);
        }
    }
    return out;
}
