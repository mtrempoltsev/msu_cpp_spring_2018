#include <iostream>
#include <cstring>
#include <cmath>

inline int get_sign(long long int a) {
    return (0 < a) - (a < 0);
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
		capacity(a.getCapacity()),
		real_len(a.getRealLen()),
		sign(a.getSign())
	{
		buf = new char [a.getCapacity()];
		std::memcpy(buf, a.buf, a.getCapacity());

	}

	~BigInt()
	{
		delete[] buf;
	}

	BigInt& operator=(const BigInt &a)
	{
		capacity = a.getCapacity();
		real_len = a.getRealLen();
		sign = a.getSign();
		rewriteBuf(a.buf, a.getCapacity());
		return *this;
	}


	friend BigInt abs(const BigInt& a) 
	{
		BigInt b = a;
		b.setSign(std::abs(b.getSign()));
		return b;
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

	size_t getCapacity() const
	{
		return capacity;
	}
	size_t getRealLen() const
	{
		return real_len;
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

	int getSign() const
	{
		return sign;
	}

	void setSign(int s)
	{
		if (real_len == 0)
			sign = 0;
		else 
			sign = s;
	}


	friend bool operator>(const BigInt& a1, const BigInt& a2)
	{
		if (a1.getSign() > a2.getSign())
			return true;

		else if (a2.getSign() > a1.getSign())
			return false;		
		
		else if (a1.getRealLen() > a2.getRealLen())
			return (a1.getSign() > 0);
		
		else if (a2.getRealLen() > a1.getRealLen())
			return (a2.getSign() < 0);

		else if (a1.getRealLen() == a2.getRealLen()) {
			for (int i = a1.getRealLen() - 1; i >= 0; i--) {
				
				if (a1.getValue(i) > a2.getValue(i))
					return a1.getSign() > 0;
				
				if (a1.getValue(i) < a2.getValue(i))
					return not (a1.getSign() > 0);				
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
		if (a1.getRealLen() != a2.getRealLen())
			return false;
		for (size_t i = 0; i < a1.getRealLen(); i++) {
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
		if (a.getSign() == 0)
			os << 0;
		if (a.getSign() < 0)
			os << "-";
		for (int i = a.getRealLen() - 1; i >= 0; i--) {
		    os << static_cast<int>(a.getValue(i));
		}
	    return os;
	}

	friend BigInt operator-(const BigInt& a)
	{
		BigInt b = a;
		b.setSign(-1 * b.getSign());
		return b;
	}

	friend BigInt operator+(const BigInt& a1, const BigInt& a2)
	{
		const BigInt* big;
		const BigInt* small;
		BigInt a = 0;
		char sum, move = 0;
		size_t i = 0;

		if (std::abs(a1.getSign() - a2.getSign()) <= 1) {

			big =  a1.getRealLen() > a2.getRealLen() ? &a1 : &a2;
			small = a1.getRealLen() > a2.getRealLen() ? &a2 : &a1;

			for (; i < small->getRealLen(); i++) {
				sum = big->getValue(i) + small->getValue(i) + move;
				move = sum / 10;
				a.setValue(sum % 10, i);
			}

			for (; i < big->getRealLen(); i++) {
				sum = big->getValue(i) + move;
				move = sum / 10;
				a.setValue(sum % 10, i);
			}

			a.setValue(move, i);
						
		} else {

			bool abs_a1_bigger = abs(a1) > abs(a2);

			big =  abs_a1_bigger ? &a1 : &a2;
			small = abs_a1_bigger ? &a2 : &a1;

			for (; i < small->getRealLen(); i++) {
				sum = big->getValue(i) - small->getValue(i) + move;
				move = sum < 0 ? -1 : 0;
				a.setValue((sum + 10) % 10, i);
			}

			for (; i < big->getRealLen(); i++) {
				sum = big->getValue(i) + move;
				move = sum < 0 ? -1 : 0;
				a.setValue((sum + 10) % 10, i);
			}
		}

		a.countRealLen();
		if (a.getRealLen() == 0)
			a.setSign(0);
		else
			a.setSign(big->getSign());
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
		const BigInt* big =  a1.getRealLen() > a2.getRealLen() ? &a1 : &a2;
		const BigInt* small = a1.getRealLen() > a2.getRealLen() ? &a2 : &a1;
		for (i = 0; i < small->getRealLen(); i++) {
			BigInt tmp_a = 0;
			move = 0;
			for (j = 0; j < big->getRealLen(); j++) {
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
		a.setSign(big->getSign() * small->getSign());
		return a;
	}


	friend void formDevisor(BigInt& devisor, const BigInt& a, int shift)
	{
		devisor.resizeBuf(a.getCapacity() + shift);
		memset(devisor.buf, 0, devisor.getCapacity());
		std::memcpy(devisor.buf + shift, a.buf, a.getCapacity());
		devisor.countRealLen();
		devisor.setSign(1);
	}

	friend BigInt operator/(const BigInt& a1, const BigInt& a2)
	{
		if (abs(a2) > abs(a1))
			return 0;
		BigInt dividend = abs(a1); // делимое
		BigInt a = 0; // ответ
		int shift = a1.getRealLen() - a2.getRealLen();
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
		a.setSign(a1.getSign() * a2.getSign());
		return a;
	}


};