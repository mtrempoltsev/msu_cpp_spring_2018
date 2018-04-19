#include <iostream>
#include <string>
#include <exception>
#include <sstream>

template<class T>class Calculator{
private:
    T calculateStr(const std::string& str) const{
        for(size_t i = str.length(); i> 0; i--){
            if(str[i] == '+')
                return multiple(str.substr(i+1)) +  calculateStr(str.substr(0,i));
            else if(str[i] == '-')
                return calculateStr(str.substr(0,i)) - multiple(str.substr(i+1));
        }
        return multiple(str);
    }
    T multiple(const std::string& str) const{
        for(size_t i = str.length(); i> 0; i--){
            if(str[i] == '*') {
                std::string numberStr = str.substr(i+1);
                std::istringstream iss (numberStr);
                T value;
                iss >> value;
                assertRightTransformation(value, numberStr);
                return multiple(str.substr(0, i)) * value;
            }
            else if(str[i] == '/') {
                std::string numberStr = str.substr(i+1);
                std::istringstream iss (numberStr);
                T value;
                iss >> value;
                assertRightTransformation(value, numberStr);
                return dividion(str.substr(0, i), value);
            }
        }
        std::istringstream iss (str);
        T value;
        iss >> value;
        assertRightTransformation(value, str);
        return value;
    }
    T dividion(const std::string& delimoe, const T delitel) const{
        for(size_t i = delimoe.length(); i> 0; i--){
            if(delimoe[i] == '*') {
                std::string numberStr = delimoe.substr(i+1);
                std::istringstream iss (numberStr);
                T value;
                iss >> value;
                assertRightTransformation(value, numberStr);
                return multiple(delimoe.substr(0, i)) * value / delitel;
            } else if(delimoe[i] == '/') {
                std::string numberStr = delimoe.substr(i+1);
                std::istringstream iss (numberStr);
                T value;
                iss >> value;
                assertRightTransformation(value, numberStr);
                return multiple(delimoe.substr(0, i)) / value / delitel;
            }
        }

        return multiple(delimoe)/delitel;
    }
    std::string deleteAllSpaces(const std::string& str)const {
        std::string out = "";
        *str.begin();
        for(auto s: str)
            if(s != ' ' && s != '\t')
                out += s;
        return out;
    }
    std::string replaceAllDoubleMinuses(const std::string& str) const{
        std::string out = "";
        for(int i =0; i<str.length(); i++){
            if(i>0 && str[i] == '-' && str[i-1] == '-')
                out+='+';
            else if(i>0 && str[i] == '-' && str[i-1] == '+')
                out+='-';
            else if(!(i+1<str.length() && (str[i] == '-' && str[i+1] == '-') || str[i] == '+' && str[i+1] == '-' ))
                out+=str[i];
        }
        return out;
    }
    void assertRightTransformation(T t, const std::string& str) const{
        std::string s = std::to_string(t);
        if(s != str)
            throw std::runtime_error("FORMAT ERROR");
    }
    void checkDividedByZero(const std::string& str)const{
        for(int i =1; i< str.length(); i++){
            if(str[i-1] == '/' && str[i] == '0')
                throw std::runtime_error("DIVIDED BY ZERO");
        }
    }

public:
    T calculate(const std::string& str){
        std::string noSpaces = deleteAllSpaces(str);
        checkDividedByZero(noSpaces);
        return calculateStr(
                replaceAllDoubleMinuses(noSpaces)
        );
    }


};
int main(int argc, char* argv[]) {
    try {
        if (argc > 2)
            throw std::range_error("argc mast have 2 parameters!");
        Calculator<int> calculator;
        std::cout << calculator.calculate(argv[1]) << std::endl;
    }catch (const std::exception& e){
        std::cout<<"error"<<std::endl;
        return 1;
    }catch (...){
        std::cout<<"error";
        return 1;
    }
    return 0;
}