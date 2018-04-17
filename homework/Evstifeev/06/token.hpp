#include <iostream>
#ifndef TOKEN_H
#define TOKEN_H

template <typename T>
class Token {
   public:
    char kind;
    T value;
    Token() : kind('e'){};
    Token(const char& _kind) : kind(_kind){};
    Token(const char& _kind, const T& _value) : kind(_kind), value(_value){};
    Token(const Token&& moved) : kind(moved.kind), value(moved.value){};
    Token& operator=(Token&& moved) {
        if (this == &moved) return *this;
        value = moved.value;
        kind = moved.kind;
        moved.value = 0;
        moved.value = 'e';
        return *this;
    }
    Token(const Token&) = delete;
    Token& operator=(const Token&) = delete;
};

#endif
