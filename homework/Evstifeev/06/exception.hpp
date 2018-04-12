#ifndef INTEXCEPT_H
#define INTEXCEPT_H

#include <stdexcept>

class MyException : public std::runtime_error {
   public:
    MyException(const std::string &s) : std::runtime_error(s) {}
};

class EDivideByZero : public MyException {
   public:
    EDivideByZero() : MyException("Division by zero") {}
    EDivideByZero(const std::string &s) : MyException(s) {}
};

class EInput : public MyException {
   public:
    EInput(const std::string &s) : MyException(s) {}
};

#endif
