#include <iostream>

class BigInt {
private:
	
	bool is_negative = false;
	size_t len = 64;
	char* number;
	size_t index = 0;
	
	char binSearch(const BigInt& first, const BigInt& second) const;
	void push_back(char a);
	void push_front(char a);
	char pop();
	void allocate();

public:
	BigInt();
	BigInt(const BigInt& number);
	BigInt(BigInt&& number);
	BigInt(int64_t value);
	~BigInt();
	BigInt& operator=(const BigInt& a);
	bool operator==(const BigInt& a) const;
	bool operator!=(const BigInt& a) const;
	bool operator<(const BigInt& a) const;
	bool operator>(const BigInt& a) const;
	bool operator<=(const BigInt& a) const;
	bool operator>=(const BigInt& a) const;
	BigInt operator-() const;
	BigInt abs() const;
	BigInt operator+(const BigInt& a) const;
	BigInt operator-(const BigInt& a) const;
	BigInt operator*(const BigInt& a) const;
	BigInt operator/(const BigInt& a) const;
	friend std::ostream& operator<<(std::ostream& out, const BigInt& number);
};

BigInt::BigInt() {
	number = new char[len];
	push_back(0);
}

BigInt::BigInt(int64_t a) {
	if (a < 0) {
		is_negative = true;
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
	is_negative = a.is_negative;
	len = a.len;

	number = new char[len];

	for (size_t i = 0; i < len; i++) {
		number[i] = a.number[i];
	}
}

BigInt::BigInt(BigInt&& a) {
	index = a.index;
	is_negative = a.is_negative;
	len = a.len;
	number = a.number;
	a.number = nullptr;
}

BigInt::~BigInt() {
	delete[] number;
}

BigInt& BigInt::operator=(const BigInt& a) {
	if (this == &a) {
		return *this;
	}

	index = a.index;
	len = a.len;
	is_negative = a.is_negative;

	delete[] number;
	number = new char[len];
	memcpy(number, a.number, index);
	return *this;
}

void BigInt::push_back(char a) {
	number[index] = a;
	++index;
	if (len == index) {
		allocate();
	}	
}

void BigInt::push_front(char a) {

	for (size_t i = index; i > 0; i--) {
		number[i] = number[i - 1];
	}

	++index;

	if (len == index) {
		allocate();
	}	
	number[0] = a;
}

char BigInt::pop() {
	return number[--index];
}

std::ostream& operator<<(std::ostream& out, const BigInt& a) {

	if (a.is_negative) {
		out << '-';
	}

	for (int i = a.index - 1; i != -1; i--) {
		out << static_cast<char>('0' + a.number[i]);
	}
	return out;
}

void BigInt::allocate() {
	len = len * 2;
	char* tmp = new char[len];
	
	for (size_t i = 0; i < len; i++) {
		tmp[i] = number[i];
	}

	delete[] number;
	number = tmp;
}

BigInt BigInt::abs() const {
	BigInt ans(*this);
	ans.is_negative = false;

	return ans;
}

BigInt BigInt::operator-() const {
	BigInt ans(*this);
	ans.is_negative = !(is_negative);

	return ans;
}

bool BigInt::operator==(const BigInt& a) const {
	if (index != a.index || is_negative != a.is_negative) {
		return false;
	}

	for (size_t i = 0; i < index; i++) {
		if (number[i] != a.number[i]) {
			return false;
		}
	}

	return true;
}

bool BigInt::operator>(const BigInt& a) const {

	if (index > a.index && is_negative == false && a.is_negative == false) {
		return true;
	}
	else if (index < a.index && is_negative == false && a.is_negative == false) {
		return false;
	}
	else if (index == a.index && is_negative == false && a.is_negative == false) {
		for (size_t i = index - 1; i >= 0; i--) {
			if (number[i] > a.number[i]) {
				return true;
			} 
			else if (number[i] < a.number[i]) {
				return false;
			}
		}
		return false;
	}
	else if (index == a.index && is_negative && a.is_negative) {
		for (size_t i = index - 1; i >= 0; i--) {
			if (number[i] > a.number[i]) {
				return false;
			}
			else if (number[i] < a.number[i]) {
				return true;
			}
		}
		return true;
	}
	else if (is_negative == true && a.is_negative == false) {
		return false;
	}
	else if (is_negative == false && a.is_negative == true) {
		return true;
	} 

	return true;
}

bool BigInt::operator<(const BigInt& a) const {

	if (index > a.index && is_negative == false && a.is_negative == false) {
		return false;
	}
	else if (index < a.index && is_negative == false && a.is_negative == false) {
		return true;
	}
	else if (index == a.index && is_negative == false && a.is_negative == false) {
		for (size_t i = index - 1; i >= 0; i--) {
			if (number[i] > a.number[i]) {
				return false;
			}
			else if (number[i] < a.number[i]) {
				return true;
			}
		}
		return true;
	}
	else if (index == a.index && is_negative && a.is_negative) {
		for (size_t i = index - 1; i >= 0; i--) {
			if (number[i] > a.number[i]) {
				return true;
			}
			else if (number[i] < a.number[i]) {
				return false;
			}
		}
		return false;
	}
	else if (is_negative == true && a.is_negative == false) {
		return true;
	}
	else if (is_negative == false && a.is_negative == true) {
		return false;
	}

	return true;
}

bool BigInt::operator<=(const BigInt& a) const {
	return !this->operator>(a);
}

bool BigInt::operator>=(const BigInt& a) const {
	return !this->operator<(a);
}

bool BigInt::operator!=(const BigInt& a) const {
	return !this->operator==(a);
}

BigInt BigInt::operator+(const BigInt& a) const {
	BigInt ans(*this);
	char tmp = 0;

	if (a.is_negative && is_negative == false) {
		return (*this) - a.abs();
	}
	else if (a.is_negative == false && is_negative) {
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
		ans.is_negative = false;
	}

	//std::cout << ans;

	return ans;
}

BigInt BigInt::operator-(const BigInt& a) const {

	if (is_negative != a.is_negative) {
		if (is_negative) {
			return -(abs() + a);
		}
		else {
			return *this + a.abs();
		}
	}

	if (is_negative) {
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
		ans.is_negative = false;
	}

	return ans;
}

BigInt BigInt::operator*(const BigInt& a) const {

	BigInt ans;

	if ((number[0] == 0 && len == 1) || (a.number[0] == 0 && len ==1)) {
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

	ans.is_negative = is_negative != a.is_negative;
	for (size_t i = ans.index - 1; i > 0; i--) {
		if (ans.number[i] > 0) {
			break;
		}
		ans.index--;
	}

	if (ans.index == 1 && ans.number[0] == 0) {
		ans.is_negative = false;
	}

	return ans;
}

char BigInt::binSearch(const BigInt &first, const BigInt &second) const {
	// result = max(x : divisor * x <= dividend)
	char ans = 0, min = 0, max = 10;

	while (min <= max) {
		char curr = (max + min) / 2;
		if (BigInt(curr) * second <= first) {
			ans = curr;
			min = curr + 1;
		}
		else {
			max = curr - 1;
		}
	}

	return ans;
}

BigInt BigInt::operator/(const BigInt& a) const {

	BigInt ans;
	BigInt tmp;
	tmp.pop();
	BigInt abs_number = a.abs();

	for (size_t i = 0; i < index; i++) {
		tmp.push_front(number[index - 1 - i]);

		for (size_t i = tmp.index - 1; i > 0; i--) {
			if (tmp.number[i] > 0) {
				break;
			}
			tmp.index--;
		}

		char div = binSearch(tmp, abs_number);
		ans.push_front(div);
		tmp = tmp - abs_number * BigInt(div);
	}

	for (size_t i = ans.index - 1; i > 0; i--) {
		if (ans.number[i] > 0) {
			break;
		}
		ans.index--;
	}

	ans.is_negative = is_negative != a.is_negative;

	if (ans.index == 1 && ans.number[0] == 0) {
		ans.is_negative = false;
	}
	
	return ans;
}