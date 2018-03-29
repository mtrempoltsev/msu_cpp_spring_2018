#include <algorithm>
#include <iostream>

class BigInt {
private:
	void allocate_to_len() {
		//size_t new_cap = 1; // size-0 vectors wont loop infinitely
		//if (cap < 1) new_cap = cap;
		size_t new_cap = cap;
		while (size_ > new_cap) {
			new_cap *= 2;
		}
		resize(new_cap);
	}

public:
	size_t size_, cap;
	int* arr;
	bool sign = true;
	BigInt();
	BigInt(const BigInt&);
	BigInt(int);

	~BigInt();

	BigInt& operator=(const BigInt&);
	//BigInt& operator=(const int&);
		
	BigInt operator-();
	
	//BigInt operator+=(const BigInt&);
	BigInt operator+(const BigInt&) const;
	BigInt operator-(const BigInt&) const;
	BigInt operator*(const BigInt&) const;
	BigInt operator/(const BigInt&) const;
	
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;
	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;

	friend std::ostream& operator<<(std::ostream&, const BigInt&);

	void resize(size_t size) {
		cap = size;
		int* newarr = new int[size];
		size_t tmp = size_;
		size_ = std::min(size_, cap);
		if (tmp != 0) {
			for (size_t i = 0; i < size_; i++) {
				newarr[i] = arr[i];
			}
		}
		arr = newarr;
		delete[] newarr;
	}
	void push_back(int number) {
		arr[size_++] = number;
		if (cap == size_)
			this->allocate_to_len();
	}
};

BigInt::BigInt() {
	size_ = 0;
	cap = 16;
	arr = new int[cap];
	push_back(0);
}

BigInt::BigInt(const BigInt& number) {
	cap = number.cap;
	sign = number.sign;
	size_ = number.size_;
	arr = new int[cap];

	for (size_t i = 0; i < size_; i++) {
		arr[i] = number.arr[i];
	}
}

BigInt::BigInt(int number) {
	size_ = 0;
	cap = 16;
	arr = new int[cap];
	if (number == 0) {
		push_back(0);
		return;
	}
	if (number < 0) {
		sign = false;
		number *= -1;
	}
	for (size_t i = 0; number > 0; i++) {
		this->push_back(number % 10);
		number /= 10;
	}
}

BigInt::~BigInt() {
	delete[] arr;
}

BigInt BigInt::operator-() {
	if(size_ == 1 && arr[0] ==0)
		return *this;

	sign = !sign;
	return *this;
}

BigInt& BigInt::operator=(const BigInt& number) {
	if (this == &number)
		return *this;
	sign = number.sign;
	size_ = number.size_;
	for (size_t i = 0; i < size_; i++) {
		arr[i] = number.arr[i];
	}
	return *this;
}

bool BigInt::operator==(const BigInt& number) const {
	if (size_ != number.size_ || sign != number.sign)
		return false;
	for (size_t i = 0; i < size_; i++)
	{
		if (arr[i] != number.arr[i])
			return false;
	}
	return true;
}

bool BigInt::operator!=(const BigInt& number) const {
	return !this->operator==(number);
}

bool BigInt::operator<(const BigInt& number) const {
	if (this == &number)
		return false;
	if (sign != number.sign)
		return !sign;

	if (size_ > number.size_)
		return !sign;
	else if (size_ < number.size_)
		return sign;

	for (size_t i = size_ - 1; i != -1; i--)
	{
		if (arr[i] > number.arr[i])
			return !sign;
		else if (arr[i] < number.arr[i])
			return sign;
	}
	return true;
}

bool BigInt::operator>(const BigInt& number) const {
	if (this == &number)
		return false;

	if (sign != number.sign)
		return sign;

	if (size_ < number.size_)
		return !sign;
	else if (size_ > number.size_)
		return sign;

	for (size_t i = size_ - 1; i != -1; i--)
	{
		if (arr[i] < number.arr[i])
			return !sign;
		else if (arr[i] > number.arr[i])
			return sign;
	}
	return true;
}

bool BigInt::operator<=(const BigInt& number) const {
	return !this->operator>(number);
}

bool BigInt::operator>=(const BigInt& number) const {
	return !this->operator<(number);
}

