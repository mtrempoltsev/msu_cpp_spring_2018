#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <limits>
#include <limits>
#include <algorithm>
class BigInt {
public:

    BigInt(const std::string str){
        initStr(str);
    }
    BigInt(int64_t number = 0){
        if(number == 0) {
            _init();
        }
        else
            initStr(std::to_string(number));
    }
    BigInt(const BigInt& other){
        mCapacity = other.mCapacity;
        mNumbers = new char[mCapacity];
        std::memcpy(mNumbers, other.mNumbers, sizeof(char)*other.mCapacity);
        isPositive = other.isPositive;
        isStringRepresentActuale = other.isStringRepresentActuale;
        if(isStringRepresentActuale)
            mStringRepresent = other.mStringRepresent;
    }
    BigInt&operator=(const BigInt& other){
        mCapacity = other.mCapacity;
        delete[] mNumbers;
        mNumbers = new char[mCapacity];
        std::memcpy(mNumbers, other.mNumbers, sizeof(char)*other.mCapacity);
        isPositive = other.isPositive;
        isStringRepresentActuale = other.isStringRepresentActuale;
        if(isStringRepresentActuale)
            mStringRepresent = other.mStringRepresent;
        return *this;
    }


    size_t getCapacity() const{
        return mCapacity;
    }
    const std::string& getString() const{
        if(isStringRepresentActuale)
            return mStringRepresent;
        else{
            buildStringRepresent();
            return mStringRepresent;
        }
    }
    ~BigInt(){
        delete[] mNumbers;
    }
    BigInt operator-() const{
        BigInt out(*this);
        out.isPositive = !out.isPositive;
        out.isStringRepresentActuale = false;
        return out;
    }
    BigInt operator-(const BigInt& other) const{
        return *this + (-other);
    }
    BigInt operator+(const BigInt& other) const{
        BigInt out;
        if(other.isPositive == isPositive){
            char* deltas = this->sum(mNumbers, other.mNumbers, mCapacity, other.mCapacity);
            size_t maxLength = std::max(mCapacity, other.mCapacity);
            for(int i =0; i< maxLength; i++){
                if(deltas[i] >= MODULE) {
                    deltas[i] -= MODULE;
                    deltas[i+1]+=1;
                }
            }
            delete[] out.mNumbers;
            out.mNumbers = deltas;
            out.mCapacity = maxLength+1;
            out.isPositive = isPositive;
        } else{
            char* deltas;
            bool positive;
            if(abs(*this) > abs(other)) {
                positive = true;
                deltas = this->difference(mNumbers, other.mNumbers, mCapacity, other.mCapacity);
            } else {
                positive = false;
                deltas = this->difference(other.mNumbers, mNumbers, other.mCapacity, mCapacity);
            }
            size_t maxLength = std::max(mCapacity, other.mCapacity);
            size_t endIndex = getEndIndex(deltas, maxLength);
            for(int i =0; i <= endIndex; i++){
                if(i<endIndex) {
                    if(deltas[i]<0) {
                        deltas[i] += MODULE;
                        deltas[i + 1] -= 1;
                    }
                }
            }
            out.isPositive = isPositive == positive;
            delete[] out.mNumbers;

            out.mNumbers = deltas;
            out.mCapacity = maxLength+1;
        }
        out.isStringRepresentActuale = false;
        return out;
    }

    BigInt operator*(const BigInt& other) const{
        char trans;
        char sum;
        size_t i, j = 0;
        BigInt a = 0;
        const BigInt* const big = mCapacity>other.mCapacity?this:&other;
        const BigInt* const small = mCapacity>other.mCapacity?&other:this;
        size_t lenBig = getEndIndex((*big).mNumbers,(*big).mCapacity)+1;
        size_t lenSmall= getEndIndex((*small).mNumbers, (*small).mCapacity)+1;
        for(i =0; i < lenSmall; i++){
            BigInt tmp = 0;
            trans = 0;
            for(j = 0; j < lenBig; j++){
                sum = big->mNumbers[j]*small->mNumbers[i] + trans;

                trans = sum/MODULE;
                if(tmp.mCapacity <= i+j)
                    tmp.resize((i+j)*2);
                tmp.mNumbers[i+j] = (sum % MODULE);
            }

            if(tmp.mCapacity <= i+j)
                tmp.resize((i+j)*2);
            tmp.mNumbers[i+j] = trans;
            a = a + tmp;
        }
        a.isPositive = isPositive == other.isPositive;
        a.isStringRepresentActuale = false;
        return a;
    }

