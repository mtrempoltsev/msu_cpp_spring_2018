#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <vector>

template<class Type>
struct Calc{

    Type expr(std::vector<std::string> tokens, int startToken, int endToken) {
        for(int i = endToken - 1; i >= startToken; i--) {
            if(tokens[i].compare("+") == 0) {
                if(i == startToken || i == endToken - 1) {
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                return expr(tokens, startToken, i) + expr(tokens, i + 1, endToken);
            }
            if(tokens[i].compare("-") == 0) {
                if(i == startToken || i == endToken - 1) {
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                return expr(tokens, startToken, i) - expr(tokens, i + 1, endToken);
            }
            if(i == startToken) {
                return term(tokens, startToken, endToken);
            }
        }

        return 0;
    }

    Type term(std::vector<std::string> tokens, int startToken, int endToken) {
        int checkZero;
    
        for(int i = startToken; i < endToken; i++) {
            if(tokens[i].compare("*") == 0) {
                if(i == startToken || i == endToken - 1) {
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                return term(tokens, startToken, i) * term(tokens, i + 1, endToken);
            }
            if(tokens[i].compare("/") == 0) {
                if(i == startToken || i == endToken - 1) {
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                checkZero = term(tokens, i + 1, endToken);
                if(checkZero == 0){
                    std::cout << "error" << std::endl;
                    exit(1);
                }
                return term(tokens, startToken, i) / checkZero;
            }
            if(i == endToken - 1) {
                return number(tokens, startToken, endToken);
            }
        }

        return 0;
    }

    Type number(std::vector<std::string> tokens, int startToken, int endToken) {
        if(endToken - startToken != 1) {
            std::cout << "error" << std::endl;
            exit(1);
        }
        if(!isNumber(tokens[startToken])){
            std::cout << "error" << std::endl;
            exit(1);
        }
        return std::stoi(tokens[startToken]);
    }

    bool isNumber(std::string s){
        std::string::const_iterator it = s.begin();
        if(*it == '-') ++it;
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

};

void parseInput(char* argv, std::shared_ptr<std::vector<std::string>>& tokens){
    bool prev_minus = false;
    int n = 0;
    std::string input;
    int j = 0;
    while (argv[j] != '\0'){    
        if(!isspace(argv[j])){
            input.append(1, argv[j]);
        }
        j++;
    }
    
    for (int i = 0; i < input.size(); i++){
        if((i == 0 || input[i-1] == '/' || input[i-1] == '*' || input[i-1] == '-' || input[i-1] == '+') && input[i]== '-' && std::isdigit(input[i+1])){                
            prev_minus = true;
            tokens.get()->push_back(std::string(1, input[i]));
            n++;
            continue;
        }
        if((prev_minus || (i > 0 && std::isdigit(input[i-1])) ) && std::isdigit(input[i]) ){
            (*(tokens.get()))[n-1].append(1, input[i]);
        } else{
            tokens.get()->push_back(std::string(1, input[i]));
            n++;
        }
        prev_minus = false;    
    }
}

int main(int argc, char* argv[])
{
    Calc<int> calc;
    std::shared_ptr<std::vector<std::string>> tokens(new std::vector<std::string>());
    if(argc != 2){
        std::cout << "error" << std::endl;
        exit(1);
    }

    parseInput(argv[1], tokens);
    int size = (*(tokens.get())).size();
    int result = calc.expr(*(tokens.get()), 0, size);
    std::cout << result;
    return 0;
}


