#include <algorithm>
#include <iostream>

class BigInt {
private:
	void allocate_to_len() {
		//if (cap < 1) new_cap = cap;
		size_t new_cap = cap;
		while (size_ >= new_cap) {
			new_cap *= 2;
		}
		resize(new_cap);
	}

public:
	size_t size_, cap;
	int* arr = nullptr;
	bool sign = true;
	BigInt();
	BigInt(const BigInt&);
	BigInt(int64_t);
	~BigInt();

	BigInt& operator=(const BigInt&);
	BigInt& operator=(int64_t number);
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
		int* newarr;
		newarr  = new int[cap];
		size_t tmp = size_;
		size_ = std::min(size_, cap);
		if (tmp != 0) {
			for (size_t i = 0; i < size_; i++) {
				newarr[i] = arr[i];
			}
		}
		delete[] arr;
		arr = newarr;
		
	}
	void push_back(int number) {
		arr[size_] = number;
		size_++;
		if (cap == size_)
			this->allocate_to_len();
	}
	void push_front(int number) {
		for (size_t i = size_; i > 0; i--)
			arr[i] = arr[i - 1];
		size_++;
		if (cap == size_)
			this->allocate_to_len();
		arr[0] = number;
	}
};

BigInt::BigInt() {
	size_ = 0;
	cap = 88;
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

BigInt::BigInt(int64_t number) {
	size_ = 0;
	cap = 88;
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
		push_back(number % 10);
		number /= 10;
	}
}

BigInt BigInt::operator-() {
	if(size_ == 1 && arr[0] ==0)
		return *this;

	sign = !sign;
	return *this;
}
BigInt& BigInt::operator=(int64_t number) {
	BigInt num(number);
	*this = num;
	return *this;
}
BigInt& BigInt::operator=(const BigInt& number) {
	if (this == &number)
		return *this;
	sign = number.sign;
	size_ = number.size_;
	arr = new int[size_];
	for (size_t i = 0; i < size_; i++) {
		arr[i] = number.arr[i];
	}
	return *this;
}

bool BigInt::operator==(const BigInt& number) const {
	if (size_ != number.size_ || sign != number.sign)
		return false;
	for (size_t i = 0; i < size_; i++) {
		if (arr[i] != number.arr[i])
			return false;
	}
	return true;
}

bool BigInt::operator!=(const BigInt& number) const {
	return !(operator==(number));
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
	//BigInt res(*this);
	BigInt num(number);

	result.sign = true;
	if ((size_ == 1 && arr[0] == 0) || (number.size_ == 1 && number.arr[0] == 0))
		return result;
	/*
	if (size_ < number.size_) {
		BigInt tmpd = num;
		num = res;
		res = tmpd;
	}*/

	for (size_t i = 0; i < num.size_; i++) {
		BigInt tmp;
		tmp.size_--;
		int carry = 0;
		for (size_t j = 0; j < i; j++)
			tmp.push_back(0);
		for (size_t j = 0; j < size_; j++) {
			int mult = num.arr[i] * arr[j] + carry;
			tmp.push_back(mult % 10);
			carry = mult / 10;
		}
		if (carry > 0)
			tmp.push_back(carry);
		result = result + tmp;
	}

	if (sign && !num.sign || !sign && num.sign) {
		result.sign = false;
	}
	while (result.size_ > 1 && result.arr[result.size_ - 1] == 0)
		result.size_--;

	return result;

}

BigInt BigInt::operator/(const BigInt& number) const
{
	BigInt result;
	BigInt buff;
	buff.size_--;
	BigInt num(number);
	BigInt res(*this);

	if(sign != number.sign)
		result.sign = false;
	//sign = true;
	if ((size_ == 1 && arr[0] == 0))
		return 0;
	res.sign = true;
	num.sign = true;
	if (res == num) {
		result = result + 1;
		if (sign != number.sign)
			result.sign = false;
		return result;
	}

	for (size_t i = 0; i < size_; i++) {
		buff.push_front(arr[size_ - 1 - i]);
		int carry = 0;
		while (buff.size_ > 1 && buff.arr[buff.size_ - 1] == 0)
			buff.size_--;
		int min = 0;
		int max = 10;

		while (min <= max) {
			int curr = (max + min) / 2;
			if (BigInt(curr) * num < buff) {
				carry = curr;
				min = curr + 1;
			}
			else
				max = curr - 1;
		}

		result.push_front(carry);
		BigInt tmp = BigInt(carry);
		buff = buff - num * tmp;
	}

	while (result.size_ > 1 && result.arr[result.size_ - 1] == 0)
		result.size_--;

	if (result.size_ == 1 && result.arr[0] == 0)
		result.sign = true;

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

BigInt::~BigInt() {
	delete[] arr;
}