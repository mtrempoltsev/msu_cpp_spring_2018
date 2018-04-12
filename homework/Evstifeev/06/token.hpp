#ifndef TOKEN_H
#define TOKEN_H

template <typename T>
class Token {
   public:
    char kind;
    T value;
    Token() : kind('e'){};
    Token(char _kind) : kind(_kind){};
    Token(char _kind, T _value) : kind(_kind), value(_value){};
};

#endif
