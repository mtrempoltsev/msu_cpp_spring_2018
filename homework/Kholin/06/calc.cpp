#include <string>
#include <iostream>
#include <stdint.h>

class Error {
};

template <typename T>
class Calculator {
public:
    T Calculate(const std::string& input) {
        std::string inputWithoutSpaces = deleteSpaces(input);
        return solve(inputWithoutSpaces, 0, inputWithoutSpaces.length(), 1);
    }
private:
    std::string deleteSpaces(const std::string& input) {
        std::string answer = "";
        for (uint32_t i = 0; i < input.length(); ++i) {
            if (input[i] != ' ') {
                answer += input[i];
            }
        }
        return answer;
    }

    T solve(const std::string& input, const uint32_t begin, const uint32_t end, const T minus) {
        if (begin >= end) {
            return 0;
        }
        for (uint32_t i = begin; i < end; ++i) {
            if (input[i] == '+') {
                if (i + 1 == end) {
                    throw Error();
                }
                if (i == begin) {
                    return solve(input, i + 1, end, minus);
                }
                return minus * solve(input, begin, i, 1) + solve(input, i + 1, end, 1);
            }
            if (input[i] == '-') {
                if (i + 1 == end) {
                    throw Error();
                }
                if (i == begin) {
                    return solve(input, i + 1, end, -minus);
                }
                return minus * solve(input, begin, i, 1) + solve(input, i + 1, end, -1);
            }
        }
        for (uint32_t i = begin; i < end; ++i) {
            if (input[i] == '*') {
                if (i + 1 == end) {
                    throw Error();
                }
                return minus * (solve(input, begin, i, 1) * solve(input, i + 1, end, 1));
            }
            if (input[i] == '/') {
                if (i + 1 == end) {
                    throw Error();
                }
                T x, y;
                x = solve(input, begin, i, 1);
                y = solve(input, i + 1, end, 1);
                if (y != 0) {
                    return minus * x / y;
                } else {
                    throw Error();
                }
            }
        }
        T x = 0;
        for (uint32_t i = end; i > begin; --i) {
            if ('0' <= input[i - 1] && input[i - 1] <= '9') {
                x = x * 10 + (input[i - 1] - '0');
            } else {
                throw Error();
            }
        }
        return minus * x;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "error" << std::endl;
        return 1;
    }
    auto calc = new Calculator<int>();
    try {
        std::cout << calc->Calculate(std::string(argv[1])) << std::endl;
    }
    catch(const Error& error) {
        std::cout << "error" << std::endl;
        return 1;
    }
    return 0;
}