    bool operator >(const BigInt& other) const{
        if(isPositive == !other.isPositive)
            return isPositive;
        size_t endIndexThis = getEndIndex(mNumbers,mCapacity);
        size_t endIndexOther= getEndIndex(other.mNumbers, other.mCapacity);
        if(endIndexThis != endIndexOther)
            return (endIndexThis > endIndexOther) == isPositive;
        for(int i =endIndexThis; i>=0; i--)
            if(mNumbers[i] != other.mNumbers[i])
                return (mNumbers[i] > other.mNumbers[i]) == isPositive;
        return false;
    }
    bool operator <=(const BigInt& other) const{
        return !(*this > other);
    }
    bool operator < (const BigInt other) const{
        if(isPositive == !other.isPositive)
            return other.isPositive;
        size_t endIndexThis  = getEndIndex(mNumbers,mCapacity);
        size_t endIndexOther = getEndIndex(other.mNumbers, other.mCapacity);
        if(endIndexThis != endIndexOther)
            return (endIndexThis < endIndexOther) == isPositive;
        for(int i =endIndexThis; i>=0; i--)
            if(mNumbers[i] != other.mNumbers[i])
                return (mNumbers[i] < other.mNumbers[i]) == isPositive;
        return false;
    }

    bool operator >=(const BigInt& other) const{
        return !(*this < other);
    }
    bool operator ==(const BigInt& other) const{
        size_t endIndexThis  = getEndIndex(mNumbers,mCapacity);
        size_t endIndexOther = getEndIndex(other.mNumbers, other.mCapacity);
        if(endIndexThis != endIndexOther)
            return false;
        for(int i =0; i<= endIndexThis; i++)
            if(mNumbers[i] != other.mNumbers[i])
                return false;
        return true;
    }
    bool operator !=(const BigInt& other) const{
        return !(*this == other);
    }
    friend BigInt abs(const BigInt& bigInt){
        BigInt out = bigInt;
        out.isPositive = true;
        out.isStringRepresentActuale = false;
        return out;
    }
    BigInt operator/(const BigInt& other) const{
        BigInt dividend = abs(*this);
        if((isPositive?*this:dividend) < (other.isPositive?other:abs(other)))
            return 0;
        BigInt out = 0;
        size_t endIndexThis  = getEndIndex(mNumbers,mCapacity);
        size_t endIndexOther = getEndIndex(other.mNumbers, other.mCapacity);
        if(endIndexOther ==0 && endIndexThis == 0)
            return mNumbers[0]/other.mNumbers[0];
        int shift = endIndexThis - endIndexOther;
        delete[] out.mNumbers;
        out.mCapacity = shift+1;
        out.mNumbers = new char[shift+1];
        out.isStringRepresentActuale = false;
        out._init();
        while(shift >=0){
            BigInt localeDividend;
            delete [] localeDividend.mNumbers;
            localeDividend.mNumbers = new char[other.mCapacity + shift];
            localeDividend.mCapacity = other.mCapacity + shift;
            localeDividend.isStringRepresentActuale = false;
            localeDividend._init();
            std::memcpy(localeDividend.mNumbers + shift, other.mNumbers, sizeof(char)*other.mCapacity);
            int count;
            for(count = 0; dividend >= localeDividend; ){
                count++;
                dividend = dividend - localeDividend;

            }
            out.mNumbers[shift] = count;
            shift-=1;
        }
        out.isPositive = isPositive == other.isPositive;
        return out;
    }
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigInt){
        os << bigInt.getString();
        return os;
    }

