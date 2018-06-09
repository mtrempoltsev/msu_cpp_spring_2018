#include <iostream>
#include <string>

template <typename T>
class Calculator {

private:
	std::string expression;
	int current_num_index = 0;
	T getNumber();
	T calcComp();
	T calcSum();

public:
	T calculate(const std::string &str);
};

template <class T>
T Calculator<T>::calculate(const std::string &expression) {
	for (int i = 0; i < expression.length; i++) {
		if (!(expression[i] == ' ' && expression[i] == '\t')) {
			this->expression.append(expression[i]);
		}
	}

	return calcSum();
}

template <class T>
T Calculator<T>::getNumber() {
	int tmp = 0;
	
	T ans = std::stoi(str.data() + current_num_index, &tmp);
	current_num_index = current_num_index + tmp;
	return ans;
}

template <class T>
T Calculator<T>::calcComp() {

	T value = getNumber();
	while (current_num_index < str.size() && (str[current_num_index] == '*' || str[current_num_index] == '/')) {

		if (str[current_num_index] == '*') {
			value = value * getNumber();
		}
		else if (str[current_num_index] == '/') {
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
	while (current_num_index < str.size() && (str[current_num_index] == '+' || str[current_num_index] == '-')) {

		if (str[current_num_index] == '+') {
			value = value + calcComp();
		}
		else if (str[current_num_index] == '-') {
			value = value - calcComp();
		}

		++current_num_index;
	}
	if (index < str.size()) {
		throw wrong_operation();
	}

	return value;
}
