#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <vector>

void parse(char* input, std::shared_ptr<std::vector<std::string>>& tokens){
    bool pmin = false;
    
    std::string inputstr;
    
    int t = 0;
    while (input[t] != 0){    
        if(!isspace(input[t]))
            inputstr.append(1, input[t]);
        
        t++;
    }
    
    int total = 0;
    for (int i = 0; i < inputstr.size(); i++){
        if ((inputstr[i]== '-') && ((i == 0) || (inputstr[i - 1] == '+') || (inputstr[i - 1] == '-') || (inputstr[i - 1] == '*') || (inputstr[i - 1] == '/')) && std::isdigit(inputstr[i + 1])){
            pmin = true;
            tokens.get()->push_back(std::string(1, inputstr[i]));
            total++;
            continue;
        }
        
        if (std::isdigit(inputstr[i]) && (pmin || ((i > 0) && std::isdigit(inputstr[i - 1]))))
            (tokens.get())->operator[](total-1).append(1, inputstr[i]);
        
        else{
            tokens.get()->push_back(std::string(1, inputstr[i]));
            total++;
        }
        
        pmin = false;    
    }
}

template<class T>
class Calc{
private:
    T expression(std::vector<std::string> *tokens, std::pair<int, int> bounds){
        for (int i = bounds.second - 1; i >= bounds.first; i--){
            if ((tokens->at(i)).compare("+") == 0){
                if ((i == bounds.first) || (i == bounds.second - 1)){
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                
                return expression(tokens, std::make_pair(bounds.first, i)) + expression(tokens, std::make_pair(i + 1, bounds.second));
            }
            
            if ((tokens->at(i)).compare("-") == 0){
                if ((i == bounds.first) || (i == bounds.second - 1)){
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                
                return expression(tokens, std::make_pair(bounds.first, i)) - expression(tokens, std::make_pair(i + 1, bounds.second));
            }
            
            if (i == bounds.first)
                return term(tokens, bounds);
        }

        return 0;
    }

    T term(std::vector<std::string> *tokens, std::pair<int, int> bounds){
        int trig;
    
        for (int i = bounds.first; i < bounds.second; i++){
            if ((tokens->at(i)).compare("*") == 0){
                if ((i == bounds.first) || (i == bounds.second - 1)){
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                
                return term(tokens, std::make_pair(bounds.first, i))*term(tokens, std::make_pair(i + 1, bounds.second));
            }
            
            if ((tokens->at(i)).compare("/") == 0){
                if ((i == bounds.first) || (i == bounds.second - 1)){
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                
                trig = term(tokens, std::make_pair(i + 1, bounds.second));
                
                if (trig == 0){
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                
                return term(tokens, std::make_pair(bounds.first, i))/trig;
            }
            
            if (i == bounds.second - 1){
                return number(tokens, std::make_pair(bounds.first, bounds.second));
            }
        }

        return 0;
    }

    T number(std::vector<std::string> *tokens, std::pair<int, int> bounds){
        if (bounds.second - bounds.first != 1){
            std::cout << "error" << std::endl;
            exit(1);
        }
        
        if (!isNumber(tokens->at(bounds.first))){
            std::cout << "error" << std::endl;
            exit(1);
        }
        
        return std::stoi(tokens->at(bounds.first));
    }

    bool isNumber(std::string s){
        std::string::const_iterator iterator = s.begin();
        
        if (*iterator == '-')
            iterator++;
        
        while ((iterator != s.end()) && std::isdigit(*iterator))
            iterator++;
        
        return ((iterator == s.end()) && !s.empty());
    }
public:
    int proceed(std::vector<std::string> *tokens){
        int length = tokens->size();
        return expression(tokens, std::make_pair(0, length));
    }
};

int main(int argc, char* argv[]){
    Calc<int> calculator;
    std::shared_ptr<std::vector<std::string>> tokens(new std::vector<std::string>());
    
    if(argc != 2){
        std::cout << "error" << std::endl;
        return 1;
    }

    parse(argv[1], tokens);
    
    int result = calculator.proceed(tokens.get());
    std::cout << result;
    
    return 0;
}