BigInt BigInt::operator+(const BigInt& number) const {

	BigInt result(*this);
	if (result.sign != number.sign) {
		if (!result.sign) {
			result.sign = true;
			return number - result;
		}
		BigInt num(number);
		num.sign = true;
		return result - num;
	}

	if (result.sign == number.sign)
		if (!result.sign) {
			BigInt num(number);
			num.sign = true;
			result.sign = true;
			return -(result + num);
		}
	
	BigInt res;
	BigInt num(number);
	if (size_ > number.size_) {
		BigInt tmp = num;
		num = result;
		result = tmp;
	}
	int carry = 0;
	int sum = result.arr[0] + num.arr[0] + carry;
	res.arr[0] = (sum) % 10;
	carry = sum / 10;
	for (size_t i = 1; i< result.size_; i++)
	{
		int sum = result.arr[i] + num.arr[i] + carry;
		res.push_back(sum % 10);
		carry = sum / 10;
	}

	for (size_t i = result.size_; i < num.size_; i++)
	{
		int sum = num.arr[i] + carry;
		res.push_back(sum % 10);
		carry = sum / 10;
	}
	
	if (carry)
		res.push_back(carry);

	while (res.size_ > 1 && res.arr[res.size_ - 1] == 0)
		res.size_--;
	return res;

}

BigInt BigInt::operator-(const BigInt& number) const {
	BigInt num(*this);
	BigInt num2(number);
	if (!num.sign && !num2.sign) {
		num.sign = true;
		num2.sign = true;
		return num2 - num;
	}
	if (num.sign && !num2.sign) {
		num2.sign = true;
		return num + num2;
	}
	if (!num.sign && num2.sign) {
		num.sign = true;
		return -(num + num2);
	}
	if (num.size_ < num2.size_) {
		
		BigInt tmp = num2;
		num2 = num;
		num = tmp;
		num.sign = false;
	}

	else if (num.size_ == num2.size_) {
		for (size_t i = num.size_ - 1; i != -1; i--) {
			if (num.arr[i] > num2.arr[i])
				break;
			if (num.arr[i] < num2.arr[i]) {
				BigInt tmp = num2;
				num2 = num;
				num = tmp;
				num.sign = false;
				break;
			}
		}
	}

	int carry = 0;
	for (size_t i = 0; i < num2.size_; i++)
	{
		int difference = num.arr[i] - num2.arr[i] - carry;
		if (difference < 0)
		{
			num.arr[i] = difference + 10;
			carry = 1;
		}
		else
		{
			num.arr[i] = difference;
			carry = 0;
		}
	}
	for (size_t i = num2.size_; i < num.size_; i++)
	{
		int difference = num.arr[i] - carry;
		if (difference < 0)
		{
			num.arr[i] = difference + 10;
			carry = 1;
		}
		else
		{
			num.arr[i] = difference;
			carry = 0;
		}
	}
	while (num.size_ > 1 && num.arr[num.size_ - 1] == 0)
		num.size_--;

	if (num.size_ == 1 && num.arr[0] == 0)
		num.sign = true;
	return num;
}

BigInt BigInt::operator*(const BigInt& number) const {
	BigInt result;
	BigInt res(*this);
	BigInt num(number);

	result.sign = true;
	if ((size_ == 1 && arr[0] == 0) || (number.size_ == 1 && number.arr[0] == 0))
		return result;

	if (size_ < number.size_) {
		BigInt tmpd = num;
		num = res;
		res = tmpd;
	}

	for (size_t i = 0; i < num.size_; i++)
	{
		BigInt tmp;
		tmp.size_--;
		int carry = 0;
		for (size_t j = 0; j < i; j++)
			tmp.push_back(0);
		for (size_t j = 0; j < res.size_; j++)
		{
			int mult = num.arr[i] * res.arr[j] + carry;
			tmp.push_back(mult % 10);
			carry = mult / 10;
		}
		if (carry > 0)
			tmp.push_back(carry);
		result = result + tmp;
	}
	if (res.sign && !num.sign || !res.sign && num.sign) {
		result.sign = false;
	}
	while (result.size_ > 1 && result.arr[result.size_] == 0)
		result.size_--;

	return result;

}

BigInt BigInt::operator/(const BigInt& number) const {
	BigInt result;
	BigInt res(*this);
	BigInt num(number);
	
	res.sign = true;
	num.sign = true;

	if ((size_ == 1 && arr[0] == 0) || res <= num)
		return result;
	if (res == num) {
		if ((sign && !number.sign) || (!sign && number.sign))
			return -1;
		return 1;
	}
	while (res > num) {
		result = result + 1;
		res = res - num;
	}
	if (sign && !number.sign || !sign && number.sign) {
		result.sign = false;
	}
	while (result.size_ > 1 && result.arr[result.size_] == 0)
		result.size_--;

	return result;
}

std::ostream& operator<<(std::ostream& out, const BigInt& value)
{
	if (!value.sign)
		out << '-';
	for (size_t i = value.size_ - 1; i !=-1; i--)
		out << (value.arr[i]);
	return out;
}