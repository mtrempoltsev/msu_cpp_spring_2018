#include <iostream>
#include <vector>
#include <cstring>

template<class T>
class Calc{
public:
    T operator()(char* str);

};



template<>
class Calc<int> {
    std::vector<int> operands;
    std::vector<char> operations;

    inline bool IsOperation(char f){
        return f == '+' || f == '-' || f == '*' || f == '/';
    }

    inline bool IsDigit(char f){
        return '0' <= f && f <= '9';
    }

    inline void shift_spaces(const char* str, size_t& ind, size_t len){
        while(ind < len && str[ind] == ' '){
            ++ind;
        }
    }

public:
    int operator()(const char *str) {
        operands.clear();
        operations.clear();

        size_t len = strlen(str);

        size_t ind = 0;
        bool odd = true;
        while (ind < len) {
            shift_spaces(str, ind, len);
            if (ind < len) {
                if (odd) {
                    bool pos = true;
                    if (str[ind] == '-' || str[ind] == '+') {
                        pos = str[ind] == '+';
                        ++ind;
                    }
                    shift_spaces(str, ind, len);
                    if (ind >= len || !IsDigit(str[ind])) {
                        throw std::logic_error("Invalid input");
                    }
                    long long value = 0;
                    while (ind < len && IsDigit(str[ind])) {
                        value = value * 10 + (str[ind] - '0');
                        if (value > (1ll << 31) - 1) {
                            throw std::logic_error("Invalid input");
                        }
                        ++ind;
                    }
                    if (!pos) {
                        value *= -1;
                    }
                    operands.push_back(value);
                    if (operations.size() && (operations.back() == '*' ||
                                              operations.back() == '/')) {
                        int a = operands.back();
                        operands.pop_back();
                        int b = operands.back();
                        operands.pop_back();
                        int res = b;
                        if (operations.back() == '*') {
                            res *= a;
                        } else {
                            if (!a) {
                                throw std::logic_error("Impossible divide by zero");
                            }
                            res /= a;
                        }
                        operations.pop_back();
                        operands.push_back(res);
                    }
                } else {
                    if (!IsOperation(str[ind])) {
                        throw std::logic_error("Invalid input");
                    } else {
                        operations.push_back(str[ind]);
                        ++ind;
                    }
                }
            }

            odd ^= true;
        }
        if (operands.size() != operations.size() + 1 || !operands.size()) {
            throw std::logic_error("Invalid input");
        }
        int result = operands[0];
        for (size_t it = 1; it < operands.size(); ++it) {
            if (operations[it - 1] == '+') {
                result += operands[it];
            } else {
                result -= operands[it];
            }
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
    if(argc != 2){
        std::cout << "error";
        return 1;
    }

    Calc<int> calc;

    try{
        int value = calc(argv[1]);
        std::cout << value << "\n";
    }catch(std::logic_error&){
        std::cout << "error";
        return 1;
    }
    return 0;
}