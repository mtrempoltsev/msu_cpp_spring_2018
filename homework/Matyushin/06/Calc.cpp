#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <vector>

typedef char** args_t;

class calcException{
public:
    int code;
    std::string msg;
    
    calcException(int errcode, std::string&& errmsg):
                                                code(errcode),
                                                msg(errmsg){
    }
};

class parseException{
public:
    int code;
    std::string msg;
    
    parseException(int errcode, std::string&& errmsg):
                                                code(errcode),
                                                msg(errmsg){
    }
};

void parse(int argc, args_t& argv, std::vector<std::string>& tokens){
    bool pmin = false;
    
    if (argc != 2)
        throw parseException(1, "error");
    
    std::string inputstr;
    
    int t = 0;
    while (argv[1][t] != 0){    
        if(!isspace(argv[1][t]))
            inputstr.append(1, argv[1][t]);
        
        t++;
    }
    
    int total = 0;
    for (int i = 0; i < inputstr.size(); i++){
        if ((inputstr[i] == '-') && ((i == 0) || (inputstr[i - 1] == '+') || (inputstr[i - 1] == '-') || (inputstr[i - 1] == '*') || (inputstr[i - 1] == '/')) && std::isdigit(inputstr[i + 1])){
            pmin = true;
            tokens.push_back(std::string(1, inputstr[i]));
            total++;
            continue;
        }
        
        if (std::isdigit(inputstr[i]) && (pmin || ((i > 0) && std::isdigit(inputstr[i - 1]))))
            tokens[total-1].append(1, inputstr[i]);
        
        else{
            tokens.push_back(std::string(1, inputstr[i]));
            total++;
        }
        
        pmin = false;    
    }
}

template<class T>
class Calc{
private:
    T expression(std::vector<std::string>& tokens, std::pair<int, int>&& bounds){
        for (int i = bounds.second - 1; i >= bounds.first; i--){
            if (tokens[i].compare("+") == 0){
                if ((i == bounds.first) || (i == bounds.second - 1))
                    throw calcException(1, "error");
                
                return expression(tokens, std::make_pair(std::move(bounds.first), i)) + expression(tokens, std::make_pair(i + 1, std::move(bounds.second)));
            }
            
            if (tokens[i].compare("-") == 0){
                if ((i == bounds.first) || (i == bounds.second - 1))
                    throw calcException(1, "error");
                
                return expression(tokens, std::make_pair(std::move(bounds.first), i)) - expression(tokens, std::make_pair(i + 1, std::move(bounds.second)));
            }
            
            if (i == bounds.first)
                return term(tokens, std::move(bounds));
        }

        return 0;
    }

    T term(std::vector<std::string>& tokens, std::pair<int, int>&& bounds){
        int divisor;
    
        for (int i = bounds.first; i < bounds.second; i++){
            if (tokens[i].compare("*") == 0){
                if ((i == bounds.first) || (i == bounds.second - 1))
                    throw calcException(1, "error");
                
                return term(tokens, std::make_pair(std::move(bounds.first), i))*term(tokens, std::make_pair(i + 1, std::move(bounds.second)));
            }
            
            if (tokens[i].compare("/") == 0){
                if ((i == bounds.first) || (i == bounds.second - 1))
                    throw calcException(1, "error");
                
                divisor = term(tokens, std::make_pair(i + 1, std::move(bounds.second)));
                
                if (divisor == 0)
                    throw calcException(1, "error");
                
                return term(tokens, std::make_pair(std::move(bounds.first), i))/divisor;
            }
            
            if (i == bounds.second - 1){
                return number(tokens, std::move(bounds));
            }
        }

        return 0;
    }

    T number(std::vector<std::string>& tokens, std::pair<int, int>&& bounds){
        if (bounds.second - bounds.first != 1)
            throw calcException(1, "error");
        
        if (!isNumber(tokens[bounds.first]))
            throw calcException(1, "error");
        
        return std::stoi(tokens[std::move(bounds.first)]);
    }

    bool isNumber(std::string& s){
        std::string::const_iterator iterator = s.begin();
        
        if (*iterator == '-')
            iterator++;
        
        while ((iterator != s.end()) && std::isdigit(*iterator))
            iterator++;
        
        return ((iterator == s.end()) && !s.empty());
    }

public:
    int proceed(std::vector<std::string>& tokens){
        int length = tokens.size();
        return expression(tokens, std::make_pair(0, length));
    }
};

int main(int argc, args_t argv){
    Calc<int> calculator;
    std::vector<std::string> tokens;
    
    try{
        parse(argc, argv, tokens);
        int result = calculator.proceed(tokens);
        std::cout << result;
    }
    catch(const parseException& e){
        std::cout << e.msg << std::endl;
        return e.code;
    }
    catch(const calcException& e){
        std::cout << e.msg << std::endl;
        return e.code;
    }
    
    return 0;
}
