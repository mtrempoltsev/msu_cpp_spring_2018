#include <iostream>
#include <string>
#include <cstdlib>
#include <ctype.h>

class err{
    std::string s;
public:
    err(const std::string& _s): s(_s) {};
    std::string get() const{
        return s;
    }
};

template<typename T>
struct Result{
    T acc;
    std::string rest;
    Result(T _acc,const std::string& _rest): acc(_acc), rest(_rest) {}
};

template <typename T>
struct Parser{
    T eval(std::string& s) {
        while (isspace(s[0])) {
            s.erase(s.begin());
        }
        Result<T> r = plusminus(s);
        if (!r.rest.empty()) {
            throw err("bad expression");
        }
        return r.acc;
    }
    Result<T> plusminus(std::string& s) {
        while (isspace(s[0])) {
            s.erase(s.begin());
        }
        Result<T> r = muldiv(s);
        T acc = r.acc;
        while (!r.rest.empty()) {
            if ((r.rest[0] != '+') && (r.rest[0] != '-')) {
                break;
            }
            char sig = r.rest[0];
            r.rest.erase(r.rest.begin());
            r = muldiv(r.rest);
            if (sig == '+') {
                acc = acc + r.acc;
            } else {
                acc = acc - r.acc;
            }
        }
        return Result<T>(acc, r.rest);
    }
    Result<T> muldiv(std::string& s) {
        while (isspace(s[0])) {
            s.erase(s.begin());
        }
        Result<T> r = num(s);
        T acc = r.acc;
        while(!r.rest.empty()) {
            if ((r.rest[0] != '*') && (r.rest[0] != '/')) {
                break;
            }
            char sig = r.rest[0];
            r.rest.erase(r.rest.begin());
            r = num(r.rest);
            if (sig == '*') {
                acc = acc * r.acc;
            } else {
                if (r.acc == 0) {
                    throw err("division by zero");
                }
                acc = acc / r.acc;
            }
        }
        return Result<T>(acc, r.rest);
    }
    Result<T> num(std::string& s) {
        int sig = 1, step = 0;
        while (isspace(s[0])) {
            s.erase(s.begin());
        }
        while ((s[0] == '+') || (s[0] == '-')) {
            if (s[0] == '-') {
                sig = -sig;
            }
            step++;
            s.erase(s.begin());
        }
        while (isspace(s[0])) {
            s.erase(s.begin());
        }
        T acc = 0;
        while((s[0] >= '0') && (s[0] <= '9')) {
            acc = acc * 10 + (s[0] - '0');
            s.erase(s.begin());
            step++;
        }
        while (isspace(s[0])) {
            s.erase(s.begin());
        }
        if (!step) {
            throw err("bad argv");
        }
        acc = acc * sig;
        return Result<T>(acc, s);
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "error" << std::endl;
        return 1;
    }
    try {
        Parser<int> p;
        std::string s(argv[1]);
        std::cout << p.eval(s) << std::endl;
    } catch(err& e) {
        std::cout << "error" << std::endl;
        return 1;
    }
    return 0;
}