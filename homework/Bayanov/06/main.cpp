#include <iostream>
#include <vector>
#include <cstring>

template<class T>
T calc(char* str){

}

inline bool IsOperation(char f){
    return f == '+' || f == '-' || f == '*' || f == '/';
}

inline bool IsDigit(char f){
    return '0' <= f && f <= '9';
}

template<>
int calc<int>(char* str){
    std::vector<int> operands;
    std::vector<char> operations;

    size_t len = 0;
    size_t walk = 0;
    while(str[walk]){
        if(str[walk] != ' '){
            if(!IsOperation(str[walk]) && !IsDigit(str[walk])){
                throw std::logic_error("");
            }
            str[len++] = str[walk];
        }
        ++walk;
    }
    size_t ind = 0;
    bool odd = true;
    while(ind < len){
        if(ind < len) {
            if (odd) {
                bool pos = true;
                if (str[ind] == '-' || str[ind] == '+') {
                    pos = str[ind] == '+';
                    ++ind;
                }
                if (ind >= len || !IsDigit(str[ind])) {
                    throw std::logic_error("");
                }
                long long value = 0;
                while (ind < len && IsDigit(str[ind])) {
                    value = value * 10 + (str[ind] - '0');
                    if (value > (1ll << 31) - 1) {
                        throw std::logic_error("");
                    }
                    ++ind;
                }
                if (!pos) {
                    value *= -1;
                }
                operands.push_back(value);
                if(operations.size() && (operations.back() == '*' ||
                                      operations.back() == '/')){
                    int a = operands.back();
                    operands.pop_back();
                    int b = operands.back();
                    operands.pop_back();
                    int res = b;
                    if(operations.back() == '*'){
                        res *= a;
                    }else{
                        if(!a){
                            throw std::logic_error("");
                        }
                        res /= a;
                    }
                    operations.pop_back();
                    operands.push_back(res);
                }
            } else {
                if (!IsOperation(str[ind])) {
                    throw std::logic_error("");
                } else {
                    operations.push_back(str[ind]);
                    ++ind;
                }
            }
        }

        odd ^= true;
    }
    if(operands.size() != operations.size() + 1 || !operands.size()){
        throw std::logic_error("");
    }
    int result = operands[0];
    for(size_t it = 1; it < operands.size(); ++it){
        if(operations[it - 1] == '+'){
            result += operands[it];
        }else{
            result -= operands[it];
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    if(argc != 2){
        std::cout << "error";
        return 1;
    }

    try{
        int value = calc<int>(argv[1]);
        std::cout << value << "\n";
    }catch(std::logic_error){
        std::cout << "error";
        return 1;
    }
    return 0;
}