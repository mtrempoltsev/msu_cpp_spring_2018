
#ifndef HOMEWORK5_INTEGER_H
#define HOMEWORK5_INTEGER_H

#endif //HOMEWORK5_INTEGER_H

#include <iostream>
#include <vector>
#include <cstdint>

class BigInt{
    bool positive_;
    const char radix_;
    char* digits_;
    size_t size_;
    size_t capacity_;

    bool CheckZero(){
        if(size_ == 1 && digits_[0] == 0){
            positive_ = true;
            return true;
        }
        return false;
    }

    bool CheckEmptyNumber() const {
        if(digits_ == nullptr){
            throw std::logic_error("Impossible to do any operation with an empty number!");
        }
    }

    bool SegmentsLess(size_t first_start, size_t first_finish, bool first_pos,
                      const BigInt& second, size_t second_start, size_t second_finish, bool second_pos) const {
        if(first_pos != second_pos){
            return !first_pos;
        }
        int cmp = 0;
        size_t first_size = first_finish - first_start;
        size_t second_size = second_finish - second_start;
        if(first_size != second_size){
            cmp = static_cast<int>(first_size < second_size);
            cmp = cmp * 2 - 1;
        }else{
            for(size_t it = first_finish; it > first_start; --it){
                size_t ind = it - 1 - first_start;
                if(digits_[it - 1] != second.digits_[ind + second_start]){
                    cmp = static_cast<int>(digits_[it - 1] < second.digits_[ind + second_start]);
                    cmp = cmp * 2 - 1;
                    break;
                }
            }
        }

        return (cmp == 1 && first_pos) || (cmp == -1 && !first_pos);
    }

    void realloc(size_t new_cap){
        if(new_cap <= capacity_){
            return;
        }
        capacity_ = new_cap;
        char* ptr = new char[capacity_];
        std::copy(digits_, digits_ + size_, ptr);
        std::fill(ptr + size_, ptr + capacity_, 0);
        delete[] digits_;
        digits_ = ptr;
    }

    void SumPositive(BigInt& result, const BigInt& second) const {
        size_t sz_f = result.size_;
        size_t sz_s = second.size_;
        result.realloc(std::max(sz_f, sz_s) + 1);
        result.size_ = std::max(sz_f, sz_s);

        char carry = 0;
        for(size_t it = 0; it < std::min(sz_f, sz_s); ++it){
            carry += result.digits_[it] + second.digits_[it];
            result.digits_[it] = carry % radix_;
            carry /= radix_;
        }
        for(size_t it = std::min(sz_f, sz_s); it < std::max(sz_f, sz_s); ++it){
            if(it < sz_f)
                carry += result.digits_[it];
            if(it < sz_s)
                carry += second.digits_[it];
            result.digits_[it] = carry % radix_;
            carry /= radix_;
        }
        if(carry){
            result.digits_[result.size_] = carry;
            ++result.size_;
        }
    }

    void SubtrPositive(BigInt& result, const BigInt& second) const {
        int sign_r = 1;
        size_t sz_r = result.size_;
        int sign_s = -1;
        size_t sz_s = second.size_;

        result.realloc(std::max(sz_s, sz_r));

        bool pos = true;
        if(result.SegmentsLess(0, sz_r, true, second, 0, sz_s, true)){
            sign_r = -1;
            sign_s = 1;
            pos = false;
        }

        int carry = 0;
        for(size_t it = 0; it < std::max(sz_r, sz_s); ++it){
            if(it < sz_r)
                carry += sign_r * result.digits_[it];
            if(it < sz_s)
                carry += sign_s * second.digits_[it];

            result.digits_[it] = (carry + radix_) % radix_;
            carry = (carry < 0? -1 : 0);
        }

        result.size_ = std::max(sz_r, sz_s);
        while(result.size_ > 1 && !result.digits_[result.size_ - 1]){
            --result.size_;
        }

        result.positive_ = pos;
    }

    void MultBy2(BigInt& number) const{
        if(number.size_ == number.capacity_){
            number.realloc(number.size_ + 5);
        }

        char carry = 0;
        for(size_t it = 0; it < number.size_; ++it){
            carry = number.digits_[it] * 2 + carry;
            number.digits_[it] = carry % number.radix_;
            carry /= number.radix_;
        }
        if(carry){
            number.digits_[number.size_] = carry;
            ++number.size_;
        }
    }

    void DivideBy2(BigInt& number) const{
        char carry = 0;
        for(size_t it = number.size_; it > 0; --it){
            carry = carry * number.radix_ + number.digits_[it - 1];
            number.digits_[it - 1] = carry / 2;
            carry %= 2;
        }
        if(number.size_ > 1 && number.digits_[number.size_ - 1] == 0){
            --number.size_;
        }
    }

public:

    BigInt(int64_t number = 0) : radix_(10){
        positive_ = 0 <= number;
        number = std::abs(number);

        size_ = 0;
        int64_t copy_number = number;
        do{
            ++size_;
            copy_number /= radix_;
        }while(copy_number > 0);

        digits_ = new char[size_];
        capacity_ = size_;

        for(size_t it = 0; it < size_; ++it){
            digits_[it] = static_cast<char>(number % radix_);
            number /= radix_;
        }
    };

