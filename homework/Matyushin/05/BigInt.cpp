#include <iostream>
#include "math.h"

class BigInt{
private:
    bool sign = false;
    long int pos = 0;
    long int length = 64;
    char* grs = nullptr;

    void extend(){
        char* tmp = new char[2*length];
        
        std::copy(grs, grs+pos, tmp);
        length *= 2;
        
        delete[] grs;
        
        grs = tmp;
    }

    void pushBack(char el){
        grs[pos++] = el;
        
        if(pos == length)
            this->extend();
    }

    void pushFront(char el){
        for(long int i = pos; i > 0; i--)
            grs[i] = grs[i-1];
        
        pos++;
        
        if(pos==length)
            this->extend();

        grs[0] = el;
    }

    char pop(){
        pos--;
        return grs[pos];
    }

    void nullCheck(){
        if ((pos == 1) && (grs[0] == 0))
            sign = false;
    }

    void trim(){
        for(long int i = pos - 1; i > 0; i--){
            if (grs[i] != 0)
                break;
            
            pos--;
        }
    }

    char divSearch(BigInt &d, BigInt &D) const{
        char res = 0;
        char bot = 0;
        char top = 10;

        while (bot <= top){
            char curr = (bot + top) / 2;
            if (BigInt(curr) * d <= D){
                res = curr;
                bot = curr + 1;
            }
            else
                top = curr - 1;
        }
        return res;
    }

public:
    BigInt():
            sign(false),
            pos(0){
        grs = new char[length];
        pushBack(0);
    }

    BigInt(int64_t init){
        grs = new char[length];
        
        if(init == 0){
            sign = false;
            pushBack(0);
            return;
        }

        if(init < 0){
            sign = true;
            init *= -1;
        }

        while(init > 0){
            pushBack(init % 10);
            init /= 10;
        }

    }

    BigInt(BigInt&& other):
                          sign(other.sign),
                          pos(other.pos),
                          length(other.length),
                          grs(other.grs){
        other.grs = new char[length];
        other.pushBack(0);
    }

    BigInt(const BigInt& other):
                                 length(other.length),
                                 pos(other.pos),
                                 sign(other.sign){
        grs = new char[length];
        std::copy(other.grs, other.grs + other.pos, grs);
    }

    bool operator==(const BigInt& other) const{
        if ((pos != other.pos) || (sign != other.sign))
            return false;
        
        for (long int i = 0; i < pos; i++)
            if (grs[i] != other.grs[i])
                return false;
        
        return true;
    }

    bool operator!=(const BigInt& other) const{
        return !(*this == other);
    }

    BigInt& operator=(const BigInt& other){
        length = other.length;
        sign = other.sign;
        pos = other.pos;
        
        delete[] grs;
        grs = new char[length];
        std::copy(other.grs, other.grs + other.pos, this->grs);
        
        return *this;
    }

    BigInt& operator=(BigInt&& other){
        length = other.length;
        sign = other.sign;
        pos = other.pos;
        
        delete[] grs;
        grs = other.grs;
        
        other.grs = nullptr;
        
        return *this;
    }

    bool operator>(const BigInt& other) const{
        if ((sign != other.sign) || (pos > other.pos))
            return !sign;
        
        if (pos < other.pos)
            return sign;
        
        for (long int i = pos - 1; i >= 0; i--){
            if (grs[i] < other.grs[i])
                return sign;
            
            else if (grs[i] > other.grs[i])
                return !sign;
        }
        
        return false;
    }

    bool operator<(const BigInt& other) const{
        if ((sign != other.sign) || (pos > other.pos))
            return sign;
        
        if (pos < other.pos)
            return !sign;
        
        for (long int i = pos - 1; i >= 0; i--){
            if (grs[i] > other.grs[i])
                return sign;
            
            else if (grs[i] < other.grs[i])
                return !sign;
        }
        
        return false;
    }

    bool operator<=(const BigInt& other) const{
        return !(*this > other);
    }

    bool operator>=(const BigInt& other) const{
        return !(*this < other);
    }

    BigInt abs() const{
        BigInt tmp = *this;
        tmp.sign = false;
        
        return tmp;
    }

    BigInt operator-() const{
        BigInt tmp(*this);
        tmp.sign = !sign;
        
        tmp.nullCheck();
        
        return tmp;
    }

    BigInt operator+(const BigInt& other) const{
        if (sign != other.sign)
            return sign ? (other - this->abs()) : (*this - other.abs());

        BigInt res(*this);
        
        for (long int i = res.pos; i < other.pos; i++)
            res.pushBack(0);
        
        char remaining = 0;
        char sum = 0;
        
        for (long int i = 0; i < other.pos; i++){
            sum = res.grs[i] + other.grs[i] + remaining;
            
            res.grs[i] = sum % 10;
            remaining = sum / 10;
        }
        
        for (long int i = other.pos; i < res.pos; i++){
            sum = res.grs[i] + remaining;
            
            res.grs[i] = sum%10;
            remaining = sum/10;
        }
        
        if (remaining > 0)
            res.pushBack(remaining);
        
        res.trim();
        res.nullCheck();
        
        return res;
    }

    BigInt operator-(const BigInt& other) const{
        if (sign != other.sign)
            return sign ? (-(this->abs() + other)) : (*this + other.abs());

        if (sign)
            return (other.abs() + *this);
        if (*this < other)
            return -(other - *this);

        BigInt res(*this);
        char remaining = 0;
        char dif = 0;

        for (long int i = 0; i < other.pos; i++){
            dif = grs[i] - other.grs[i] - remaining;
            
            if(dif < 0){
                res.grs[i] = dif + 10;
                remaining = 1;
            }
            
            else{
                res.grs[i] = dif;
                remaining = 0;
            }
        }
        
        for (long int i = other.pos; i < pos; i++){
            dif = grs[i] - remaining;
            
            if(dif < 0){
                res.grs[i] = dif + 10;
                remaining = 1;
            }
            
            else{
                res.grs[i] = dif;
                remaining = 0;
            }
        }
        
        res.trim();
        res.nullCheck();

        return res;
    }

    BigInt operator*(const BigInt& other) const{
        BigInt res;
        char remaining = 0;
        char mult = 0;

        for (long int i = 0; i < other.pos; i++){
            BigInt step;
            step.pop();
            remaining = 0;
            for(long int j = 0; j < i; j++)
                step.pushBack(0);
            for(long int j = 0; j < pos; j++){
                mult = grs[j]*other.grs[i] + remaining;
                step.pushBack(mult%10);
                remaining = mult/10;
            }
            
            if (remaining > 0)
                step.pushBack(remaining);
            res = res + step;

        }

        res.sign = (sign != other.sign);
        res.trim();
        res.nullCheck();
        
        return res;
    }


    BigInt operator/(const BigInt& other) const{
        BigInt res;
        
        BigInt tmp;
        tmp.pop();
        
        BigInt aother = other.abs();
        
        for (long int i = 0; i < pos; i++){
            tmp.pushFront(grs[pos - 1 - i]);
            tmp.trim();
            
            char div = divSearch(aother, tmp);
            
            res.pushFront(div);
            
            tmp = tmp - aother * BigInt(div);
        }
        
        res.trim();
        res.sign = (sign != other.sign);
        res.nullCheck();
        
        return res;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& other){
        if (other.sign)
            out << '-';
        for (long int i = other.pos - 1; i >= 0; i--)
            out << static_cast<char>('0' + other.grs[i]);
        
        return out;
    }
    
    ~BigInt(){
        delete [] grs;
    }
};
