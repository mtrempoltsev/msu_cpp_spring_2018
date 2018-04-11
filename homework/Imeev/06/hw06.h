#include <algorithm>
#include <stdexcept>
#include <string>

class wrong_operation: public std::exception {};
class division_by_zero: public std::exception {};

template <class T> class Calculator
{
    std::string str{};
    size_t index = 0;

    T expression(T value = T(0), char op = '+');
    T term(T value = T(1), char op = '*');
    T number();
public:
    Calculator(std::string str_);

    T calculate() { return expression(); };
};

template <class T>
Calculator<T>::Calculator(std::string str_): str(str_)
{
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
}

template <class T>
T Calculator<T>::expression(T value, char op)
{
    if(op == '+') {
        value = value + term();
    } else {
        value = value - term();
    }
    if(index < str.size()) {
        if(str[index] == '+' || str[index] == '-') {
            ++index;
            return expression(value, str[index - 1]);
        } else {
            throw wrong_operation();
        }
    }
    return value;
}

template <class T>
T Calculator<T>::term(T value, char op)
{
    if(op == '*') {
        value = value * number();
    } else {
        T num = number();
        if(num == T(0)) throw division_by_zero();
        value = value / num;
    }
    if(index < str.size() && (str[index] == '*' || str[index] == '/')) {
        ++index;
        return term(value, str[index - 1]);
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