    BigInt(const BigInt& other): radix_(10),
                                 size_(other.size_),
                                 capacity_(other.size_),
                                 positive_(other.positive_){
        digits_ = new char[size_];
        std::copy(other.digits_, other.digits_ + size_, digits_);
    };

    BigInt(BigInt&& other): radix_(10),
                                 size_(other.size_),
                                 capacity_(other.size_),
                                 positive_(other.positive_){
        digits_ = other.digits_;

        other.digits_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    };

    ~BigInt(){
        if(digits_ != nullptr)
            delete[] digits_;
    }

    BigInt& operator=(const BigInt& other){
        size_ = other.size_;
        capacity_ = other.size_;
        positive_ = other.positive_;
        digits_ = new char[size_];
        std::copy(other.digits_, other.digits_ + size_, digits_);
    };

    BigInt& operator=(BigInt&& other){
        if(digits_ != nullptr){
            delete[] digits_;
        }
        digits_ = other.digits_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        positive_ = other.positive_;

        other.digits_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }


    BigInt operator+(const BigInt& other) const{
        CheckEmptyNumber();
        other.CheckEmptyNumber();

        BigInt result(*this);
        if(positive_ == other.positive_) {
            SumPositive(result, other);
        }else {
            SubtrPositive(result, other);
            result.positive_ = result.positive_ == positive_;
        }
        result.CheckZero();
        return result;
    };

    BigInt operator-(){
        CheckEmptyNumber();

        BigInt result(*this);
        if(!result.CheckZero())
            result.positive_ ^= true;
        return result;
    }

    BigInt operator-(const BigInt& other) const{
        CheckEmptyNumber();
        other.CheckEmptyNumber();

        BigInt result(*this);
        if(positive_ == other.positive_){
            SubtrPositive(result, other);
            result.positive_ = result.positive_ == positive_;
        }else {
            SumPositive(result, other);
        }
        result.CheckZero();
        return result;
    };

    BigInt operator*(const BigInt& other) const{
        CheckEmptyNumber();
        other.CheckEmptyNumber();

        BigInt result = BigInt();
        bool pos = positive_ == other.positive_;
        result.realloc(size_ + other.size_ + 1);
        for(size_t it = 0; it < other.size_; ++it){
            char carry = 0;
            for(size_t it2 = 0; it2 < size_; ++it2){
                carry = result.digits_[it + it2] + digits_[it2] * other.digits_[it] + carry;
                result.digits_[it + it2] = carry % 10;
                carry /= 10;
            }
            result.size_ = it + size_;
            if(carry){
                result.digits_[it + size_] = carry;
                ++result.size_;
            }
        }
        while(result.size_ > 1 && result.digits_[result.size_ - 1] == 0){
            --result.size_;
        }
        result.positive_ = pos;
        result.CheckZero();
        return result;
    };

    BigInt operator/(const BigInt& other) const{
        CheckEmptyNumber();
        other.CheckEmptyNumber();

        if(other.size_ == 1 && other.digits_[0] == 0){
            throw std::logic_error("Imposible divide by zero!");
        }

        BigInt divident(*this);
        BigInt divisor(other);
        divident.positive_ = true;
        divisor.positive_ = true;

        BigInt up_bound = BigInt(1);
        while(up_bound * divisor < divident){
            MultBy2(up_bound);
        }

        BigInt low_bound = BigInt();
        BigInt int1 = BigInt(1);
        while(low_bound < up_bound){
            BigInt mid = low_bound + up_bound;
            DivideBy2(mid);
            if(mid * divisor < divident){
                SumPositive(mid, int1);
                low_bound = std::move(mid);
            }else{
                up_bound = std::move(mid);
            }
        }
        if(divisor * up_bound != divident){
            SubtrPositive(up_bound, int1);
        }
        if(positive_ != other.positive_)
            up_bound.positive_ = false;
        up_bound.CheckZero();
        return up_bound;
    };

    bool operator==(const BigInt& other) const {
        CheckEmptyNumber();
        other.CheckEmptyNumber();

        if(positive_ != other.positive_){
            return false;
        }
        if(size_ != other.size_){
            return false;
        }
        for(size_t it = 0; it < size_; ++it){
            if(digits_[it] != other.digits_[it]){
                return false;
            }
        }
        return true;
    };

    bool operator!=(const BigInt& other) const{
        return !(*this == other);
    };

    bool operator<(const BigInt& other) const{
        CheckEmptyNumber();
        other.CheckEmptyNumber();

        return SegmentsLess(0, size_, positive_,
                             other, 0, other.size_, other.positive_);
    };

    bool operator>(const BigInt& other) const {
        return !(*this < other || *this == other);
    };

    bool operator<=(const BigInt& other) const {
        return *this < other || *this == other;
    };

    bool operator>=(const BigInt& other) const {
        return !(*this < other);
    };

    friend std::ostream& operator<<(std::ostream& out, const BigInt& number){
        number.CheckEmptyNumber();

        if(!number.positive_){
            out << "-";
        }
        for(size_t it = number.size_; it > 0; --it){
            out << static_cast<size_t>(number.digits_[it - 1]);
        }
        return out;
    };
};
