#include <iostream>

class BigInt {
private:
    char* data_;
    bool sign = false;
    friend std::ostream& operator<<(std::ostream& out, const BigInt& val) {
        if (val.sign) out << '-';
        for (size_t i = val.size_ - 1; i != -1; i--)
            out << static_cast<char>('0' + val.data_[i]);
        return out;
    }
    void push_back(char val) {
        data_[size_++] = val;
        if (capacity_ == size_) this->allocate();
    }
    char pop() {
        return data_[--size_];
    }
    void push_front(char val) {
        for (size_t i = size_; i > 0; i--) data_[i] = data_[i - 1];
        size_++;
        if (capacity_ == size_) this->allocate();
        data_[0] = val;
    }
    void delete_zero() {
        for (size_t i = size_ - 1; i > 0; i--) {
            if (data_[i] > 0) break;
            size_--;
        }
    }
    void allocate() {
        capacity_ *= 2;
        char* new_data = new char[capacity_];
        memcpy(new_data, data_, size_);
        delete[] data_;
        data_ = new_data;
    }
    char binSearch(const BigInt& dividend, const BigInt& divisor) const {
        char result = 0;
        char min = 0;
        char max = 10;
        while (min <= max) {
            char curr = (max + min) / 2;
            if (BigInt(curr) * divisor <= dividend) {
                result = curr;
                min = curr + 1;
            } else max = curr - 1;
        }
        return result;
    }
    void check_zero() {
        if (size_ == 1 && data_[0] == 0) {
            sign = false;
        }
    }
    size_t capacity_ = 32;
    size_t size_ = 0;
public:
    
    BigInt(long value) {
        if (value < 0) {
            sign = true;
            value *= -1;
        }
        data_ = new char[capacity_];
        if (value == 0) {
            this->push_back(0);
            return;
        }
        for (size_t i = 0; value > 0; i++) {
            this->push_back(value % 10);
            value /= 10;
        }
    }
    BigInt() {
        data_ = new char[capacity_];
        this->push_back(0);
    }
    
    BigInt(const BigInt& val): size_(val.size_), sign(val.sign), capacity_(val.capacity_) {
        data_ = new char[capacity_];
        memcpy(data_, val.data_, size_);
    }
    BigInt(BigInt&& val): size_(val.size_), sign(val.sign), capacity_(val.capacity_), data_(val.data_) {
        val.data_ = nullptr;
    }
    ~BigInt() {
        delete[] data_;
    }
    BigInt operator - () const {
        BigInt val(*this);
        val.sign = !sign;
        val.check_zero();
        return val;
    }
    BigInt& operator = (const BigInt& val) {
        if (this == &val) return *this;
        size_ = val.size_;
        capacity_ = val.capacity_;
        sign = val.sign;
        delete[] data_;
        data_ = new char[capacity_];
        memcpy(data_, val.data_, size_);
        return *this;
    }
    bool operator == (const BigInt& val) const {
        if (size_ != val.size_ || sign != val.sign) return false;
        for (size_t i = 0; i < size_; i++) {
            if (data_[i] != val.data_[i]) return false;
        }
        return true;
    }
    bool operator != (const BigInt& val) const {
        return !(*this == val);
    }
    bool operator < (const BigInt& val) const {
        if (sign != val.sign || size_ > val.size_) return sign;
        else if (size_ < val.size_) return !sign;
        for (size_t i = size_ - 1; i != -1; i--) {
            if (data_[i] > val.data_[i]) return sign;
            else if (data_[i] < val.data_[i]) return !sign;
        }
        return false;
    }
    bool operator <= (const BigInt& val) const {
        return !(*this > val);
    }
    bool operator > (const BigInt& val) const {
        if (sign != val.sign || size_ > val.size_) return !sign;
        if (size_ < val.size_) return sign;
        for (size_t i = size_ - 1; i != -1; i--) {
            if (data_[i] < val.data_[i]) return sign;
            else if (data_[i] > val.data_[i]) return !sign;
        }
        return false;
    }
    
    bool operator >= (const BigInt& val) const {
        return !(*this < val);
    }
    BigInt module_() const {
        BigInt tmp = *this;
        tmp.sign = false;
        return tmp;
    }
    
    BigInt operator + (const BigInt& val) const {
        if (sign != val.sign) {
            if (sign) return val - module_();
            else return *this - val.module_();
        }
        BigInt result(*this);
        for (size_t i = result.size_; i < val.size_; i++)
            result.push_back(0);
        char next = 0;
        for (size_t i = 0; i < val.size_; i++) {
            char shift = result.data_[i] + val.data_[i] + next;
            result.data_[i] = shift % 10;
            next = shift / 10;
        }
        for (size_t i = val.size_; i < result.size_; i++) {
            char shift = result.data_[i] + next;
            result.data_[i] = shift % 10;
            next = shift / 10;
        }
        if (next > 0) result.push_back(next);
        result.delete_zero();
        result.check_zero();
        return result;
    }
    BigInt operator - (const BigInt& val) const {
        if (sign != val.sign) {
            if (sign)
                return -(this->module_() + val);
            else
                return *this + val.module_();
        }
        if (sign)
            return val.module_() + *this;
        if (*this < val)
            return -(val - *this);
        BigInt result(*this);
        char next = 0;
        for (size_t i = 0; i < val.size_; i++) {
            char difference = result.data_[i] - val.data_[i] - next;
            if (difference < 0) {
                result.data_[i] = difference + 10;
                next = 1;
            } else {
                result.data_[i] = difference;
                next = 0;
            }
        }
        for (size_t i = val.size_; i < result.size_; i++) {
            char difference = result.data_[i] - next;
            if (difference < 0) {
                result.data_[i] = difference + 10;
                next = 1;
            } else {
                result.data_[i] = difference;
                next = 0;
            }
        }
        result.delete_zero();
        result.check_zero();
        return result;
    }
    BigInt operator * (const BigInt& val) const {
        BigInt result;
        for (size_t i = 0; i < val.size_; i++) {
            BigInt output;
            output.pop();
            char next = 0;
            for (size_t j = 0; j < i; j++)
                output.push_back(0);
            for (size_t j = 0; j < size_; j++) {
                char multiplication = val.data_[i] * data_[j] + next;
                output.push_back(multiplication % 10);
                next = multiplication / 10;
            }
            if (next > 0)
                output.push_back(next);
            result = result + output;
        }
        result.sign = sign != val.sign;
        result.delete_zero();
        result.check_zero();
        return result;
    }
    BigInt operator / (const BigInt& val) const {
        BigInt result;
        BigInt output;
        output.pop();
        BigInt abs_number = val.module_();
        for (size_t i = 0; i < size_; i++) {
            output.push_front(data_[size_ - 1 - i]);
            output.delete_zero();
            char div = binSearch(output, abs_number);
            result.push_front(div);
            output = output - abs_number * BigInt(div);
        }
        result.delete_zero();
        result.sign = sign != val.sign;
        result.check_zero();
        return result;
    }
};
