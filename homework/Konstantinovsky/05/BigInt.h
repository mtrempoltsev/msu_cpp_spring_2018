#include <iostream>

class BigInt
{
private:
	char *number;
	bool minus = false;
	size_t index = 0;
	size_t len = 64;

	void push_back(char element);
	void push_front(char element);
	char pop();
	void mem();
public:
	BigInt();
	BigInt(const BigInt& a);
	BigInt(int64_t a);
	~BigInt();

	BigInt operator-() const;
	BigInt abs() const;

	BigInt& operator=(const BigInt& a);

	BigInt operator+(const BigInt& a) const;
	BigInt operator-(const BigInt& a) const;
	BigInt operator*(const BigInt& a) const;
	BigInt operator/(const BigInt& a) const;

	bool operator==(const BigInt& a) const;
	bool operator!=(const BigInt& a) const;
	bool operator<(const BigInt& a) const;
	bool operator>(const BigInt& a) const;
	bool operator<=(const BigInt& a) const;
	bool operator>=(const BigInt& a) const;
	
	friend std::ostream& operator<<(std::ostream& out, const BigInt& a);
};

BigInt::BigInt() {
	number = new char[len];
	push_back(0);
}

BigInt::BigInt(int64_t a) {
	if (a < 0) {
		minus = true;
		a = a * -1;
	}

	number = new char[len];

	if (a == 0) {
		push_back(0);
		return;
	}

	for (size_t i = 0; a > 0; i++) {
		push_back(a % 10);
		a = (a - a % 10) / 10;
	}
}

BigInt::BigInt(const BigInt& a) {
	index = a.index;
	minus = a.minus;
	len = a.len;

	number = new char[len];

	for (size_t i = 0; i < len; i++) {
		number[i] = a.number[i];
	}
}

void BigInt::push_back(char a) {
	number[index] = a;
	++index;
	if (len == index) {
		mem();
	}
}

char BigInt::pop() {
	return number[--index];
}

void BigInt::push_front(char a) {

	for (size_t i = index; i > 0; i--) {
		number[i] = number[i - 1];
	}

	++index;

	if (len == index) {
		mem();
	}
	number[0] = a;
}

void BigInt::mem() {
	len = len * 2;
	char* tmp = new char[len];

	for (size_t i = 0; i < len; i++) {
		tmp[i] = number[i];
	}

	delete[] number;
	number = tmp;
}

BigInt& BigInt::operator=(const BigInt& a) {
	if (this == &a) {
		return *this;
	}

	index = a.index;
	len = a.len;
	minus = a.minus;

	delete[] number;
	number = new char[len];
	memcpy(number, a.number, index);
	return *this;
}

BigInt::~BigInt() {
	delete[] number;
}

std::ostream& operator<<(std::ostream& out, const BigInt& a) {

	if (a.minus) {
		out << '-';
	}

	for (int i = a.index - 1; i != -1; i--) {
		out << char('0' + a.number[i]);
	}
	return out;
}

bool BigInt::operator==(const BigInt& a) const {
	if (index != a.index || minus != a.minus) {
		return false;
	}

	for (size_t i = 0; i < index; i++) {
		if (number[i] != a.number[i]) {
			return false;
		}
	}

	return true;
}

bool BigInt::operator!=(const BigInt& a) const {
	return !operator==(a);
}

bool BigInt::operator<(const BigInt& a) const {
	if (minus != a.minus) {
		return minus;
	}
		
	if (index > a.index) {
		return minus;
	}
	else if (index < a.index) {
		return !minus;
	}
	else {
		for (int i = index - 1; i != -1; i--) {
			if (number[i] > a.number[i]) {
				return minus;
			}
			else if (number[i] < a.number[i]) {
				return !minus;
			}
		}
		return false;
	}
}

bool BigInt::operator>(const BigInt& a) const {
	if (minus != a.minus) {
		return !minus;
	}
		
	if (index < a.index) {
		return minus;
	}
	else if (index > a.index) {
		return !minus;
	}
	else {
		for (int i = index - 1; i != -1; i--) {
			if (number[i] < a.number[i]) {
				return minus;
			}
			else if (number[i] > a.number[i])
				return !minus;
		}
		return false;
	}
}

bool BigInt::operator<=(const BigInt& a) const {
	return !operator>(a);
}

bool BigInt::operator>=(const BigInt& a) const {
	return !operator<(a);
}

BigInt BigInt::operator-() const {
	BigInt ans(*this);

	if (index == 1 && number[0] == 0) {
		return ans;
	}

	ans.minus = !(minus);

	return ans;
}

BigInt BigInt::abs() const {
	BigInt ans(*this);
	ans.minus = false;

	return ans;
}

