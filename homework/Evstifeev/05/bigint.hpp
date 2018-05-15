#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include "vector.hpp"

class BigInt {
   public:
    BigInt() : sign{true}, number{1} {}

    // from string
    BigInt(const std::string& str) {
        if (std::stoi(str) < 0)
            sign = negative;
        else
            sign = positive;
        for (size_t i = 1; i < str.size(); i++) {
            number.push_back(str[i] - '0');
        }
        std::reverse(number.begin(), number.end());
    }

    // init from long long int
    BigInt(int64_t num) {
        if (num < 0) {
            num = -num;
            sign = negative;
        } else
            sign = positive;
        do {
            number.push_back(num % base);
        } while (num /= base);
    }

    // copy cons
    BigInt(const BigInt& other) : number{other.number}, sign{other.sign} {}

    BigInt(const IntVector& v, const bool _sign) : number{v}, sign{_sign} {}

    BigInt operator+(const BigInt& rhs) const {
        if (sign != rhs.sign) {
            if (sign == negative)
                return rhs - (-*this);
            else if (sign == positive)
                return *this - (-rhs);
        }
        IntVector tmp_num;
        const int r_size = rhs.number.size();
        const int l_size = number.size();
        int k = 0;
        for (int j = 0; j < std::max(r_size, l_size); j++) {
            int l_num = j < l_size ? number[j] : 0;
            int r_num = j < r_size ? rhs.number[j] : 0;
            tmp_num.push_back((l_num + r_num + k) % base);
            k = floor((l_num + r_num + k) / base);
        }
        tmp_num.push_back(k);
        BigInt tmp(tmp_num, rhs.sign);
        tmp.clean_leading_zeros();
        return tmp;
    }

    BigInt operator-(const BigInt& rhs) const {
        IntVector tmp_num;
        bool tmp_sign;
        IntVector left = number;
        IntVector right = rhs.number;
        if (sign == positive && rhs.sign == negative) return *this + (-rhs);
        if (sign == negative && rhs.sign == positive) {
            return -(-*this + rhs);
        }
        if (sign == negative && rhs.sign == negative) return -rhs + *this;
        if (*this < rhs) {
            tmp_sign = negative;
            std::swap(left, right);
        } else
            tmp_sign = positive;
        int k = 0;
        const int r_size = right.size();
        const int l_size = left.size();
        for (int j = 0; j < std::max(r_size, l_size); j++) {
            int l_num = j < l_size ? left[j] : 0;
            int r_num = j < r_size ? right[j] : 0;
            tmp_num.push_back((base + ((l_num - r_num + k) % base)) % base);
            k = floor(((float)l_num - r_num + k) / base);
        }
        BigInt tmp(tmp_num, tmp_sign);
        tmp.clean_leading_zeros();
        return tmp;
    }

    BigInt operator*(const BigInt& rhs) const {
        bool tmp_sign = sign * rhs.sign;
        if (sign == negative && rhs.sign == negative) tmp_sign = positive;
        const int l_size = number.size();
        const int r_size = rhs.number.size();
        IntVector tmp_num(l_size + r_size);
        int k = 0;
        int t = 0;
        for (size_t j = 0; j < r_size; j++) {
            k = 0;
            for (size_t i = 0; i < l_size; i++) {
                t = number[i] * rhs.number[j] + tmp_num[i + j] + k;
                tmp_num[i + j] = t % base;
                k = floor(t / base);
            }
            tmp_num[j + l_size] = k;
        }
        BigInt tmp_b_int(tmp_num, tmp_sign);
        tmp_b_int.clean_leading_zeros();
        tmp_b_int.check_zero();
        return tmp_b_int;
    }

    BigInt operator/(const BigInt& rhs) const {
        bool tmp_sign = sign * rhs.sign;
        if (sign == negative && rhs.sign == negative) tmp_sign = positive;
        IntVector left = number;
        IntVector right = rhs.number;
        const int l_size = left.size();
        const int r_size = right.size();
        BigInt tmp;
        IntVector tmp_num;
        BigInt abs_ = rhs;
        if (rhs.sign == negative) abs_ = -abs_;
        for (size_t i = 0; i < l_size; i++) {
            tmp.number.push_front(left[l_size - 1 - i]);
            tmp.clean_leading_zeros();
            int divisor = binary_search(tmp, abs_);
            tmp_num.push_back(divisor);
            // std::cout << "DIVISOR: " << divisor << std::endl;
            // std::cout << "TMP: " << tmp << std::endl;
            // std::cout << "rhs * bigInt: " << rhs * BigInt(divisor) <<
            // std::endl;
            tmp = tmp - abs_ * BigInt(divisor);
            // std::cout << "RESULT: " << tmp << std::endl;
        }
        std::reverse(tmp_num.begin(), tmp_num.end());
        BigInt result(tmp_num, tmp_sign);
        result.clean_leading_zeros();
        result.check_zero();
        return result;
    }

    bool operator<(const BigInt& rhs) const {
        if (sign == positive && rhs.sign == negative) return false;
        if (sign == negative && rhs.sign == positive) return true;
        const int r_size = rhs.number.size();
        const int l_size = number.size();

        if (l_size > r_size)
            return false;
        else if (l_size < r_size)
            return true;

        bool both_negative = (sign == negative && rhs.sign == negative);
        for (int i = r_size - 1; i >= 0; i--) {
            if (number[i] > rhs.number[i]) {
                if (both_negative == true) return true;
                return false;
            } else if (number[i] < rhs.number[i]) {
                if (both_negative == true) return false;
                return true;
            }
        }
        return false;
    }

    bool operator==(const BigInt& rhs) const {
        if (&rhs == this) return true;
        const size_t r_size = rhs.number.size();
        const size_t l_size = number.size();
        if (r_size != l_size || sign != rhs.sign) return false;
        for (size_t i = 0; i < r_size; i++) {
            if (number[i] != rhs.number[i]) return false;
        }
        return true;
    }

    bool operator!=(const BigInt& rhs) const { return !(*this == rhs); }

    bool operator>(const BigInt& rhs) const {
        if (*this == rhs) return false;
        return !(*this < rhs);
    }

    bool operator<=(const BigInt& rhs) const {
        return (*this == rhs) || (*this < rhs);
    }

    bool operator>=(const BigInt& rhs) const {
        return (*this == rhs) || (*this > rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& b_int) {
        if (b_int.sign == negative) os << "-";
        for (int i = b_int.number.size() - 1; i >= 0; i--) {
            os << b_int.number[i];
        }
        return os;
    }

    BigInt operator-() const {
        BigInt tmp{*this};
        if (tmp == BigInt(0)) return tmp;
        tmp.sign = !sign;
        return tmp;
    }

    void check_zero() {
        if (number.size() == 1 && number[0] == 0 && sign == negative)
            sign = positive;
    }

   private:
    void clean_leading_zeros() {
        for (size_t i = number.size() - 1; number[i] == 0 && i != 0; i--) {
            number.pop_back();
        }
    }

    int binary_search(const BigInt& divisor, const BigInt& x) const {
        int left_bound = 0, mid = 0, right_bound = base, result = 0;
        while (right_bound - left_bound > 1) {
            mid = (left_bound + right_bound) / 2;
            if (x * BigInt(mid) <= divisor)
                left_bound = mid;
            else
                right_bound = mid;
        }
        return left_bound;
    }

    IntVector number;  // invariant - should be always reversed
    bool sign;
    const static int base = 10;

    enum { positive = true, negative = false };
};
