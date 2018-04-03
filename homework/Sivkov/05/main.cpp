#include <iostream>
#include <algorithm>
#include <cstring>
#include <tuple>


class BigInt {
    //digits are stored in the reversed order
    char *data = nullptr;
    size_t size = 0;
    mutable int sign = 1;

    //special method for sub
    std::tuple<char *, char *, int> consecrate_for_sub(const BigInt &other) const {
        if (other.size > size) return std::make_tuple(other.data, data, sign * -1);
        else if (other.size < size) return std::make_tuple(data, other.data, sign);
        for (size_t i = size; i > 0; --i) {
            if (data[i - 1] < other.data[i - 1]) return std::make_tuple(other.data, data, sign * -1);
            else if (data[i - 1] > other.data[i - 1]) return std::make_tuple(data, other.data, sign);
        }
        return std::make_tuple(data, other.data, 0);
    }

    //special method for div
    static int numb_cmp_div(const BigInt &first, const BigInt &second) {
        if (first.size > second.size) return 1;
        else if (first.size < second.size) return -1;
        for (size_t i = first.size; i > 0; --i) {
            if (first.data[i - 1] < second.data[i - 1]) return -1;
            else if (first.data[i - 1] > second.data[i - 1]) return 1;
        }
        return 0;
    }

public:
    BigInt() {
        data = new char[2];
        data[0] = '0';
        data[1] = '\0';
        size = 1;
    }

    BigInt(long int init) {
        if (init < 0) {
            sign = -1;
            init *= -1;
        }
        size_t length = 0;
        long int tmp = init;
        if (init == 0) length = 1;
        for (length; tmp != 0; ++length) tmp /= 10;
        data = new char[length + 1];
        sprintf(data, "%li", init);
        std::reverse(data, data + length);
        data[length] = '\0';
        size = length;
    }

    BigInt(const BigInt &other) {
        data = new char[other.size + 1];
        std::strcpy(data, other.data);
        data[other.size] = '\0';
        size = other.size;
        sign = other.sign;
    }

    BigInt(BigInt &&movable) noexcept {
        data = movable.data;
        size = movable.size;
        sign = movable.sign;
        movable.data = nullptr;
    }

    BigInt &operator=(long int init) {
        delete[] data;
        if (init < 0) {
            sign = -1;
            init *= -1;
        }
        size_t length = 0;
        long int tmp = init;
        for (length; tmp != 0; ++length) tmp /= 10;
        data = new char[length + 1];
        sprintf(data, "%li", init);
        std::reverse(data, data + length);
        data[length] = '\0';
        size = length;
    }

    BigInt &operator=(const BigInt &other) {
        if (this == &other) return *this;
        delete[] data;
        data = new char[other.size + 1];
        std::strcpy(data, other.data);
        size = other.size;
        sign = other.sign;
    }

    BigInt &operator=(BigInt &&movable) noexcept {
        if (data == movable.data) return *this;
        delete[] data;
        data = movable.data;
        size = movable.size;
        sign = movable.sign;
        movable.data = nullptr;
    }

    friend std::ostream &operator<<(std::ostream &os, const BigInt &object);

    BigInt operator+(const BigInt &other) const {
        if (sign * other.sign < 0) {
            if (other.sign < 0) { ;
                other.sign = 1;
                auto tmp_res = *this - other;
                other.sign = -1;
                return tmp_res;
            } else {
                sign = 1;
                auto tmp_res = other - *this;
                sign = -1;
                return tmp_res;
            }
        }
        size_t fin_size = std::max(size, other.size);
        size_t min_size = std::min(size, other.size);
        auto tmp = new char[fin_size + 2];
        int remind = 0;
        for (size_t i = 0; i < fin_size; ++i) {
            int term_1, term_2;
            if (i < size) term_1 = data[i] - '0';
            else term_1 = 0;
            if (i < other.size) term_2 = other.data[i] - '0';
            else term_2 = 0;
            int sum = term_1 + term_2 + remind;
            tmp[i] = char(sum % 10) + '0';
            remind = sum / 10;
        }
        auto res = BigInt();
        res.size = 0;
        delete[] res.data;

        if (remind > 0) {
            tmp[fin_size] = char(remind) + '0';
            tmp[fin_size + 1] = '\0';
            res.size = fin_size + 1;
        } else {
            tmp[fin_size] = '\0';
            res.size = fin_size;
        }
        res.data = tmp;
        res.sign = sign;
        return res;
    }