private:
    size_t getEndIndex(char* const deltas, size_t capacity) const{
        size_t endIndex = 0;
        for(int i =capacity-1; i>=0; i--){
            if(deltas[i] != 0) {
                endIndex = i;
                break;
            }
        }
        return endIndex;
    }
    char* sum(char* const l1, char* const l2, size_t len1, size_t len2) const{
        size_t maxLength = std::max(len1, len2);
        size_t minLength = std::min(len1, len2);
        char* arrMaxLen = len1 > len2 ? l1 : l2;
        size_t len = maxLength + 1;
        char* out = new char[len];
        for(int i =0; i< len; i++){
            if(i<minLength)
                out[i] = l1[i] + l2[i];
            else if (i < maxLength)
                out[i] = arrMaxLen[i];
            else
                out[i] = 0;
        }
        return out;
    }
    char* difference(char* const l1, char* const l2, size_t len1, size_t len2) const{
        size_t maxLength = std::max(len1, len2);
        size_t minLength = std::min(len1, len2);
        char* arrMaxLen = len1 > len2 ? l1 : l2;
        char sign = len1 > len2 ? 1 : -1;
        size_t len = maxLength + 1;
        char* out = new char[len];
        for(int i =0; i< len; i++){
            if(i<minLength)
                out[i] = l1[i] - l2[i];
            else if (i < maxLength)
                out[i] = sign * arrMaxLen[i];
            else
                out[i] = 0;
        }
        return out;
    }

    void initStr(const std::string &numberString){
        _init();
        bool flag = true;
        std::string str;
        mStringRepresent = numberString;
        isStringRepresentActuale = true;
        if(numberString[0] == '-'){
            str = numberString.substr(1);
            isPositive = false;
        } else
            str = numberString;
        if(str.length() > mCapacity)
            resize(str.length()+1);

        for(size_t i = 0; flag; i += POW) {
            flag = i + POW < str.length();
            std::string blockString;
            if(flag)
                blockString = str.substr(str.length() - i - POW, POW);
            else
                blockString = str.substr(0, str.length() - i);

            mNumbers[i/POW] = (char)std::stoi(blockString);

        }
    }
    void _init(){
        for(int i =0; i<mCapacity; i++)
            mNumbers[i] =0;
    }
    void buildStringRepresent() const{
        if(isPositive)
            mStringRepresent = "";
        else
            mStringRepresent = "-";
        bool flag = true;
        bool flag2 = false;
        for (int i=mCapacity-1; i>=0; i--){
            if(flag && mNumbers[i] == 0)
                continue;
            else
                flag = false;
            std::string numStr = std::to_string((int)mNumbers[i]);
            if(flag2)
                for(int j = numStr.length(); j < POW; j++)
                    numStr = "0" + numStr;
            flag2 = true;
            mStringRepresent += numStr;
        }
        if(mStringRepresent.length() == 0 || mStringRepresent.length() == 1 && mStringRepresent[0] == '-')
            mStringRepresent = "0";
        isStringRepresentActuale = true;
    }

    void resize(size_t newCapacity){
        size_t oldCapacity = mCapacity;
        mCapacity = newCapacity;
        char* old = mNumbers;
        mNumbers = new char[mCapacity];
        //std::memset(mNumbers, 0, sizeof(long)*newCapacity);
        _init();
        std::memcpy(mNumbers, old, sizeof(char)*oldCapacity);
        delete[] old;

    }
    const static size_t START_CAPACITY = 4;
    const static size_t POW = 1;
    const size_t MODULE = (size_t)std::pow(10,POW); //модуль системы счислени€. ƒолжен быть кратен 10. мен€ть его не актуально дл€ типов данных char.
    size_t mCapacity = START_CAPACITY;
    char* mNumbers = new char[START_CAPACITY];
    bool isPositive = true;
    mutable std::string mStringRepresent;
    mutable bool isStringRepresentActuale = false;

};
