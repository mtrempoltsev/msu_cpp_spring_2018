#include <iostream>
#include <string>
#include <exception>
template<class T>class Calculator{
private:
    T calculateStr(const std::string& str) const{
        for(size_t i = str.length(); i> 0; i--){
                if(str[i] == '+')
                return multiple(str.substr(i+1)) +  calculateStr(str.substr(0,i));
            else if(str[i] == '-' )
                return calculateStr(str.substr(0,i)) - multiple(str.substr(i+1));
        }
        return multiple(str);
    }
    T multiple(const std::string& str) const{
        for(size_t i = str.length(); i> 0; i--){
            if(str[i] == '*')
                return multiple(str.substr(0,i))*std::stoi(str.substr(i+1));
            else if(str[i] == '/')
                return dividion(str.substr(0,i),std::stoi(str.substr(i+1)));
        }
        return std::stoi(str);
    }
    T dividion(const std::string& delimoe, const T delitel) const{
        for(size_t i = delimoe.length(); i> 0; i--){
            if(delimoe[i] == '*')
                return multiple(delimoe.substr(0,i)) * std::stoi(delimoe.substr(i+1)) /delitel;
            else if(delimoe[i] == '/')
                return multiple(delimoe.substr(0,i)) / std::stoi(delimoe.substr(i+1)) /delitel;
        }

        return multiple(delimoe)/delitel;
    }
    std::string deleteAllSpaces(const std::string& str)const {
        std::string out = "";
        for(int s: str)
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
    }catch (std::exception e){
        std::cout<<"error"<<std::endl;
        return 1;
    }catch (...){
        std::cout<<"error";
        return 1;
    }
    return 0;
}