    BigInt operator-(const BigInt &other) const {
        if (sign * other.sign < 0) {
            if (other.sign < 0) {
                other.sign = 1;
                auto tmp_res = *this + other;
                other.sign = -1;
                return tmp_res;
            } else if (sign < 0) {
                other.sign = -1;
                auto tmp_res = *this + other;
                other.sign = 1;
                return tmp_res;
            }
        }
        char *first_numb = nullptr;
        char *second_numb = nullptr;
        int res_sign = 0;

        std::tie(first_numb, second_numb, res_sign) = this->consecrate_for_sub(other);
        size_t second_size = std::min(size, other.size);
        size_t fin_size = std::max(size, other.size);

        auto res_data = new char[fin_size + 1];
        auto res = BigInt();
        res.size = 0;
        delete[] res.data;

        if (res_sign == 0) {
            res_data[0] = '0';
            res_data[1] = '\0';
            res.data = res_data;
            res.sign = 1;
            res.size = 1;
            return res;
        }

        int remind = 0;
        for (size_t i = 0; i < fin_size; ++i) {
            int sub;
            if (i < second_size) sub = second_numb[i] - '0';
            else sub = 0;
            int dif = first_numb[i] - '0' - sub;
            if (dif < 0) {
                if (remind == 0) remind = 10;
                else remind = 9;
                dif += remind;
            } else if (dif > 0 && remind > 0) {
                dif -= 1;
                remind = 0;
            } else if (remind != 0) {
                remind = 9;
                dif += remind;
            }
            res_data[i] = char(dif + '0');
        }
        size_t last_sig_char = fin_size - 1;
        for (last_sig_char; res_data[last_sig_char] == '0' && last_sig_char > 0; --last_sig_char);
        res_data[last_sig_char + 1] = '\0';
        res.data = res_data;
        res.sign = res_sign;
        res.size = last_sig_char + 1;
        return res;
    }

    BigInt operator*(const BigInt &other) const {
        size_t fin_size = size + other.size;
        auto res = BigInt();
        res.size = 0;
        delete[] res.data;

        res.data = new char[fin_size + 2];
        std::fill(res.data, res.data + fin_size + 1, '0');
        res.data[fin_size + 1] = '\0';
        res.size = fin_size + 1;
        for (size_t i = 0; i < other.size; ++i) {
            int curr_dig = other.data[i] - '0';
            auto tmp = new char[size + 2 + i];
            int remind = 0;
            for (size_t q = 0; q < size + 1 + i; ++q) tmp[q] = '0';

            for (size_t j = i; j < size + i; ++j) {
                int mul = (data[j - i] - '0') * curr_dig + remind;
                auto tmp_dig = char(mul % 10 + '0');
                remind = mul / 10;
                tmp[j] = tmp_dig;
            }
            if (remind > 0) {
                tmp[size + i] = char(remind + '0');
            }

            auto tmp_obj = BigInt();
            tmp_obj.size = 0;
            delete[] tmp_obj.data;
            tmp_obj.data = tmp;
            tmp_obj.size = size + i + 1;
            tmp_obj.data[tmp_obj.size] = '\0';
            res = res + tmp_obj;
        }
        for (res.size; res.data[res.size - 1] == '0' && res.size > 1; --res.size);
        res.data[res.size] = '\0';
        if (res.data[res.size - 1] == '0') res.sign = 1;
        else res.sign = sign * other.sign;
        return res;
    }

