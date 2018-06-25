#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <sstream>

class division_by_zero : public std::exception {};
class wrong_operation : public std::exception {};

template <typename T>
class Calculator {

private:
	std::string expression = "";
	int current_num_index = 0;
	T getNumber();
	T calcComp();
	T calcSum();

public:
	T calculate(const std::string &expression);
};

template <class T>
T Calculator<T>::calculate(const std::string &expression_) {
	for (int i = 0; i < expression_.length(); i++) {
		if (expression_[i] != ' ' && expression_[i] != '\t') {
			expression = expression + expression_[i];
		}
	}

	current_num_index = 0;

	return calcSum();
}

template <class T>
T Calculator<T>::getNumber() {
	size_t tmp = 0;
	T ans;
	std::stringstream s;
	int flag = 0, i = 0;
	bool negative = false;
	std::string str = expression.data() + current_num_index;

	if (str[0] == '-') {
		negative = true;
		str = str.substr(1);
	}

	for (i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			if (str[i] == '.' && flag++ == 0) {
				continue;
			}
			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
				break;
			}
			else {
				throw std::runtime_error("");
			}
		}
	}

	if (i == 0) {
		throw std::runtime_error("");
	}

	s << str.substr(0, i);
	s >> ans;

	if (negative) {
		++i;
		ans = (-1) * ans;
	}
	
	current_num_index = current_num_index + i;

	return ans;
}

template <class T>
T Calculator<T>::calcComp() {
	//std::cout << expression[current_num_index];
	T value = getNumber();

	while (current_num_index < expression.length() && (expression[current_num_index] == '*' || expression[current_num_index] == '/')) {

		if (expression[current_num_index] == '*') {
			++current_num_index;
			value = value * getNumber();
		}
		else if (expression[current_num_index] == '/') {
			++current_num_index;
			T number = getNumber();
			if (number == T(0)) {
				throw division_by_zero();
			}
			value = value / number;
		}
	}

	return value;
}

template <class T>
T Calculator<T>::calcSum() {

	T value = calcComp();

	while (current_num_index < expression.length() && (expression[current_num_index] == '+' || expression[current_num_index] == '-')) {
		
		if (expression[current_num_index] == '+') {
			++current_num_index;
			value = value + calcComp();
		}
		else if (expression[current_num_index] == '-') {
			++current_num_index;
			value = value - calcComp();
		}
	}

	if (current_num_index < expression.length()) {
		throw wrong_operation();
	}

	return value;
}
