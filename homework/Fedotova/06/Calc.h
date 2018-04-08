#pragma once
#include <string>
#include <sstream>

template <typename T>
class Calc
{
public:
    class Error {};
private:
        std::string::const_iterator find_last_plus_or_minus(std::string::const_iterator start, std::string::const_iterator stop) const {
        bool prev_op = true;
        auto res = stop;
        for (auto it = start; it != stop; it++) {
            if (*it == '+' || (*it == '-' && !prev_op))
                res = it;
            if (*it == '+' || *it == '-' || *it == '*' || *it == '/')
                prev_op = true;
            if (*it >= '0' && *it <= '9')
                prev_op = false;
        }
        return res;
    }

    std::string::const_iterator find_last_mult_or_div(std::string::const_iterator start, std::string::const_iterator stop) const {
        auto res = stop;
        for (auto it = start; it != stop; it++) {
            if (*it == '*' || *it == '/')
                res = it;
        }
        return res;
    }
    
    std::string::const_iterator find_first_unary_minus(std::string::const_iterator start, std::string::const_iterator stop) const {
        for (auto it = start; it != stop; it++) {
            if (*it == '-')
                return it;
        }
        return stop;
    }

    T calculate_part(std::string::const_iterator start, std::string::const_iterator stop, bool check_zero) const {
        T res;
        std::string::const_iterator it = find_last_plus_or_minus(start, stop);
        if (it != stop) {
            if (*it == '+')
                return calculate_part(start, it, false) + calculate_part(it + 1, stop, false);
            if (*it == '-')
                return calculate_part(start, it, false) - calculate_part(it + 1, stop, false);
        }
        it = find_last_mult_or_div(start, stop);
        if (it != stop) {
            if (*it == '*')
                return calculate_part(start, it, false) * calculate_part(it + 1, stop, false);
            if (*it == '/')
                return calculate_part(start, it, false) / calculate_part(it + 1, stop, true);
        }
        it = find_first_unary_minus(start, stop);
        if (it != stop) {
            return - calculate_part(it + 1, stop, check_zero);
        }
        std::istringstream ss(std::string(start, stop));
        if (ss >> res && (res != 0 || !check_zero))
            return res;
        throw Calc::Error();
    }
public:
    T calculate(const std::string& s) const {
        return calculate_part(s.begin(), s.end(), false);
    }
};
