#pragma once

#include <string>
#include <stdexcept>
#include <ctype.h>
#include <stdlib.h>
#include <memory>

std::string trimWhitespaces(const std::string& str)
{
    std::unique_ptr<char[]> result(new char[1 + str.length()]);

    size_t j = 0;
    for (size_t i = 0; i <= str.length(); ++i) {
        if (str[i] != ' ' && str[i] != '\t') {
            result[j++] =  str[i];
        }
    }

    return std::string(result.get());
}

template <typename T>
class Calc
{
private:
    T getNextNum(std::string& str)
    {
        bool negative = false;

        // число также может начинаться с минуса
        if (str[0] == '-') {
            negative = true;
            str = str.substr(1);
        }
        // разрешаем только цифры и точку
        size_t  i;
        for (i = 0; i < str.length(); ++i) {
            if (!isdigit(str[i])) {
                if (str[i] == '+' || str[i] == '-' ||
                    str[i] == '*' || str[i] == '/')
                {
                    break;
                } else {
                    throw std::runtime_error("error");
                }
            }
        }

        if (i == 0) { // что-либо похожее на число мы не нашли
            throw std::runtime_error("error");
        }

        T number(atoi(str.substr(0, i).c_str()));
        if (negative) {
            number = -number;
        }

        str = str.substr(i);

        return number;
    }

    T computeNextMultiplicationPart(std::string& str)
    {
        auto currentNumber =  getNextNum(str);

        while (str.length() > 0) {
            if (!(str[0] == '*' || str[0] == '/')) {
                if (str[0] == '+' || str[0] == '-') {
                    break;
                } else {
                    throw std::runtime_error("error");
                }
            }

            char sign = str[0];
            str = str.substr(1);

            auto nextNumber = getNextNum(str);
            if (sign == '*') {
                currentNumber *= nextNumber;
            } else {
                if (nextNumber == 0) {
                    throw std::runtime_error("error");
                }
                currentNumber /= nextNumber;
            }
        }

        return currentNumber;
    }

public:
    T compute(const std::string& input_str)
    {
        std::string str = trimWhitespaces(input_str);

        if (!isdigit(str.back())) {
            throw std::runtime_error("error");
        }

        auto currentNumber =  computeNextMultiplicationPart(str);


        while (str.length() > 0) {
            if (!(str[0] == '+' || str[0] == '-')) {
                break;
            }

            char sign = str[0];
            str = str.substr(1);

            auto nextNumber = computeNextMultiplicationPart(str);
            if (sign == '+') {
                currentNumber += nextNumber;
            } else {
                currentNumber -= nextNumber;
            }
        }

        return currentNumber;
    }
};
