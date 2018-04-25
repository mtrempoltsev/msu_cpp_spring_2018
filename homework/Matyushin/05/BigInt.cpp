#include <iostream>
#include "math.h"

class BigInt {
private:
    long int length;
    long int pos;
    bool positive;
    int* grs;
    
    void deepcopy(int deltalength){
        int* tmp = new int[length + deltalength];
        for (int t = 0; t < length; t++)
            tmp[t] = grs[t];
        for (int t = length; t < length + deltalength; t++)
            tmp[t] = 0;
        grs = new int[length + deltalength];
        for (int t = 0; t < length + deltalength; t++)
            grs[t] = tmp[t];
        length = length + deltalength;
        delete[] tmp;
    }
    
    bool absLe(const BigInt& other) const{
        //true if abs(this) >= abs(other)
        if (pos > other.pos){
            return true;
        }
        if (pos < other.pos){
            return false;
        }
        
        for (long int t = pos - 1; t >= 0; t--){
            if (grs[t] > other.grs[t]){
                return true;
            }
            if (grs[t] < other.grs[t]){
                return false;
            }
        }
        
        return true;
    }
    
    bool absEq(const BigInt& other) const{
        //true if abs(this) == abs(other)
        if ((pos > other.pos) || (pos < other.pos)){
            return false;
        }
        for (long int t = 0; t < pos; t++)
            if ((grs[t] > other.grs[t]) || (grs[t] < other.grs[t]))
                return false;
        
        return true;
    }
    
    void absPlus(const BigInt& other){
        long int minpos = pos;        
        if (other.pos < pos){
            minpos = other.pos;
        }
        
        int nextgr = 0;
        long int t = 0;
        for (t = 0; t < minpos; t++){
            int sum = other.grs[t] + grs[t] + nextgr;
            int thisgr = sum % 10000;
            nextgr = sum / 10000;
            grs[t] = thisgr;
        }
        
        while (nextgr > 0){
            if (t == pos){
                pos++;
                if (pos > length)
                    deepcopy(1);
            }
            int sum = grs[t] + nextgr;
            int thisgr = sum % 10000;
            nextgr = sum / 10000;
            grs[t] = thisgr;
            t++;
        }
    }
    
    void absMinus(const BigInt& other){
        long int minpos = pos;        
        if (other.pos < pos)
            minpos = other.pos;
        
        int nextgr = 0;
        long int tpos = 0;
        long int t = 0;
        for (t = 0; t < minpos; t++){
            int diff = grs[t] - other.grs[t] - nextgr;
            int thisgr = diff;
            nextgr = 0;
            while (thisgr < 0){
                thisgr = thisgr + 10000;
                nextgr++;
            }
            grs[t] = thisgr;
            if (grs[t] > 0)
                tpos = t + 1;
        }
        
        while (nextgr > 0){
            int diff = grs[t] - nextgr;
            int thisgr = diff;
            nextgr = 0;
            while(thisgr < 0){
                thisgr = thisgr + 10000;
                nextgr++;
            }
            grs[t] = thisgr;
            if (grs[t] > 0)
                tpos = t + 1;
            t++;
        }
        if (t == pos)
            pos = tpos;
    }
public:
    BigInt():
    length(1),
    pos(0){
        positive = true;
        grs = new int[1];
        grs[0] = 0;
    }

    BigInt(int init){
        if (init == 0){
            pos = 0;
            length = 1;
            grs = new int[length];
            grs[0] = 0;
            positive = true;
        }
        else{
            length = (long int)(log(abs(init))/log(10000)) + 1;
            grs = new int[length];
            int tmp = abs(init);
            int t = 0;
            while (tmp > 0){
                grs[t] = tmp % 10000;
                tmp = tmp / 10000;
                t++;
            }
            pos = t;
            if (init >= 0){
                positive = true;
            }
            else{
                positive = false;
            }
        }
    }
    
    BigInt(const BigInt& other){
        length = other.length;
        pos = other.pos;
        positive = other.positive;
        grs = new int[length];
        for (int t = 0; t < length; t++)
            grs[t] = other.grs[t];
    }
    
