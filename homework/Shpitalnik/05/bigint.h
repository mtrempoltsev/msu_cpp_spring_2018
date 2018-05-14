#include <iostream>
#include <memory>

class BigInt{

    int size;
    int num_size;
    std::unique_ptr<char[]> data = nullptr;
    bool is_neg = false;
    void extend();
    void shift(int i=1);
    bool is_null();
    friend BigInt minus(const BigInt* a, const BigInt* b, const char op);
    friend BigInt plus(const BigInt* a, const BigInt* b);
    bool is_ge_pos(const BigInt& other) const;
    bool is_le_pos(const BigInt& other) const;
public:
    BigInt(long long i = 0);
    BigInt(const BigInt& copy);
    BigInt (BigInt&& moved) noexcept;
    BigInt& operator= (const BigInt& copy);
    BigInt& operator= (BigInt&& moved) noexcept;
    bool operator== (const BigInt& other) const;
    bool operator!= (const BigInt& other) const;
    bool operator<= (const BigInt& other) const;
    bool operator>= (const BigInt& other) const;
    bool operator< (const BigInt& other) const;
    bool operator> (const BigInt& other) const;
    BigInt operator- () const;
    BigInt operator/ (const BigInt& other) const;
    BigInt operator/= (const BigInt& other);
    BigInt operator* (const BigInt& other) const;
    BigInt operator*= (const BigInt& other);
    BigInt operator+ (const BigInt& other) const;
    BigInt operator+= (const BigInt& other);
    BigInt operator- (const BigInt& other) const;
    BigInt operator-= (const BigInt& other);

    friend std::ostream& operator <<(std::ostream& os, const BigInt& obj);
};

void BigInt::extend() {
    auto newData = std::make_unique<char[]>(size*2);
    std::copy(data.get(), data.get() + size, newData.get());
    data.swap(newData);
    size = size*2;
}

BigInt::BigInt(long long i): size(2), num_size(0), data(std::make_unique<char[]>(2)) {
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


BigInt::BigInt(BigInt &&moved) noexcept :num_size(moved.num_size), size(moved.size),
                               is_neg(moved.is_neg)  {
    //data.reset(moved.data.release());
    data = std::move(moved.data);

}


BigInt& BigInt::operator=(BigInt &&moved) noexcept {
    if (this != &moved){
        num_size = moved.num_size;
        size = moved.size;
        //data.reset(moved.data.release());
        data = std::move(moved.data);
        is_neg = moved.is_neg;

    }
    return *this;
}

BigInt::BigInt(const BigInt &copy):size(copy.size), is_neg(copy.is_neg),
                                   num_size(copy.num_size), data(std::make_unique<char[]>(copy.size)) {
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


bool BigInt::is_null() {
    int i= num_size-1;
    while( (i>0) && (data[i]== 0))
        i--;
    num_size = i+1;
    if(num_size == 1 && data[0] == 0) {
        is_neg = false;
        return true;
    }
}


BigInt BigInt::operator-() const {
    BigInt tmp = *this;
    if ((tmp.num_size!=1)  || (tmp.data[0] != 0))
        tmp.is_neg = !tmp.is_neg;
    return tmp;
}


BigInt& BigInt::operator=(const BigInt &copy) {
    size = copy.size;
    is_neg = copy.is_neg;
    num_size = copy.num_size;
    data = std::make_unique<char[]>(size);
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
    if(is_neg != other.is_neg)
        return plus(this, &other);
    else
        return minus(this, &other, '-');
}


BigInt BigInt::operator-=(const BigInt &other) {
    *this = (*this - other);
    return *this;
}

BigInt plus(const BigInt* a, const BigInt* b) {
    BigInt res;
    res.is_neg = a->is_neg;
    int max_num_size = std::max(a->num_size, b->num_size);
    while (max_num_size+1 >= res.size)
        res.extend();
    char add1 = 0;
    for(int j=0; j<max_num_size; j++){
        int add2 = b->num_size<=j ? 0 : b->data[j];
        int add3 = a->num_size<=j ? 0 : a->data[j];
        res.data[j] = add1 + add2 + add3;
        add1 = 0;
        if (res.data[j] > 9){
            res.data[j] -= 10;
            add1 = 1;
        }
    }
    res.num_size = max_num_size;
    if (add1) {
        res.num_size++;
        res.data[res.num_size - 1] = 1;
    }
    res.is_null();
    return res;
}

BigInt minus(const BigInt* a, const BigInt* b, const char op) {
    bool not_swaped = true;
    if(a->is_le_pos(*b)) {
        std::swap(a, b);
        not_swaped = false;
    }
    bool is_neg = (op == '+' && a->is_neg)||
            (op=='-' && ((not_swaped && a->is_neg) || not(a->is_neg ||  not_swaped)));
    BigInt res(*a);
    res.is_neg = is_neg;
    char sub1 = 0;
    int tmp;
    for(int j = 0; j<res.num_size; j++){
        int sub2 = b->num_size <= j ? 0 : b->data[j];
        tmp = res.data[j] - sub1 - sub2;
        sub1 = 0;
        if (tmp<0){
            tmp += 10;
            sub1 = 1;
        }
        res.data[j] = tmp;
    }
    res.is_null();
    return res;
}

BigInt BigInt::operator+(const BigInt &other) const {
    if(is_neg == other.is_neg)
        return plus (this, &other);
    else
        return minus (this, &other, '+');
}


BigInt BigInt::operator+=(const BigInt &other) {
    *this = (*this + other);
    return *this;
}


BigInt BigInt::operator*(const BigInt &other) const {
    return BigInt(*this) *= other;
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
    return BigInt(*this) /= other;
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

