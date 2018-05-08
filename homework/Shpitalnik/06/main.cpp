#include <iostream>

class Error{};

template<class T>
class Calc{
    T getVar(const char *&str);
public:
    T calculate(const char *str);
};

template <class T>
T Calc<T>::getVar(const char *&str) {
    T res = 0;
    bool is_neg = false;
    int i=0;
    while(str[i] == ' ')
        i++;
    while(str[i] == ' ' || str[i] == '-') {
        if(str[i] == '-')
            is_neg = not is_neg;
        i++;
    }
    if (str[i] < '0'|| str[i] >'9')
        throw Error();
    do{
        res*=10;
        res+= (str[i] - '0');
        i++;
    } while(str[i] <= '9' && str [i] >= '0');
    str = &(str[i]);
    if (is_neg)
        res = -res;
    return res;
}


template <class T>
T Calc<T>::calculate(const char *str) {
    T op = getVar(str);
    T op2;
    do {
        switch (str[0]) {
            case (0):
                return op;
            case ('+'):
                str = &(str[1]);
                return op + calculate(str);
            case ('-'):
                return op + calculate(str);
            case ('*'):
                str = &(str[1]);
                op *= getVar(str);
                break;
            case ('/'):
                str = &(str[1]);
                op2 = getVar(str);
                if (op2 == 0)
                    throw Error();
                op /= op2;
                break;
            case (' '):
                str = &(str[1]);
                break;
            default:
                throw Error();
        }
    } while(true);
}

int main(int argc, char** argv) {
    Calc<int> c;
    if (argc != 2) {
        std::cout << "error";
        return 1;
    }
    try {
        std::cout << c.calculate(argv[1]);
    }
    catch (const Error& error){
        std::cout << "error";
        return 1;
    }
    return 0;
}