    BigInt& operator=(const BigInt& other){
        length = other.length;
        pos = other.pos;
        positive = other.positive;
        grs = new int[length];
        for (int t = 0; t < length; t++)
            grs[t] = other.grs[t];
        
        return *this;
    }
    
    BigInt(BigInt&& other){
        length = std::move(other.length);
        pos = std::move(other.pos);
        positive = std::move(other.positive);
        grs = new int[length];
        for (int t = 0; t < length; t++)
            grs[t] = std::move(other.grs[t]);
    }
    
    BigInt& operator=(BigInt&& other){
        length = std::move(other.length);
        pos = std::move(other.pos);
        positive = std::move(other.positive);
        grs = new int[length];
        for (int t = 0; t < length; t++)
            grs[t] = std::move(other.grs[t]);
        
        return *this;
    }
    
    ~BigInt(){
        delete[] grs;
    }
    
    BigInt& operator-() const{
        BigInt* res = new BigInt(*this);
        if (*res != 0)
            res->positive = !res->positive;
        return *res;
    }
    
    BigInt& operator+(const BigInt& other) const{
        BigInt* res = new BigInt(*this);
        if (positive && other.positive){
            if (absLe(other)){
                *res = *this;
                res->absPlus(other);
            }
            else
                *res = other + *this;
        }
        else if (!positive && other.positive){
            if (absLe(other))
                *res = -((-(*this)) + (-other));
            else{
                *res = other;
                res->absMinus(*this);
            }
        }
        else if (positive && !other.positive){
            if (absLe(other)){
                *res = *this;
                res->absMinus(other);
            }
            else{
                *res = -((-other) + (-(*this)));
            }
        }
        else
            *res = -((-other) + (-(*this)));
        
        if (res->pos == 0)
            res->positive = true;
        
        return *res;
    }
    
    BigInt& operator-(const BigInt& other) const{
        return (*this) + (-other);
    }
    
    BigInt& operator*(const BigInt& other) const{
        if (!absLe(other))
            return other*(*this);
        if (!other.positive)
            return -((*this)*(-other));
        if (!positive)
            return -((-(*this))*other);
        
        BigInt* res = new BigInt(0);
        BigInt t = 0;
        while (t < other){
            *res = *res + (*this);
            t = t + 1;
        }
        
        return *res;
    }
    
    BigInt& operator/(const BigInt& other) const{
        if (!positive)
            return -((-(*this))/other);
        if (!other.positive)
            return -((*this)/(-other));
        
        BigInt* res = new BigInt(-1);
        BigInt tmp = 0;
        while (tmp <= (*this)){
            tmp = tmp + other;
            *res = *res + 1;
        }
        
        return *res;
    }
    
    bool operator>(const BigInt& other) const{
        
        if (positive && other.positive){
            if (absLe(other) && ((*this) != other))
                return true;
            return false;
        }
        if (!positive && !other.positive){
            if (absLe(other) || ((*this) == other))
                return false;
            return true;
        }
        if (positive && !other.positive)
            return true;
        
        return false;
    }
    
    bool operator<(const BigInt& other) const{
        return -(*this) > (-other);
    }
    
    bool operator>=(const BigInt& other) const{
        return !((*this) < other);
    }
    
    bool operator<=(const BigInt& other) const{
        return !((*this) > other);
    }
    
    bool operator==(const BigInt& other) const{
        if ((positive && !other.positive) || (!positive && other.positive))
            return false;
        return absEq(other);
    }
    
    bool operator!=(const BigInt& other) const{
        return !((*this) == other);
    }
    
    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
};

std::ostream& operator<<(std::ostream& out, const BigInt& value){
    if (value.pos == 0)
        out << 0;
    if (!value.positive)
        out << '-';
    for (int t = value.pos - 1; t >= 0; t--){
        if (t < value.pos - 1)
            for (int null = 0; null < log10(10000/value.grs[t]) - 1; null++)
                out << 0;
        out << value.grs[t];
    }
}
