#include <iostream>
#include <cstring>
#include <cmath>

inline int get_sign(long long int a) {
    if (a < 0)
    	return -1;
    else if (a > 0)
    	return 1;
    return 0;
}

class BigInt
{
	size_t capacity;
	size_t real_len;
	char* buf;
	int sign;
public:

	BigInt(long long int a = 0):
		capacity(1),
		real_len(0)
	{
		buf = new char [capacity];
		std::memset(buf, 0, capacity * sizeof(char));
		sign = get_sign(a);
		a = std::abs(a);
		while (a) {
			setValue(a % 10, real_len);
			real_len++;
			a /= 10;
		}
		countRealLen();
	}

	BigInt(const BigInt &a):
		capacity(a.capacity),
		real_len(a.real_len),
		sign(a.sign)
	{
		buf = new char [a.capacity];
		std::memcpy(buf, a.buf, a.capacity);

	}

	~BigInt()
	{
		delete[] buf;
	}

	BigInt& operator=(const BigInt &a)
	{
		capacity = a.capacity;
		real_len = a.real_len;
		sign = a.sign;
		rewriteBuf(a.buf, a.capacity);
		return *this;
	}

	friend BigInt abs(const BigInt& a) 
	{
		BigInt b = a;
		b.setSign(std::abs(b.sign));
		return b;
	}

	friend bool operator>(const BigInt& a1, const BigInt& a2)
	{
		if (a1.sign > a2.sign)
			return true;

		else if (a2.sign > a1.sign)
			return false;		
		
		else if (a1.real_len > a2.real_len)
			return (a1.sign > 0);
		
		else if (a2.real_len > a1.real_len)
			return (a2.sign < 0);

		else if (a1.real_len == a2.real_len) {
			for (int i = a1.real_len - 1; i >= 0; i--) {
				
				if (a1.getValue(i) > a2.getValue(i))
					return a1.sign > 0;
				
				if (a1.getValue(i) < a2.getValue(i))
					return not (a1.sign > 0);				
			}	
			return false;		
		}
		else 
			return false;
	}

	friend bool operator<(const BigInt& a1, const BigInt& a2)
	{
		return a2 > a1; 
	}

	friend bool operator==(const BigInt& a1, const BigInt& a2)
	{
		if (a1.real_len != a2.real_len)
			return false;
		for (size_t i = 0; i < a1.real_len; i++) {
			if (a1.getValue(i) != a2.getValue(i))
				return false;
		}
		return true;
	}

	friend bool operator!=(const BigInt& a1, const BigInt& a2)
	{
		return not(a1 == a2); 
	}

	friend bool operator<=(const BigInt& a1, const BigInt& a2)
	{
		return not(a1 > a2); 
	}

	friend bool operator>=(const BigInt& a1, const BigInt& a2)
	{
		return not(a1 < a2); 
	}

	friend std::ostream& operator<<(std::ostream& os, const BigInt& a)
	{
		if (a.sign == 0)
			os << 0;
		if (a.sign < 0)
			os << "-";
		for (int i = a.real_len - 1; i >= 0; i--) {
		    os << static_cast<int>(a.getValue(i));
		}
	    return os;
	}

	friend BigInt operator-(const BigInt& a)
	{
		BigInt b = a;
		b.setSign(-1 * b.sign);
		return b;
	}

