#include <iostream>
#include <string>
#include <sstream>

template <class T>
class Calc
{
    T res = T();
    using iss = std::istringstream;
    using terr = std::invalid_argument;
    inline bool isfp(char c) const
    {
        return c == '*' || c == '/';
    }
    inline bool issp(char c) const
    {
        return c == '+' || c == '-';
    }
    T GetSign(iss &ss) const
    {
        char sign;
        ss >> sign;
        if (!ss) {
            throw terr("");
        } else if (sign == '-') {
            return -1;
        } else if (sign == '+') {
            return 1;
        } else {
            ss.unget();
            return 1;
        }
    }
    T GetNum(iss &ss) const
    {
        T sign = GetSign(ss);
        T t;
        if (ss >> t) {
            return t * sign;
        } else {
            throw terr("");
        }
    }
    T MulOrDiv(iss &ss) const
    {
        T val1 = GetNum(ss);
        char op;
        while (ss >> op && isfp(op)) {
            T val2 = GetNum(ss);
            if (op == '*') {
                val1 *= val2;
            } else {
                if (val2 == 0) {
                    throw terr("");
                } else {
                    val1 /= val2;
                }
            }
        }
        if (ss) {
            ss.unget();
        }
        return val1;
    }
    T SumOrSub(iss &ss) const
    {
        T val1 = MulOrDiv(ss);
        char op;
        while (ss >> op && issp(op)) {
            T val2 = MulOrDiv(ss);
            if (op == '+') {
                val1 += val2;
            } else {
                val1 -= val2;
            }
        }
        if (ss) {
            throw terr("");
        }
        return val1;
    }
public:
    Calc(const std::string &s)
    {
        iss ss(s);
        res = SumOrSub(ss);
    }
    T GetRes() const
    {
        return res;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "error" << std::endl;
        return 1;
    }
    try {
        std::cout << Calc<int>(argv[1]).GetRes() << std::endl;
    } catch (const std::invalid_argument &) {
        std::cerr << "error" << std::endl;
        return 1;
    }
    return 0;
}
