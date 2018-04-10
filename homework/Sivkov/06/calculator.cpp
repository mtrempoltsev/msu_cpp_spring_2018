#include <iostream>
#include <memory>
#include <string>
#include <set>

template<class T>
class Parser {
private:
    const std::set<char> operations = {'+', '-', '*', '/'};
public:
    T calculate(const std::string &arg);

    T expression(const std::string &arg, size_t start, size_t fin);

    T from_string(const std::string &numb);
};

template<>
int Parser<int>::from_string(const std::string &numb) {
    for (auto symbol : numb)
        if (operations.find(symbol) == operations.end() && !(symbol < '9' && symbol > '0'))
            throw std::invalid_argument("invalid symbol");
    return std::stoi(numb);
}

template<class T>
T Parser<T>::calculate(const std::string &arg) {
    std::string clear_arg;
    clear_arg.reserve(arg.size());

    for (char symbol:arg) {
        if (symbol != ' ') {
            clear_arg.push_back(symbol);
        }
    }

    try {
        return expression(clear_arg, 0, clear_arg.size());
    }
    catch (std::invalid_argument &error) {
        std::cerr << "error" << std::endl;
        throw;
    }
    catch (std::out_of_range &error) {
        std::cerr << "error" << error.what() <<std::endl;
        throw;
    }
}

template<class T>
T Parser<T>::expression(const std::string &arg, size_t start, size_t fin) {
    size_t operator_pos = 0;
    for (size_t i = fin; i > start; --i) {
        if (arg[i - 1] == '+' || arg[i - 1] == '-' && i > 1 && arg[i - 2] < '9' && arg[i - 2] > '0') {
            operator_pos = i - 1;
            break;
        }
    }

    if (operator_pos == 0) {
        for (size_t i = fin; i > start; --i) {
            if (arg[i - 1] == '*' || arg[i - 1] == '/') {
                operator_pos = i - 1;
                break;
            }
        }
    }
    if (operator_pos == 0) {
        return from_string(arg.substr(start, fin));
    } else {
        char operation = arg[operator_pos];
        switch (operation) {
            case '+':
                return expression(arg, start, operator_pos) + expression(arg, operator_pos + 1, fin);
            case '-':
                return expression(arg, start, operator_pos) - expression(arg, operator_pos + 1, fin);
            case '*':
                return expression(arg, start, operator_pos) * expression(arg, operator_pos + 1, fin);
            case '/': {
                auto dividend = expression(arg, start, operator_pos);
                auto divider = expression(arg, operator_pos + 1, fin);
                if (divider == T(0)) throw std::invalid_argument("zero division");
                return dividend / divider;
            }
            default:
                throw std::invalid_argument("invalid operation");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "error" << std::endl;
        return 1;
    }
    auto calculator = Parser<int>();
    try {
        std::cout << calculator.calculate(argv[1]) << std::endl;
    }
    catch (std::invalid_argument &error) {
        return 1;
    }
    catch (std::out_of_range &error) {
        return 1;
    }
    return 0;
}
