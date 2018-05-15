#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <vector>

void parse(char* argv, std::shared_ptr<std::vector<std::string>>& tokens){
    bool pmin = false;
    
    std::string input;
    
    int t = 0;
    while (argv[t] != 0){    
        if(!isspace(argv[t]))
            input.append(1, argv[t]);
        
        t++;
    }
    
    int total = 0;
    for (int i = 0; i < input.size(); i++){
        if ((input[i]== '-') && ((i == 0) || (input[i - 1] == '+') || (input[i - 1] == '-') || (input[i - 1] == '*') || (input[i - 1] == '/')) && std::isdigit(input[i + 1])){ //unary minus
            pmin = true;
            tokens.get()->push_back(std::string(1, input[i]));
            total++;
            continue;
        }
        
        if (std::isdigit(input[i]) && (pmin || ((i > 0) && std::isdigit(input[i - 1]))))
            (tokens.get())->operator[](total-1).append(1, input[i]);
        
        else{
            tokens.get()->push_back(std::string(1, input[i]));
            total++;
        }
        
        pmin = false;    
    }
}

template<class T>
class Calc{
private:
    T expression(std::vector<std::string> *tokens, std::pair<int, int> bounds){//, int sToken, int eToken){
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

    T term(std::vector<std::string> *tokens, std::pair<int, int> bounds){//, int sToken, int eToken) {
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

    T number(std::vector<std::string> *tokens, std::pair<int, int> bounds){//int sToken, int eToken) {
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