BigInt BigInt::operator+(const BigInt& a) const {
	BigInt ans(*this);
	char tmp = 0;

	if (a.minus && minus == false) {
		return (*this) - a.abs();
	}
	else if (a.minus == false && minus) {
		return a.abs() - (*this).abs();
	}

	if (a.index == ans.index) {
		for (size_t i = 0; i < a.index; i++) {
			char sum = ans.number[i] + a.number[i] + tmp;
			ans.number[i] = sum % 10;
			tmp = (sum - sum % 10) / 10;
		}
		if (tmp != 0) {
			ans.push_back(tmp);
		}
	}
	else if (a.index > ans.index) {
		for (size_t i = ans.index; i < a.index; i++) {
			ans.push_back(0);
		}

		for (size_t i = 0; i < a.index; i++) {
			char sum = ans.number[i] + a.number[i] + tmp;
			ans.number[i] = sum % 10;
			tmp = (sum - sum % 10) / 10;
		}
		if (tmp != 0) {
			ans.push_back(tmp);
		}
	}
	else if (a.index < ans.index) {
		for (size_t i = 0; i < a.index; i++) {
			char sum = ans.number[i] + a.number[i] + tmp;
			ans.number[i] = sum % 10;
			tmp = (sum - sum % 10) / 10;
		}
		for (size_t i = a.index; i < ans.index; i++) {
			char sum = ans.number[i] + tmp;
			ans.number[i] = sum % 10;
			tmp = sum / 10;
		}
		if (tmp != 0) {
			ans.push_back(tmp);
		}
	}

	for (size_t i = ans.index - 1; i > 0; i--) {
		if (ans.number[i] > 0) {
			break;
		}
		ans.index--;
	}

	if (ans.index == 1 && ans.number[0] == 0) {
		ans.minus = false;
	}

	//std::cout << ans;

	return ans;
}

BigInt BigInt::operator-(const BigInt& a) const {

	if (minus != a.minus) {
		if (minus) {
			return -(abs() + a);
		}
		else {
			return *this + a.abs();
		}
	}

	if (minus) {
		return a.abs() + *this;
	}
	if (*this < a) {
		return -(a - *this);
	}

	BigInt ans(*this);
	char tmp = 0;

	for (size_t i = 0; i < a.index; i++) {
		char diff = ans.number[i] - a.number[i] - tmp;

		if (diff < 0) {
			ans.number[i] = diff + 10;
			tmp = 1;
		}
		else {
			ans.number[i] = diff;
			tmp = 0;
		}
	}

	for (size_t i = a.index; i < ans.index; i++) {
		char diff = ans.number[i] - tmp;
		if (diff < 0) {
			ans.number[i] = diff + 10;
			tmp = 1;
		}
		else {
			ans.number[i] = diff;
			tmp = 0;
		}
	}

	for (size_t i = ans.index - 1; i > 0; i--) {
		if (ans.number[i] > 0) {
			break;
		}
		ans.index--;
	}

	if (ans.index == 1 && ans.number[0] == 0) {
		ans.minus = false;
	}

	return ans;
}

BigInt BigInt::operator*(const BigInt& a) const {

	BigInt ans;

	if ((number[0] == 0 && len == 1) || (a.number[0] == 0 && len == 1)) {
		return ans;
	}

	for (size_t i = 0; i < a.index; i++) {

		BigInt tmp;
		tmp.pop();
		char to_next = 0;

		for (size_t j = 0; j < i; j++) {
			tmp.push_back(0);
		}

		for (size_t j = 0; j < index; j++) {
			char mult = a.number[i] * number[j] + to_next;
			tmp.push_back(mult % 10);
			to_next = (mult - (mult % 10)) / 10;
		}

		if (to_next > 0) {
			tmp.push_back(to_next);
		}
		ans = ans + tmp;
	}

	ans.minus = minus != a.minus;
	for (size_t i = ans.index - 1; i > 0; i--) {
		if (ans.number[i] > 0) {
			break;
		}
		ans.index--;
	}

	if (ans.index == 1 && ans.number[0] == 0) {
		ans.minus = false;
	}

	return ans;
}

BigInt BigInt::operator/(const BigInt& a) const {

	char div = 0, min = 0, max = 10;
	BigInt ans;
	BigInt tmp;
	tmp.pop();
	BigInt abs_number = a.abs();
	
	for (size_t i = 0; i < index; i++) {
		tmp.push_front(number[index-1-i]);

		for (size_t i = tmp.index - 1; i > 0; i--) {
			if (tmp.number[i] > 0) {
				break;
			}
			tmp.index--;
		}

		min = 0;
		max = 10;
		while (min <= max) {
			char c = (max + min) / 2;
			if (BigInt(c) * abs_number <= tmp) {
				div = c;
				min = c + 1;
			}
			else {
				max = c - 1;
			}
		}
		
		ans.push_front(div);
		tmp = tmp - abs_number * BigInt(div);
	}

	for (size_t i = ans.index - 1; i > 0; i--) {
		if (ans.number[i] > 0) {
			break;
		}
		ans.index--;
	}

	ans.minus = minus != a.minus;

	if (ans.index == 1 && ans.number[0] == 0) {
		ans.minus = false;
	}

	return ans;
}