    BigInt operator/(const BigInt &other) const {

        if (size < other.size || other.data[other.size - 1] == '0') {
            return BigInt(0);
        }

        int this_sign = sign;
        int other_sign = other.sign;
        sign = 1;
        other.sign = 1;
        if (*this < other) {
            sign = this_sign;
            other.sign = other_sign;
            return BigInt(0);
        }

        auto curr_divider = BigInt(0);
        auto res = BigInt();
        res.size = 0;
        delete[] res.data;
        res.data = new char[size + 1];

        size_t curr_not_taken = size;
        bool fin_flag = false;
        bool first_time = true;
        while (true) {
            int counter = 0;
            while (numb_cmp_div(curr_divider, other) == -1) {
                if (curr_not_taken == 0) {
                    fin_flag = true;
                    break;
                }
                if (counter >= 1 && !first_time) {
                    res.data[res.size] = '0';
                    res.size++;
                }
                int curr_dig = data[curr_not_taken - 1] - '0';
                curr_divider = curr_divider * 10;
                curr_divider = curr_divider + curr_dig;

                --curr_not_taken;
                counter++;
            }
            first_time = false;
            if (fin_flag) {
                if (counter > 0) {
                    res.data[res.size] = '0';
                    res.size++;
                }
                break;
            }

            auto curr_mul = BigInt(0);
            int curr_numb = 0;
            while (numb_cmp_div(curr_divider, curr_mul) >= 0) {
                curr_mul = curr_mul + other;
                ++curr_numb;
            }
            curr_mul = curr_mul - other;
            --curr_numb;

            curr_divider = curr_divider - curr_mul;

            res.data[res.size] = char(curr_numb + '0');
            res.size++;
        }
        std::reverse(res.data, res.data + res.size);
        res.data[res.size] = '\0';
        res.sign = other_sign * this_sign;

        other.sign = other_sign;
        sign = this_sign;

        return res;
    }

    BigInt& operator++() {
        if (sign < 0) {
            sign = 1;
            --*this;
            sign = -1;
        }
        size_t pos = 0;
        while (true) {
            if (data[pos] == '9') {
                data[pos] = '0';
                pos++;
            }
            else {
                data[pos] += 1;
                break;
            }
        }
        if (pos == size - 1 && data[pos] == '0') {
            auto tmp = new char[size + 1];
            std::strcpy(tmp, data);
            tmp[size] = '1';
            size++;
            tmp[size] = '\0';
            delete[] data;
            data = tmp;
        }
        return *this;
    }

    BigInt& operator--() {
        if (sign < 0) {
            sign = 1;
            ++*this;
            sign = -1;
        }
        size_t pos = 0;
        while (true) {
            if (data[pos] == '0') {
                data[pos] = '9';
                pos++;
            }
            else {
                data[pos] -= 1;
                break;
            }
        }
        if (pos == size - 1 && data[pos] == '0' && pos > 1) {
            data[pos] = '\0';
            size--;
        }
        return *this;
    }

    BigInt operator-() {
        if (data[size - 1] == '0') return BigInt(*this);
        auto tmp = BigInt(*this);
        tmp.sign *= -1;
        return tmp;
    }

    bool operator==(const BigInt &other) const {
        if (size != other.size || sign != other.sign) return false;
        for (size_t i = size; i > 0; --i) {
            if (data[i - 1] != other.data[i - 1]) return false;
        }
        return true;
    }

    bool operator!=(const BigInt &other) const {
        return !(*this == other);
    }

    bool operator<(const BigInt &other) const {
        if (*this == other) return false;
        if (sign < other.sign) return true;
        else if (sign > other.sign) return false;
        else if (size > other.size) return false;
        else if (size < other.size) return true;
        if (sign < 0) {
            sign = 1;
            other.sign = 1;
            bool res = *this > other;
            sign = -1;
            other.sign = -1;
            return res;
        }
        for (size_t i = size; i > 0; --i) {
            if (data[i - 1] > other.data[i - 1]) return false;
            else if (data[i - 1] < other.data[i - 1]) return true;
        }
        return false;
    }

    bool operator>(const BigInt &other) const {
        if (*this == other) return false;
        return !(*this < other);
    }

    bool operator>=(const BigInt &other) const {
        if (*this == other) return true;
        else return (*this > other);
    }

    bool operator<=(const BigInt &other) const {
        if (*this == other) return true;
        else return (*this < other);
    }

    bool operator==(long int other) const { return *this == BigInt(other); }

    bool operator!=(long int other) const { return *this != BigInt(other); }

    bool operator<(long int other) const { return *this < BigInt(other); }

    bool operator>(long int other) const { return *this > BigInt(other); }

    bool operator>=(long int other) const { return *this >= BigInt(other); }

    bool operator<=(long int other) const { return *this <= BigInt(other); }

    ~BigInt() {
        delete[] data;
    }
};

std::ostream &operator<<(std::ostream &os, const BigInt &object) {
    auto buf = new char[object.size + 1];
    std::reverse_copy(object.data, object.data + object.size, buf);
    if (object.sign < 0) os << '-';
    buf[object.size] = '\0';
    os << buf;
    delete[] buf;
    return os;
}