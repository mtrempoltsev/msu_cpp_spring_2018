#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "exception.hpp"
#include "token.hpp"

template <typename T>
class Calculator {
   public:
    Calculator(const std::string& _number);

    T expression();
    T term();
    T primary();
    Token<T> get_token();

   private:
    Token<T> get_digit_token(const std::string&);
    void putback(Token<T>&);
    std::string number;
    size_t indx{0};
    bool full{false};
    bool is_digit{false};  // continue get numbers from string
    Token<T> buf;
};

template <typename T>
Calculator<T>::Calculator(const std::string& _number) : number{_number} {}

template <typename T>
void Calculator<T>::putback(Token<T>& token) {
    full = true;
    buf = std::move(token);
}

template <typename T>
Token<T> Calculator<T>::get_digit_token(const std::string& str_digit) {
    std::istringstream ss(str_digit);
    T num;
    ss >> num;
    is_digit = false;
    return Token<T>('n', num);
}

template <typename T>
Token<T> Calculator<T>::get_token() {
    if (full) {  // if we already have token in buffer
        full = false;
        return std::move(buf);
    }
    std::string str_digit;
    while (indx < number.size()) {
        char cur = number[indx];
        switch (cur) {
            case ' ':
                indx++;
                break;
            case '(':
            case ')':
            case '+':
            case '-':
            case '*':
            case '/':
                if (is_digit) {
                    return get_digit_token(str_digit);
                }
                indx++;
                return Token<T>(cur);
            default:
                if (std::isdigit(cur) || cur == '.') {
                    is_digit = true;
                    str_digit += cur;
                    indx++;
                } else
                    throw EInput("Found wrong value" + str_digit);
        };
    };
    if (is_digit) {
        return get_digit_token(str_digit);
    }
    return Token<T>('e');
}

template <typename T>
T Calculator<T>::expression() {
    T left = term();
    Token<T> token = get_token();
    while (true) {
        switch (token.kind) {
            case '+':
                left += term();
                token = get_token();
                break;
            case '-':
                left -= term();
                token = get_token();
                break;
            default:
                putback(token);
                return left;
        }
    }
}

template <typename T>
T Calculator<T>::term() {
    T left = primary();
    Token<T> token = get_token();
    while (true) {
        switch (token.kind) {
            case '*':
                left *= primary();
                token = get_token();
                break;
            case '/': {
                T number = primary();
                if (number == T(0)) throw EDivideByZero();
                left /= number;
                token = get_token();
                break;
            }
            default:
                putback(token);
                return left;
        }
    }
}

template <typename T>
T Calculator<T>::primary() {
    Token<T> token = get_token();
    switch (token.kind) {
        case '(': {
            T d = expression();
            token = get_token();
            if (token.kind != ')') throw EInput("Need )");
            return d;
        }
        case 'n':
            return token.value;

        case '-':
            return -primary();

        case '+':
            return primary();
        default:
            throw EInput("Need primary expression");
    }
}
