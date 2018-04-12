#include <string>
#include <iostream>
#include <stdint.h>

template <typename T>
class Calculator {
public:
    
    Calculator(int32_t argc, char* argv[]) {
        if (argc != 2) {
            throw std::string("error");
        }
        std::string input = deleteSpaces(std::string(argv[1]));
        try {
            _result = solve(input, 0, input.length(), 1);
        }
        catch(const std::string& error) {
            throw std::string("error");
        }
    }

    
    T result() {
        return _result;
    }
private:
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
                    throw std::string("error");
                }
                if (i == begin) {
                    try {
                        return solve(input, i + 1, end, minus);
                    }
                    catch(const std::string& error) {
                        throw error;
                    }
                }
                try {
                    return minus * solve(input, begin, i, 1) + solve(input, i + 1, end, 1);
                }
                catch(const std::string& error) {
                    throw error;
                }
            }
            if (input[i] == '-') {
                if (i + 1 == end) {
                    throw std::string("error");
                }
                if (i == begin) {
                    try {
                        return solve(input, i + 1, end, -minus);
                    }
                    catch(const std::string& error) {
                        throw error;
                    }
                }
                try {
                    return minus * solve(input, begin, i, 1) + solve(input, i + 1, end, -1);
                }
                catch(const std::string& error) {
                    throw error;
                }
            }
        }
        for (uint32_t i = begin; i < end; ++i) {
            if (input[i] == '*') {
                if (i + 1 == end) {
                    throw std::string("error");
                }
                try {
                    return minus * (solve(input, begin, i, 1) * solve(input, i + 1, end, 1));
                }
                catch(const std::string& error) {
                    throw error;
                }
            }
            if (input[i] == '/') {
                if (i + 1 == end) {
                    throw std::string("error");
                }
                T x, y;
                try {
                    x = solve(input, begin, i, 1);
                    y = solve(input, i + 1, end, 1);
                }
                catch(const std::string& error) {
                    throw error;
                }
                if (y != 0) {
                    return minus * x / y;
                } else {
                    throw std::string("error");
                }
            }
        }
        T x = 0;
        for (uint32_t i = end; i > begin; --i) {
            if ('0' <= input[i - 1] && input[i - 1] <= '9') {
                x = x * 10 + (input[i - 1] - '0');
            } else {
                throw std::string("error");
            }
        }
        return minus * x;
    }
};

int main(int argc, char* argv[]) {
    try {
        Calculator<int> calc(argc, argv);
        std::cout << calc.result() << std::endl;
        return 0;
    }
    catch(const std::string& error) {
        std::cout << error << std::endl;
        return 1;
    }
}
