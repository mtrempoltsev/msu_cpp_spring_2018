#include <iostream>
#include <string>
#include <cstring>

template<class Type>
struct Calc{

	Type expr(char* tokens[], int startToken, int endToken) {
		for(int i = startToken; i < endToken; i++) {
		//std::cout << "cicle expr" << std::endl;
			if(strcmp(tokens[i], "+") == 0) {
			//std::cout << "cicle expr +" << std::endl;
				if(i == startToken || i == endToken - 1) {
					std::cout << "Incorrect input" << std::endl;
					exit(1);
				}
				return expr(tokens, startToken, i) + expr(tokens, i + 1, endToken);
			}
			if(strcmp(tokens[i], "-") == 0) {
			//std::cout <<"cicle expr -" << std::endl;
				if(i == startToken || i == endToken - 1) {
					std::cout << "Incorrect input" << std::endl;
					exit(1);
				}
				return expr(tokens, startToken, i) - expr(tokens, i + 1, endToken);
			}
			if(i == endToken - 1) {
			//std::cout << "cicle expr 0" << std::endl;
				return term(tokens, startToken, endToken);
			}
		}

		return 0;
	}

	Type term(char* tokens[], int startToken, int endToken) {
		int checkZero;
	
		for(int i = startToken; i < endToken; i++) {
		//std::cout << "cicle term" << std::endl;
			if(strcmp(tokens[i], "*") == 0) {
			//std::cout << "cicle term *" << std::endl;
				if(i == startToken || i == endToken - 1) {
					std::cout << "Incorrect input" << std::endl;
					exit(1);
				}
				return term(tokens, startToken, i) * term(tokens, i + 1, endToken);
			}
			if(strcmp(tokens[i], "/") == 0) {
			//std::cout << "cicle term /" << std::endl;
				if(i == startToken || i == endToken - 1) {
					std::cout << "Incorrect input" << std::endl;
					exit(1);
				}
				checkZero = term(tokens, i + 1, endToken);
				if(checkZero == 0){
					std::cout << "Error: Divide by 0" << std::endl;
					exit(1);
				}
				return term(tokens, startToken, i) / term(tokens, i + 1, endToken);
			}
			if(i == endToken - 1) {
			//std::cout << "cicle term 0" << std::endl;
				return number(tokens, startToken, endToken);
			}
		}

		return 0;
	}

	Type number(char* tokens[], int startToken, int endToken) {
		if(endToken - startToken != 1) {
			std::cout << "Incorrect input" << std::endl;
			exit(1);
		}
	//std::cout << "number" << std::endl;
		if(!isNumber(tokens[startToken])){
			std::cout << "Incorrect input" << std::endl;
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



