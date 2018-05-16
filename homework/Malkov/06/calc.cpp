#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

template <class T>
class Calculator
{
private:
    T minus(std::istringstream &iss) const
    {
        char c;
        iss >> c;

        if (!iss) {
            throw std::invalid_argument("error");
        }

        if (c != '-') {
            iss.putback(c);
        }

        return c == '-' ? -1 : 1;
    }

    T number_parsing(std::istringstream &iss) const
    {
        T sign = minus(iss), num;
        iss >> num;

        if (!iss) {
            throw std::invalid_argument("error");
        }

        return num * sign;
    }

    T mul(std::istringstream &iss) const
    {
        T num1 = number_parsing(iss);

        char oper;
        while (iss >> oper && (oper == '*' || oper == '/')) {
            T num2 = number_parsing(iss);

            T res;
            if (oper == '*') {
                res = num1 * num2;
            } else {
                if (num2 == 0) {
                    throw std::invalid_argument("error");
                }
                res = num1 / num2;
            }

            num1 = res;
        }

        if (iss) {
            iss.putback(oper);
        }

        return num1;
    }

    T sum(std::istringstream &iss) const
    {
        T num1 = mul(iss);

        char oper;
        while (iss >> oper && (oper == '+' || oper == '-')) {
            T num2 = mul(iss);

            T res;
            if (oper == '-') {
                res = num1 - num2;
            } else {
                res = num1 + num2;
            }

            num1 = res;
        }

        if (iss) {
            throw std::invalid_argument("error");
        }

        return num1;
    }

    T answer = T();

public:
    Calculator(const std::string &s)
    {
        std::istringstream iss(s);

        answer = sum(iss);
    }

    T get_answer() const
    {
        return answer;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "error" << std::endl;
        return 1;
    }

    try {
        std::cout << Calculator<int>(argv[1]).get_answer() << std::endl;
    } catch(const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
