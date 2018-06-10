#include <iostream>
#include <string>
#include <stdexcept>

class division_by_zero : public std::exception {};
class wrong_operation : public std::exception {};

template <typename T>
class Calculator {

private:
	std::string expression;
	int current_num_index = 0;
	T getNumber();
	T calcComp();
	T calcSum();

public:
	T calculate(const std::string &expression);
};

template <class T>
T Calculator<T>::calculate(const std::string &expression) {
	for (int i = 0; i < expression.length(); i++) {
		if (!(expression[i] == ' ' && expression[i] == '\t')) {
			this->expression.append(expression[i]);
		}
	}

	return calcSum();
}

template <class T>
T Calculator<T>::getNumber() {
	int tmp = 0;
	
	T ans = std::stoi(expression.data() + current_num_index, &tmp);
	current_num_index = current_num_index + tmp;
	return ans;
}

template <class T>
T Calculator<T>::calcComp() {

	T value = getNumber();
	while (current_num_index < expression.lenght() && (expression[current_num_index] == '*' || expression[current_num_index] == '/')) {

		if (expression[current_num_index] == '*') {
			value = value * getNumber();
		}
		else if (expression[current_num_index] == '/') {
			T number = getNumber();
			if (number == T(0)) {
				throw division_by_zero();
			}
			value = value / number;
		}

		++current_num_index;
	}

	return value;
}

template <class T>
T Calculator<T>::calcSum() {

	T value = calcComp();
	while (current_num_index < expression.lenght() && (expression[current_num_index] == '+' || expression[current_num_index] == '-')) {

		if (expression[current_num_index] == '+') {
			value = value + calcComp();
		}
		else if (expression[current_num_index] == '-') {
			value = value - calcComp();
		}

		++current_num_index;
	}
	if (index < expression.size()) {
		throw wrong_operation();
	}

	return value;
}
