#include "list.h"

class BigInt {
private:
    List *bigint_;
    int sign;
    static const int CHUNK_SIZE = 4;
    // MAX_NUMBER = 10^CHUNK_SIZE
    static const int MAX_NUMBER = 10000;

    void change_sign() {
        sign *= -1;
    }

    void dell_zero() {
        int i = bigint_->get_size() - 1;
        while ((*bigint_)[i] == 0 && i > 0) {
            bigint_->pop_back();
            i--;
        }
        return;
    }

public:
    BigInt(const int64_t number = 0) {
        bigint_ = new List{};
        int64_t tmp_int = number;
        if (number >= 0) {
            sign = 1;
        } else {
            sign = -1;
            tmp_int *= -1;
        }
        int curr_int;
        if (!tmp_int) {
            bigint_->push_back(0);
        }
        while (tmp_int) {
            curr_int = tmp_int % MAX_NUMBER;
            bigint_->push_back(curr_int);
            tmp_int /= MAX_NUMBER;
        }
    }

    BigInt(const BigInt &copied) :
            sign(copied.sign) {
        bigint_ = new List(*copied.bigint_);
    }

    BigInt(BigInt &&moved) noexcept {
        sign = moved.sign;
        bigint_ = moved.bigint_;
        moved.bigint_ = new List{0};
        moved.sign = 1;
    }

    BigInt &operator=(const BigInt &copied) {
        if (this == &copied) {
            return *this;
        }
        delete bigint_;
        bigint_ = new List(*copied.bigint_);
        sign = copied.sign;
        return *this;
    }

    BigInt &operator=(BigInt &&moved) noexcept {
        if (this == &moved) {
            return *this;
        }
        delete bigint_;
        bigint_ = moved.bigint_;
        sign = moved.sign;
        moved.bigint_ = new List{0};
        moved.sign = 1;
    }

    friend std::ostream &operator<<(std::ostream &os, const BigInt &bigInt) {
        if (bigInt.sign == -1) {
            os << "-";
        }
        int norma;
        int64_t curr_data;
        os << (*bigInt.bigint_)[bigInt.bigint_->get_size() - 1];
        for (int i = bigInt.bigint_->get_size() - 2; i >= 0; --i) {
            curr_data = (*bigInt.bigint_)[i];
            norma = MAX_NUMBER / 10;
            for (int j = 0; j < CHUNK_SIZE; ++j) {
                if (curr_data / norma) {
                    break;

                } else {
                    os << 0;
                    norma /= 10;
                }
            }
            if (curr_data) {
                os << curr_data;
            }
        }

        return os;
    }

    bool operator==(const BigInt &bigInt) const {
        if (this == &bigInt) {
            return true;
        }
        if (sign != bigInt.sign) {
            return false;
        }
        return *bigint_ == *bigInt.bigint_;
    }

    bool operator!=(const BigInt &bigInt) const {
        return !(*this == bigInt);
    }

    bool operator>=(const BigInt &bigInt) const {
        if (this == &bigInt) {
            return true;
        }
        if (sign > bigInt.sign) {
            return true;
        } else if (sign < bigInt.sign) {
            return false;
        } else if (sign < 0) {
            return !(*bigint_ > *bigInt.bigint_);
        }
        return *bigint_ >= *bigInt.bigint_;
    }

    bool operator>(const BigInt &bigInt) const {
        if (this == &bigInt) {
            return false;
        }
        if (sign > bigInt.sign) {
            return true;
        } else if (sign < bigInt.sign) {
            return false;
        } else if (sign < 0) {
            return !(*bigint_ >= *bigInt.bigint_);
        }
        return *bigint_ > *bigInt.bigint_;
    }

    bool operator<=(const BigInt &bigInt) const {
        return !(*this > bigInt);
    }

    bool operator<(const BigInt &bigInt) const {
        return !(*this >= bigInt);
    }

    void sum_bigInt(const List &x, const List &y) {
        delete bigint_;
        bigint_ = new List;
        size_t size_x = x.get_size();
        size_t size_y = y.get_size();
        size_t min_size = size_x > size_y ?
                          size_y :
                          size_x;
        int carry_over = 0;
        int64_t sum;
        for (int i = 0; i < min_size; ++i) {
            sum = x[i] + y[i] + carry_over;
            carry_over = sum / MAX_NUMBER;
            bigint_->push_back(sum % MAX_NUMBER);
        }
        for (int j = size_y; j < size_x; ++j) {
            sum = x[j] + carry_over;
            carry_over = sum / MAX_NUMBER;
            bigint_->push_back(sum % MAX_NUMBER);
        }
        for (int j = size_x; j < size_y; ++j) {
            sum = y[j] + carry_over;
            carry_over = sum / MAX_NUMBER;
            bigint_->push_back(sum % MAX_NUMBER);
        }
        if (carry_over) {
            bigint_->push_back(carry_over);
        }
        return;
    }

    void dif_bigInt(const List &x, const List &y) {
        delete bigint_;
        bigint_ = new List;
        size_t size_x = x.get_size();
        size_t size_y = y.get_size();
        int carry_over = 0;
        int64_t dif;
        for (int i = 0; i < size_y; ++i) {
            dif = x[i] - y[i] - carry_over;
            if (dif < 0) {
                carry_over = 1;
                dif += MAX_NUMBER;
            } else {
                carry_over = 0;
            }
            bigint_->push_back(dif);
        }
        for (int j = size_y; j < size_x; ++j) {
            dif = x[j] - carry_over;
            if (dif < 0) {
                carry_over = 1;
                dif += MAX_NUMBER;
            } else {
                carry_over = 0;
            }
            bigint_->push_back(dif);
        }

        return;
    }

