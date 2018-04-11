#include <algorithm>
#include <stdexcept>
#include <string>

class wrong_operation: public std::exception {};
class division_by_zero: public std::exception {};

template <class T> class Calculator
{
    std::string str{};
    size_t index = 0;

    T expression();
    T term();
    T number();
public:
    T calculate(const std::string &str_);
};

template <class T>
T Calculator<T>::calculate(const std::string &str_)
{
    str = str_;
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    index = 0;
    return expression();
}

template <class T>
T Calculator<T>::expression()
{
    T value = term();
    while(index < str.size() && (str[index] == '+' || str[index] == '-')) {
        ++index;
        if(str[index - 1] == '+') {
            value = value + term();
        } else {
            value = value - term();
        }
    }
    if(index < str.size()) {
        throw wrong_operation();
    }
    return value;
}

template <class T>
T Calculator<T>::term()
{
    T value = number();
    while(index < str.size() && (str[index] == '*' || str[index] == '/')) {
        ++index;
        if(str[index - 1] == '*') {
            value = value * number();
        } else {
            T num = number();
            if(num == T(0)) throw division_by_zero();
            value = value / num;
        }
    }
    return value;
}

template <>
int Calculator<int>::number()
{
    size_t tmp_index = 0;
    int num = std::stoi(str.c_str() + index, &tmp_index);
    index += tmp_index;
    return num;
}
