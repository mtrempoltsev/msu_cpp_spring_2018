// Kononov Sergey BD-11

#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

class CalcError : std::exception {};


// Класс парсит и вычисляет арифметическое выражение в котором присутсвуют
// операторы +, -, *, /, унарный минус методом реккурентного спуска 
template <typename T>
class Calculator
{
private:

	using str_it = std::string::const_iterator;

	str_it find_last_plus_or_minus(str_it start, str_it stop) const
	{
		// Поиск положения последнего плюса или минуса в данной строке

		auto result = stop;
		// Инициализация позиции последнего плюса или минуса невалидным занчением

		bool previous_operator = true;
		// Наличие оператора в предыдущей позиции

		for (auto it = start; it != stop; it++)
		{
			if (*it == '+' || (*it == '-' && !previous_operator))
				result = it;

			if (*it == '-' || *it == '+' || *it == '/' || *it == '*')
				previous_operator = true;

			if (*it >= '0' && *it <= '9')
				previous_operator = false;
		}
		return result;
	}

	str_it find_last_mult_or_div(str_it start, str_it stop) const
	{
		// Поиск позиции последнего умножения или деления в текущей строке

		auto result = stop;
		// Инициализация позиции последнего умножения или деления невалидным занчением

		for (auto it = start; it != stop; it++)
		{
			if (*it == '*' || *it == '/')
				result = it;
		}

		return result;
	}

	str_it find_first_unary_minus(str_it start, str_it stop) const
	{
		// Поиск первого унарного минуса
		// Ищет первый минус, поскольку это подразумевает контекст использования
		// функции

		for (auto it = start; it != stop; it++) {
			if (*it == '-')
				return it;
		}
		return stop;
	}

	T calculate_part(str_it start,
					 str_it stop, 
					 bool check_zero = false) const
	{
		T result;

		// Поиск и рекурсивное вычисление слагаемых в выражении
		str_it it = find_last_plus_or_minus(start, stop);
		if (it != stop)
		{
			if (*it == '+')
				return calculate_part(start, it) + calculate_part(it + 1, stop);
			if (*it == '-')
				return calculate_part(start, it) - calculate_part(it + 1, stop);
		}

		// Поиск и рекурсивное вычисление множителей в выражении
		it = find_last_mult_or_div(start, stop);
		if (it != stop) {
			if (*it == '*')
				return calculate_part(start, it) * calculate_part(it + 1, stop);
			if (*it == '/')
				return calculate_part(start, it) / calculate_part(it + 1, stop, true);
		}

		// Поиск унарного минуса перед числом
		it = find_first_unary_minus(start, stop);
		if (it != stop) {
			return - calculate_part(it + 1, stop, check_zero);
		}

		// Парсинг числа, проверка на ноль для исключения деления на ноль
		std::stringstream ss(std::string(start, stop));

		// Перегруженный оператор >> преобразует строку в тип аргумента и записывает её туда
		if (ss >> result && (result != 0 || !check_zero))
			return result;

		// Инче ошибка в выражении
		throw CalcError();
	}

public:
		// Вычисление выражения
		T calculate(const std::string& s) const {
		return calculate_part(s.begin(), s.end());
	}

};

int main(int argc, char* argv[])
{	
	if (argc != 2) {
		std::cerr << "error\n";
		return 1;
	}
	
	Calculator <int> c;
	
	try
	{
		std::cout << c.calculate(argv[1]) << std::endl;
	}
	catch(CalcError& error) {
		std::cerr << "error\n";
		return 1;
	}

	return 0;
}