    List *simple_mul(const List &x, const int64_t y) {
        delete bigint_;
        bigint_ = new List;
        List *tmp;
        size_t size_x = x.get_size();
        int carry_over = 0;
        int64_t mul;
        for (int i = 0; i < size_x; ++i) {
            tmp = new List;
            mul = x[i] * y;
            for (int j = 0; j < i; ++j) {
                tmp->push_back(0);
            }
            tmp->push_back(mul % MAX_NUMBER);
            tmp->push_back(mul / MAX_NUMBER);
            List copy(*bigint_);
            this->sum_bigInt(copy, *tmp);
            delete tmp;
        }
        return bigint_;
    }

    void mul_bigInt(const List &x, const List &y) {
        delete bigint_;
        bigint_ = new List;
        size_t size_x = x.get_size();
        size_t size_y = y.get_size();
        BigInt mul;
        List *mul_bigint;
        for (int i = 0; i < size_y; ++i) {
            mul_bigint = mul.simple_mul(x, y[i]);
            for (int j = 0; j < i; ++j) {
                mul_bigint->push_front(0);
            }
            List copy(*bigint_);
            this->sum_bigInt(copy, *mul_bigint);
        }
        this->dell_zero();
    }

    BigInt operator-() const {
        BigInt tmp(*this);
        if ((*bigint_)[bigint_->get_size() - 1] == 0) {
            return tmp;
        }
        tmp.change_sign();
        return tmp;
    }

    friend BigInt operator+(const BigInt &x, const BigInt &y) {
        BigInt tmp;
        if (x.sign < 0 && y.sign < 0) {
            tmp.change_sign();
            tmp.sum_bigInt(*x.bigint_, *y.bigint_);
        } else if (x.sign < 0) {
            if (*x.bigint_ > *y.bigint_) {
                tmp.dif_bigInt(*x.bigint_, *y.bigint_);
                tmp.change_sign();
            } else {
                tmp.dif_bigInt(*y.bigint_, *x.bigint_);
            }
        } else if (y.sign < 0) {
            if (*y.bigint_ > *x.bigint_) {
                tmp.dif_bigInt(*y.bigint_, *x.bigint_);
                tmp.change_sign();
            } else {
                tmp.dif_bigInt(*x.bigint_, *y.bigint_);
            }
        } else {

            tmp.sum_bigInt(*x.bigint_, *y.bigint_);
        }
        return tmp;
    }

    friend BigInt operator-(const BigInt &x, const BigInt &y) {
        BigInt tmp;
        if (x.sign > 0 && y.sign < 0) {
            tmp.sum_bigInt(*x.bigint_, *y.bigint_);
        } else if (x.sign > 0) {
            if (*x.bigint_ >= *y.bigint_) {
                tmp.dif_bigInt(*x.bigint_, *y.bigint_);
            } else {
                tmp.change_sign();
                tmp.dif_bigInt(*y.bigint_, *x.bigint_);
            }
        } else if (y.sign < 0) {
            if (*y.bigint_ >= *x.bigint_) {
                tmp.dif_bigInt(*y.bigint_, *x.bigint_);
            } else {
                tmp.change_sign();
                tmp.dif_bigInt(*x.bigint_, *y.bigint_);
            }
        } else {
            tmp.change_sign();
            tmp.sum_bigInt(*x.bigint_, *y.bigint_);
        }
        tmp.dell_zero();
        return tmp;
    }

    friend BigInt operator*(const BigInt &x, const BigInt &y) {
        BigInt tmp;
        if (x == 0 || y == 0) {
            return 0;
        }
        if (x.sign != y.sign) {
            tmp.change_sign();
        }
        tmp.mul_bigInt(*x.bigint_, *y.bigint_);
        return tmp;
    }

    friend BigInt operator/(const BigInt &x, const BigInt &y) {
        BigInt tmp;
        if (y == 0) {
            std::cout << "ERROR division by zero" << std::endl;
            return tmp;
        }
        size_t size_x = x.bigint_->get_size();
        size_t size_y = y.bigint_->get_size();

        BigInt tmp_x(x);
        if (x.sign < 0) {
            tmp_x.change_sign();
        }
        BigInt abs_y(y);
        if (y.sign < 0) {
            abs_y.change_sign();
        }
        if (tmp_x < abs_y) {
            return tmp;
        }
        BigInt tmp_y(abs_y);
        int64_t mult_int = MAX_NUMBER / 2;

        if (size_x - size_y) {
            mult_int = 1;
            for (int i = 0; i < size_x - size_y; ++i) {
                mult_int *= MAX_NUMBER;
            }
        }
        while (tmp_x >= abs_y) {
            tmp_y = abs_y * mult_int;
            while (tmp_x >= tmp_y) {
                tmp = tmp + mult_int;
                tmp_x = tmp_x - tmp_y;
            }
            mult_int = mult_int / 2;
        }
        if (x.sign != y.sign && x != 0) {
            tmp.change_sign();
        }
        return tmp;
    }

    ~BigInt() {
        delete bigint_;
    }
};

