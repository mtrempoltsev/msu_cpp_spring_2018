#include <string>
#include <iostream>
#include <stdint.h>

class Error {
};

template <typename T>
class Calculator {
public:
    Calculator(const std::string& input) {
        std::string inputWithoutSpaces = deleteSpaces(input);
        try {
            _result = solve(inputWithoutSpaces, 0, inputWithoutSpaces.length(), 1);
        }
        catch(const Error& error) {
            _isError = true;
            std::cout << "error" << std::endl;
        }
    }

    bool isError() {
        return _isError;
    }
    
    T result() {
        return _result;
    }
private:
    bool _isError = false;
    T _result;

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
                    try {
                        return solve(input, i + 1, end, minus);
                    }
                    catch(const Error& error) {
                        throw error;
                    }
                }
                try {
                    return minus * solve(input, begin, i, 1) + solve(input, i + 1, end, 1);
                }
                catch(const Error& error) {
                    throw error;
                }
            }
            if (input[i] == '-') {
                if (i + 1 == end) {
                    throw Error();
                }
                if (i == begin) {
                    try {
                        return solve(input, i + 1, end, -minus);
                    }
                    catch(const Error& error) {
                        throw error;
                    }
                }
                try {
                    return minus * solve(input, begin, i, 1) + solve(input, i + 1, end, -1);
                }
                catch(const Error& error) {
                    throw error;
                }
            }
        }
        for (uint32_t i = begin; i < end; ++i) {
            if (input[i] == '*') {
                if (i + 1 == end) {
                    throw Error();
                }
                try {
                    return minus * (solve(input, begin, i, 1) * solve(input, i + 1, end, 1));
                }
                catch(const Error& error) {
                    throw error;
                }
            }
            if (input[i] == '/') {
                if (i + 1 == end) {
                    throw Error();
                }
                T x, y;
                try {
                    x = solve(input, begin, i, 1);
                    y = solve(input, i + 1, end, 1);
                }
                catch(const Error& error) {
                    throw error;
                }
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
    auto calc = new Calculator<int>(std::string(argv[1]));
    if (!calc->isError()) {
        std::cout << calc->result() << std::endl;
        return 0;
    } else {
        return 1;
    }
}
