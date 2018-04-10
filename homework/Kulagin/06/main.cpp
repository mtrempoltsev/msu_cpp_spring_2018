#include <iostream>

template <class T>
class Calculator {

public:
	Calculator() {}

	T eval(char* expr) {
		if (*expr == '\0') {
			throw std::invalid_argument("input expression is empty");
		}

		int opened_brackets_cnt = 0;

		int result = get_expr(expr);

		if (opened_brackets_cnt != 0 || *expr == ')') {
			throw std::runtime_error("mismached brackets - an extra \")\"");
		}

		if (*expr != '\0') {
			throw std::runtime_error("unexpected character \"" + std::to_string(*expr) + "\"");
		}

		return result;
	}

	~Calculator() {}

private:
	int opened_brackets_cnt;

	bool is_digit(char c) {
		return (c >= '0') && (c <= '9');
	}

	void skip_spaces(char*& expr) {
		while (*expr == ' ') {
			expr++;
		}
	}

	// [GET_EXPR]: parsing 'expr = term | expr + term | expr - term'
	T get_expr(char*& expr) {
		int term_1 = get_term(expr);

		while (1) {
			skip_spaces(expr);

			char op = *expr;

			switch (op) {
			case '+': {
				expr++;

				term_1 += get_term(expr);

				break;
			}
			case '-': {
				skip_spaces(expr);

				expr++;

				term_1 -= get_term(expr);

				break;
			}
			default:
				return term_1;
			}
		}
	}

	// [GET_PRIM]: parsing [+-]\d+
	T get_prim(char*& expr);

	// [GET_TERM]: parsing 'prim | term * prim | term / prim'
	T get_term(char*& expr) {
		int term_1 = get_prim(expr);

		while (1) {
			skip_spaces(expr);

			char op = *expr;

			switch (op) {
			case '*': {
				expr++;

				term_1 *= get_prim(expr);

				break;
			}
			case '/': {
				expr++;

				int term_2 = get_prim(expr);

				if (term_2 == 0) {
					throw std::logic_error("division by zero in \"" + std::to_string(term_1) + " / " + std::to_string(term_2) + "\"");
				}

				term_1 /= term_2;

				break;
			}
			default:
				return term_1;
			}
		}
	}
};


template <>
int Calculator<int>::get_prim(char*& expr) {
	skip_spaces(expr);

	bool is_negative = false;

	switch (*expr) {
	case '+': {
		expr++;

		break;
	}
	case '-': {
		is_negative = true;

		expr++;
		skip_spaces(expr);

		break;
	}
	default:
		break;
	}

	if (*expr == '(') {
		expr++;

		opened_brackets_cnt++;

		long prim = get_expr(expr);

		if (*expr != ')') {
			throw std::runtime_error("mismached brackets - an extra \"(\"");
		}

		expr++;

		opened_brackets_cnt--;

		return is_negative ? -prim : prim;
	}

	long prim = 0;

	if (is_digit(*expr)) {
		do {
			prim = 10 * prim + (*expr - '0');

			expr++;
		} while (is_digit(*expr));
	} else {
		std::string s;

		s += *expr;

		throw std::runtime_error("unexpected character \"" + s + "\"");
	}

	return is_negative ? -prim : prim;
}


int main(int argc, char** argv) {
	if (argc == 2) {
		Calculator<int> calc;
		try {
			int result = calc.eval(argv[1]);

			std::cout << result << std::endl;
		} catch (std::exception& err) {
			std::cout << "error" << std::endl;

			return 1;
		}
	} else {
		std::cout << "error" << std::endl;

		return 1;
	}

	return 0;
}