	friend BigInt operator+(const BigInt& a1, const BigInt& a2)
	{
		const BigInt* big;
		const BigInt* small;
		BigInt a = 0;
		char sum, move = 0;
		size_t i = 0;

		if (std::abs(a1.sign - a2.sign) <= 1) {

			big =  a1.real_len > a2.real_len ? &a1 : &a2;
			small = a1.real_len > a2.real_len ? &a2 : &a1;

			for (; i < small->real_len; i++) {
				sum = big->getValue(i) + small->getValue(i) + move;
				move = sum / 10;
				a.setValue(sum % 10, i);
			}

			for (; i < big->real_len; i++) {
				sum = big->getValue(i) + move;
				move = sum / 10;
				a.setValue(sum % 10, i);
			}

			a.setValue(move, i);
						
		} else {

			bool abs_a1_bigger = abs(a1) > abs(a2);

			big =  abs_a1_bigger ? &a1 : &a2;
			small = abs_a1_bigger ? &a2 : &a1;

			for (; i < small->real_len; i++) {
				sum = big->getValue(i) - small->getValue(i) + move;
				move = sum < 0 ? -1 : 0;
				a.setValue((sum + 10) % 10, i);
			}

			for (; i < big->real_len; i++) {
				sum = big->getValue(i) + move;
				move = sum < 0 ? -1 : 0;
				a.setValue((sum + 10) % 10, i);
			}
		}

		a.countRealLen();
		if (a.real_len == 0)
			a.setSign(0);
		else
			a.setSign(big->sign);
		return a;
	}

	friend BigInt operator-(const BigInt& a1, const BigInt& a2)
	{
		return a1 + (-a2);
	}

	friend BigInt operator*(const BigInt& a1, const BigInt& a2)
	{
		size_t i, j;
		char sum, move;
		BigInt a = 0;
		const BigInt* big =  a1.real_len > a2.real_len ? &a1 : &a2;
		const BigInt* small = a1.real_len > a2.real_len ? &a2 : &a1;
		for (i = 0; i < small->real_len; i++) {
			BigInt tmp_a = 0;
			move = 0;
			for (j = 0; j < big->real_len; j++) {
				sum = big->getValue(j) * small->getValue(i) + move;
				move = sum / 10;
				tmp_a.setValue(sum % 10, i + j);
			}
			tmp_a.setValue(move, i + j);
			tmp_a.setSign(1);
			tmp_a.countRealLen();
			a = a + tmp_a;
		}
		a.countRealLen();
		a.setSign(big->sign * small->sign);
		return a;
	}

	friend BigInt operator/(const BigInt& a1, const BigInt& a2)
	{
		if (abs(a2) > abs(a1))
			return 0;
		BigInt dividend = abs(a1); // делимое
		BigInt a = 0; // ответ
		int shift = a1.real_len - a2.real_len;
		while(shift >= 0) {
			BigInt devisor = 0;
			formDevisor(devisor, a2, shift);
			int count = 0;
			while (dividend >= devisor) {
				dividend = dividend - devisor;
				count++;
			}
			a.setValue(count, shift);
			shift -= 1;
		}		
		a.countRealLen();
		a.setSign(a1.sign * a2.sign);
		return a;
	}

private:

	friend void formDevisor(BigInt& devisor, const BigInt& a, int shift)
	{
		devisor.resizeBuf(a.capacity + shift);
		memset(devisor.buf, 0, devisor.capacity);
		std::memcpy(devisor.buf + shift, a.buf, a.capacity);
		devisor.countRealLen();
		devisor.setSign(1);
	}
	
	char getValue(size_t i) const
	{
		return buf[i];
	}

	void setValue(char value, size_t i)
	{
		if (i > capacity - 1) {
			resizeBuf(2*i);
		}
		buf[i] = value;
	}

	void resizeBuf(size_t new_capacity)
	{
		char* new_buf = new char [new_capacity];
		std::memset(new_buf, 0, new_capacity);
		std::memcpy(new_buf, buf, capacity);
		delete [] buf;
		buf = new_buf;
		capacity = new_capacity;
	}

	void rewriteBuf(const char* source, size_t new_capacity)
	{
		delete [] buf;
		buf = new char [new_capacity];
		std::memcpy(buf, source, new_capacity);
	}

	void countRealLen()
	{
		for (int i = capacity - 1; i >= 0; i--) {
			if (buf[i]) {
				real_len = i + 1;
				return;
			}
		}	
	}

	void setSign(int s)
	{
		if (real_len == 0 or s == 0)
			sign = 0;
		else 
			sign = s > 0 ? 1 : -1;
	}
};