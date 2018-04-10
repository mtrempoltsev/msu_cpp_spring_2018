#ifndef SPHERE_01_C_HW06_CALC_H
#define SPHERE_01_C_HW06_CALC_H

#include <string>
#include <iostream>
#include <exception>
#include <algorithm>

class calc_exception : public std::exception {
    std::string msg;
public:
    explicit calc_exception(std::string && err) : msg(std::move(err)) {
    }
    std::string & get_msg() {
        return msg;
    }
};

template<typename T>
class calc {
    std::string expression;
    std::string::const_iterator parse_pos;

    T brackets();
    T expr1();
    T expr2();
    T get_val();
public:
    explicit calc(const std::string & expr);
    explicit calc(std::string && expr);
    T eval();
};

bool is_num(char c) {
    return c >= '0' && c <= '9';
}

template<typename T>
T calc<T>::get_val() {
    if(parse_pos == expression.end()) {
        throw calc_exception("Unexpected end of string");
    }
    if(!is_num(*parse_pos)) {
        throw calc_exception("Not a number");
    } else {
        T acc = 0;
        do {
            acc *= 10;
            acc += *parse_pos++ - '0';
        } while(is_num(*parse_pos));
        return acc;
    }
}

template<typename T>
T calc<T>::eval() {
    T temp;
    T val = expr1();
    while(*parse_pos == '+' || *parse_pos == '-') {
        if (*parse_pos == '+') {
            ++parse_pos;
            temp = expr1();
            val += temp;
        } else if (*parse_pos == '-') {
            ++parse_pos;
            temp = expr1();
            val -= temp;
        }
    }
    return val;
}

template<typename T>
T calc<T>::brackets() {
    if(parse_pos == expression.end()) {
        throw calc_exception("Unexpected end of string");
    }
    if(*parse_pos != '(') {
        throw calc_exception("error");
    }
    ++parse_pos;
    T value = eval();
    if(*parse_pos != ')') {
        throw calc_exception("Unbalanced brackets");
    }
    ++parse_pos;
    return value;
}

template<typename T>
T calc<T>::expr1() {
    if(parse_pos == expression.end()) {
        throw calc_exception("Unexpected end of string");
    }
    T val = expr2();
    T temp;
    while(*parse_pos == '*' || *parse_pos == '/') {
        if (*parse_pos == '*') {
            ++parse_pos;
            temp = expr2();
            val *= temp;
        } else if (*parse_pos == '/') {
            ++parse_pos;
            temp = expr2();
            if(temp ==  T(0)) {
                throw calc_exception("Division by zero");
            }
            val /= temp;
        }
    }
    return val;
}

template<typename T>
T calc<T>::expr2() {
    if(parse_pos == expression.end()) {
        throw calc_exception("Unexpected end of string");
    } else {
        T val;
        if (*parse_pos == '-') {
            ++parse_pos;
            val = -expr2();
        } else if (*parse_pos == '(') {
            val = brackets();
        } else {
            val = get_val();
        }
        return val;
    }
}

template<typename T>
calc<T>::calc(const std::string &expr) : expression(expr), parse_pos(expression.begin()) {
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
}

template<typename T>
calc<T>::calc(std::string &&expr) : expression(std::move(expr)), parse_pos(expression.begin()) {
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
}

#endif //SPHERE_01_C_HW06_CALC_H