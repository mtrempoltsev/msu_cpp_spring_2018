#include<iostream>
#include<string>
#include<algorithm>

template <class T>
class Calculator {
    T division(std::string&& str);
    T divisionAndMultiply(std::string&& str);
    std::string normalize(std::string& str);
public:
    T calculate(std::string str);
};

template <class T>
T Calculator<T>::calculate(std::string str) {
    if (str.find("/0") != std::string::npos) {
        throw std::exception();
    }
    return division(normalize(str));
}

template <class T>
T Calculator<T>::division(std::string&& s) {
    for (int i = s.length(); i >= 1; i--) {
        if (s[i] == '+') {
            return division(s.substr(0, i)) + divisionAndMultiply(s.substr(i + 1));
        }
        else if (s[i] == '-' && (s[i - 1] != '*' || s[i - 1] != '/')) {
            return division(s.substr(0, i)) - divisionAndMultiply(s.substr(i + 1));
        }
    }
    auto res = s[0] == '-' ? -1 * divisionAndMultiply(s.substr(1)) : divisionAndMultiply(s.substr(0));
    return res;
}

template <class T>
T Calculator<T>::divisionAndMultiply(std::string&& str) {
    std::string post;
    for (size_t i = str.length(); i > 0; i--) {
        if (str[i] == '*' || str[i] == '/') {
            post = str.substr(i + 1);
            auto r = post[0] == '-' ? -1 * std::stoi(post.substr(1)): std::stoi(post);
            if (str[i] == '*') return divisionAndMultiply(str.substr(0, i)) * r;
            else return divisionAndMultiply(str.substr(0, i)) / r;
        }
    }
    auto res = str[0] == '-' ? -1 * std::stoi(str.substr(1)): std::stoi(str);
    return res;
}

template <class T>
std::string Calculator<T>::normalize(std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    for (int i = 0; i < str.length() - 1; i++) {
        if (str[i] == '-' && str[i + 1] == '-') {
            str[i] = ' ';
            str[i + 1] = '+';
        } else if (str[i] == '+' && str[i + 1] == '-') str[i] = ' ';
    }
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "error\n";
        return 1;
    }
    Calculator<int> a;
    try {
        std::cout << a.calculate(argv[1]) << std::endl;
    }
    catch (const std::runtime_error) {
        std::cerr << "error\n";
        return 1;
    }
    return 0;
}
