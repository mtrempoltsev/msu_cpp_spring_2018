#include <iostream>

class BigInt{

    int size;
    int num_size;
    char* data = nullptr;
    bool is_neg = false;
    void extend();
    void shift(int i=1);
    void is_null();
    bool is_ge_pos(const BigInt& other) const;
    bool is_le_pos(const BigInt& other) const;
public:
    BigInt(long long i = 0);
    BigInt(const BigInt& copy);
    BigInt (BigInt&& moved);
    BigInt& operator= (const BigInt& copy);
    BigInt& operator= (BigInt&& moved);
    bool operator== (const BigInt& other) const;
    bool operator!= (const BigInt& other) const;
    bool operator<= (const BigInt& other) const;
    bool operator>= (const BigInt& other) const;
    bool operator< (const BigInt& other) const;
    bool operator> (const BigInt& other) const;
    BigInt operator- ();
    BigInt operator/ (const BigInt& other) const;
    BigInt operator/= (const BigInt& other);
    BigInt operator* (const BigInt& other) const;
    BigInt operator*= (const BigInt& other);
    BigInt operator+ (const BigInt& other) const;
    BigInt operator+= (const BigInt& other);
    BigInt operator- (const BigInt& other) const;
    BigInt operator-= (const BigInt& other);
    ~BigInt();

    friend std::ostream& operator <<(std::ostream& os, const BigInt& obj);
};

void BigInt::extend() {
    size*= 2;
    data = (char*) realloc(data, size);
}

BigInt::BigInt(long long i): size(8), num_size(0) {
    data = new char[size];
    long long tmp = i;
    if (tmp < 0){
        is_neg = true;
        tmp = -tmp;
    } else {
        is_neg = false;
    }
    int j = 0;
    while(tmp > 9){
        if (j==size-1)
                extend();
        data[j] = tmp % 10;
        tmp /= 10;
        j++;
    }
    data[j] = tmp;
    num_size = j+1;
        }


BigInt::BigInt(BigInt &&moved): num_size(moved.num_size), size(moved.size), data(moved.data), is_neg(moved.is_neg){
    moved.data = nullptr;
}


BigInt& BigInt::operator=(BigInt &&moved) {
    if (this != &moved){
        if (data!= nullptr)
            delete[] data;
        num_size = moved.num_size;
        size = moved.size;
        data = moved.data;
        moved.data = nullptr;
        is_neg = moved.is_neg;
    }
    return *this;
}

BigInt::BigInt(const BigInt &copy):size(copy.size), is_neg(copy.is_neg), num_size(copy.num_size) {
    data = new char[size];
    for (int i = num_size-1; i>-1; i--)
        data[i] = copy.data[i];
}


void BigInt::shift(int i) {
    if (i == 0)
        return;
    while ((size - num_size) <= i)
        extend();
    for (int j = num_size+i-1; j>-1; j--)
        if (j<i) {
            data[j] = 0;
        }else {
            data[j] = data[j - i];
        }
    num_size += i;
}


void BigInt::is_null() {
    int i= num_size-1;
    while( (i>0) && (data[i]== 0))
        i--;
    num_size = i+1;
    if(num_size == 1 && data[0] == 0)
        is_neg = false;
}


BigInt BigInt::operator-() {
    if (num_size!=1 && data[0] != 0)
        is_neg = !is_neg;
    return *this;
}


BigInt& BigInt::operator=(const BigInt &copy) {
    delete[] data;
    size = copy.size;
    is_neg = copy.is_neg;
    num_size = copy.num_size;
    data = new char[size];
    for (int i = num_size-1; i>-1; i--)
        data[i] = copy.data[i];
    return *this;
}

bool BigInt::operator==(const BigInt &other) const {
    if(is_neg !=other.is_neg || num_size != other.num_size)
        return false;
    for(int i = num_size-1; i>-1; i--)
        if (data[i] != other.data[i])
            return false;
    return true;
}

bool BigInt::operator!=(const BigInt &other) const {
    return ! (*this == other);
}

bool BigInt::is_ge_pos(const BigInt &other) const {
    if (num_size == other.num_size) {
        for (int i = num_size-1; i > -1; i--)
            if (data[i] > other.data[i])
                return true;
            else if (data[i] < other.data[i])
                return false;
        return true;
    } else {
        return (num_size > other.num_size);
    }
}


bool BigInt::is_le_pos(const BigInt &other) const {
    if (num_size == other.num_size) {
        for (int i = num_size-1; i > -1; i--)
            if (data[i] > other.data[i])
                return false;
            else if (data[i] < other.data[i])
                return true;
        return true;
    } else {
        return  (num_size <= other.num_size);
    }
}

bool BigInt::operator<(const BigInt &other) const {
    if (is_neg == other.is_neg)
        if (is_neg)
            return is_ge_pos(other);
        else
            return !is_ge_pos(other);
    else
        return (is_neg > other.is_neg);
}

