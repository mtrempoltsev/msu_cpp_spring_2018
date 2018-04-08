#include <iostream>

bool is_digit(char c) {
	return (c >= '0') && (c <= '9');
}

void skip_spaces(char*& expr) {
	while (*expr == ' ') {
		expr++;
	}
}

// IF '(' THEN opened_brackets_cnt += 1
// ELSE IF ')' THEN opened_brackets_cnt -= 1
// ENDIF


int get_expr(char*& expr, int opened_brackets_cnt);

// [GET_PRIM]: parsing [+-]?(?:Pi|e|\d+)
// int get_prim(char*& expr);
int get_prim(char*& expr, int opened_brackets_cnt) {
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

		long prim = get_expr(expr, opened_brackets_cnt);

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

		throw std::runtime_error("unknown character \"" + s + "\"");
	}

	return is_negative ? -prim : prim;
}

// [GET_TERM]: parsing 'prim | term * prim | term / prim'
// int get_term(char*& expr);
int get_term(char*& expr, int opened_brackets_cnt) {
	int term_1 = get_prim(expr, opened_brackets_cnt);

	while (1) {
		skip_spaces(expr);

		char op = *expr;

		switch (op) {
		case '*': {
			expr++;

			term_1 *= get_prim(expr, opened_brackets_cnt);

			break;
		}
		case '/': {
			expr++;

			int term_2 = get_prim(expr, opened_brackets_cnt);

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

// [GET_EXPR]: parsing 'expr = term | expr + term | expr - term'
// int get_expr(char*& expr);
int get_expr(char*& expr, int opened_brackets_cnt) {
	int term_1 = get_term(expr, opened_brackets_cnt);

	while (1) {
		skip_spaces(expr);

		char op = *expr;

		switch (op) {
		case '+': {
			expr++;

			term_1 += get_term(expr, opened_brackets_cnt);

			break;
		}
		case '-': {
			skip_spaces(expr);

			expr++;

			term_1 -= get_term(expr, opened_brackets_cnt);

			break;
		}
		default:
			return term_1;
		}
	}
}

int eval(char* expr) {
	if (*expr == '\0') {
		throw std::invalid_argument("input expression is empty");
	}

	int opened_brackets_cnt = 0;

	int result = get_expr(expr, opened_brackets_cnt);

	if (opened_brackets_cnt != 0 || *expr == ')') {
		throw std::runtime_error("mismached brackets - an extra \")\"");
	}

	if (*expr != '\0') {
		throw std::runtime_error("invalid character \"" + std::to_string(*expr) + "\"");
	}

	return result;
}


int main(int argc, char** argv) {
	if (argc == 2) {
		try {
			int result = eval(argv[1]);

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