bool BigInt::operator>=(const BigInt &other) const {
    return !(*this < other);
}

bool BigInt::operator>(const BigInt &other) const {
    if(is_neg == other.is_neg)
        if (is_neg)
            return is_le_pos(other);
        else
            return !is_le_pos(other);
    else
        return  (is_neg <= other.is_neg);
}

bool BigInt::operator<=(const BigInt &other) const {
    return !(*this > other);
}

std::ostream& operator<<(std::ostream &os, const BigInt &obj) {
    if (obj.is_neg)
        os << '-';
    for (int i = obj.num_size -1 ; i > -1; i--)
        os <<(int) obj.data[i];
    return os;
}


BigInt BigInt::operator-(const BigInt &other) const {
    BigInt tmp_int = *this;
    return tmp_int -= other;
}


BigInt BigInt::operator-=(const BigInt &other) {
    if ((!is_neg) && (!other.is_neg)) {
        if (*this >= other){
            char sub1 = 0;
            int tmp;
            for(int j = 0; j<num_size; j++){
                int sub2 = other.num_size<=j ? 0 : other.data[j];
                tmp = data[j] - sub1 - sub2;
                sub1 = 0;
                if (tmp<0){
                    tmp += 10;
                    sub1 = 1;
                }
                data[j] = tmp;
            }
        } else {
            BigInt tmp_int = other;
            *this = (tmp_int -= *this);
            is_neg = true;
        }
    } else if ((is_neg) && (other.is_neg)){
        BigInt tmp_int = other;
        is_neg = false;
        tmp_int.is_neg = false;
        *this -= tmp_int;
        is_neg =  !is_neg;
    } else {
        BigInt tmp_int = other;
        tmp_int.is_neg = not tmp_int.is_neg;
        *this += tmp_int;
    }
    is_null();
    return *this;
}


BigInt BigInt::operator+(const BigInt &other) const {
    BigInt tmp_int = *this;
    return tmp_int += other;
}


BigInt BigInt::operator+=(const BigInt &other) {
    if (is_neg == other.is_neg){
        int new_num_size = std::max(num_size, other.num_size);
        while (new_num_size+1 >= size){
            extend();
        }
        char add1 = 0;
        for(int j=0; j<new_num_size; j++){
            int add2 = other.num_size<=j ? 0 : other.data[j];
            int add3 = num_size<=j ? 0: data[j];
            data[j] = add1 + add2 + add3;
            add1 = 0;
            if (data[j] > 9){
                data[j] -= 10;
                add1 = 1;
                 }
            }
        num_size = new_num_size;
        if (add1){
            num_size++;
            data[num_size-1] = 1;
        }
    } else {
        BigInt tmp_int = other;
        tmp_int.is_neg = not tmp_int.is_neg;
        *this -= tmp_int;

    }
    is_null();
    return *this;
}


BigInt BigInt::operator*(const BigInt &other) const {
    BigInt tmp_int = *this;
    return tmp_int *= other;
}


BigInt BigInt::operator*=(const BigInt &other) {
    is_neg = is_neg xor other.is_neg;
    BigInt res = 0;
    res.is_neg = is_neg;
    for (int i = other.num_size-1; i>-1; i--){
        char sub = other.data[i];
        BigInt tmp;
        if(sub != 0) {
            tmp = *this;
            char add = 0;
            for (int j = 0; j < tmp.num_size; j++) {
                tmp.data[j] *= sub;
                tmp.data[j] += add;
                add = 0;
                if (tmp.data[j] > 9) {
                    add = tmp.data[j] / 10;
                    tmp.data[j] %= 10;
                }
            }
            if (add) {
                if (tmp.size <= tmp.num_size)
                    tmp.extend();
                tmp.data[num_size] = add;
                tmp.num_size += 1;
            }
            tmp.shift(i);
            res += tmp;
        }
    }
    *this = res;
    is_null();
    return *this;
}


BigInt BigInt::operator/ (const BigInt &other) const {
    BigInt tmp_int = *this;
    return tmp_int /= other;
}


BigInt BigInt::operator/=(const BigInt &other) {
    bool res_neg = is_neg xor other.is_neg;
    is_neg = false;
    BigInt res = 0;
    BigInt tmp ;
    BigInt tmp_res;
    for (int i = num_size - other.num_size; i > -1; i--) {
        tmp = other;
        tmp.is_neg = false;
        tmp_res = 0;
        tmp.shift(i);
        while (tmp <= *this) {
            *this -= tmp;
            tmp_res += 1;
        }
        tmp_res.shift(i);
        res += tmp_res;
    }
    res.is_neg = res_neg;
    *this = res;
    is_null();
    return *this;
}


BigInt::~BigInt() {
    if (data!= nullptr)
        delete[] data;
}

