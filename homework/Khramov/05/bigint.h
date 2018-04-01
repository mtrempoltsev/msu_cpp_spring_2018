#include<iomanip>
#include<iostream>

#define DIGIT_SIZE 1000'000'000
#define BASE 9

#pragma once


template<class T>
class Mvector
{
public:

	Mvector();
	Mvector(int l, T initial);
	Mvector(const Mvector<T>& other);
	Mvector(Mvector<T>&& moved);
	Mvector<T>& operator=(const Mvector<T>& other);
	Mvector<T>& operator=(Mvector<T>&& moved);
	~Mvector();

	T& operator[](size_t i);
	T& operator[](size_t i) const;
	void push_back(T x);
	void pop();
	void push_front(T x);
	int size() const;
	size_t capacity();
	void new_size(int i, T initial) {
		if (_size > i) return;
		T* newMem = new T[i];
		std::copy(_array, _array + _size, newMem);

		for (int j = _size; j < i; j++) {
			newMem[j] = initial;
			//std::cout << newMem[j] <<" -j- "<<j<< '\n';
		}
		delete[] _array;
		_array = newMem;
		_capacity = i;
	}


private:
	T * _array = nullptr;
	size_t _size;
	size_t _capacity;
	void resize();
};


template<class T>
Mvector<T>::Mvector()
{
	_capacity = 4;
	_array = new T[_capacity];
	_size = 0;
}


template<class T>
Mvector<T>::Mvector(int l, T initial)
{
	_capacity = l;
	_array = new T[_capacity]{ initial };
	_size = l;
}


template<class T>
Mvector<T>::Mvector(const Mvector<T> & other) :
	_capacity(other._capacity), _size(other._size)
{
	_array = new T[_capacity];
	std::copy(other._array, other._array + _size, _array);
}

template<class T>
Mvector<T> & Mvector<T>::operator=(const Mvector<T> & other)
{
	if (this != &other) {
		T* tmp = new T[other._capacity];
		std::copy(other._array, other._array + other._size, tmp);
		delete[] _array;
		_array = tmp;
		_capacity = other._capacity;
		_size = other._size;
	}
	return *this;
}

template<class T>
Mvector<T>::Mvector(Mvector && moved) :
	_capacity(moved._capacity), _size(moved._size)
{
	_array = moved._array;
	moved._array = nullptr;
}

template<class T>
Mvector<T>& Mvector<T>::operator=(Mvector<T>&& moved)
{
	if (this != &moved) {
		delete[] _array;
		_array = moved._array;
		_capacity = moved._capacity;
		_size = moved._size;
		moved._array = nullptr;
	}
	return *this;
}

template<class T>
Mvector<T>::~Mvector()
{

	delete[] _array;
}

template<class T>
T& Mvector<T>::operator[](size_t i)
{
	return _array[i];
}

template<class T>
T& Mvector<T>::operator[](size_t i) const
{
	return _array[i];
}

template<class T>
void Mvector<T>::push_back(T x)
{
	if (_size == _capacity) {
		resize();
	}
	_array[_size++] = x;
}

template<class T>
inline void Mvector<T>::pop()
{
	_size--;
}

template<class T>
inline void Mvector<T>::push_front(T x)
{
	if (_size == _capacity) {
		resize();
	}
	if (_size > 0) {
		for (size_t i = _size; i > 0; i--) {
			_array[i] = _array[i - 1];
		}
	}
	_size++;
	_array[0] = x;
}



template<class T>
int Mvector<T>::size() const
{
	return _size;
}

template<class T>
size_t Mvector<T>::capacity()
{
	return _capacity;
}

template<class T>
void Mvector<T>::resize()
{
	_capacity *= 2;
	T* newMem = new T[_capacity];
	std::copy(_array, _array + _size, newMem);
	delete[] _array;
	_array = newMem;
}



class BigInt
{
public:
	BigInt();
	BigInt(long long a);
	BigInt(const bool sign, const Mvector<long long> num);
	BigInt(const BigInt& other);
	//BigInt(BigInt&& moved);
	BigInt& operator=(const BigInt& b);
	//BigInt& operator=(BigInt&& moved);
	~BigInt();

	friend std::ostream& operator<<(std::ostream& out, const BigInt& b);

	friend BigInt operator+(const BigInt& left, const BigInt& right);
	friend BigInt operator-(const BigInt& left, const BigInt& right);
	friend BigInt operator*(const BigInt& left, const BigInt& right);
	friend BigInt operator/(const BigInt& left, const BigInt& right);
	friend bool compare_abs(const BigInt& one, const BigInt& two);
	friend long long binsearch(const BigInt &div, const BigInt &num);


	BigInt operator-() const;
	bool operator==(const BigInt& other) const;
	bool operator>=(const BigInt& other) const;
	bool operator<=(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator>(const BigInt& other) const;
	bool operator<(const BigInt& other) const;

	void add_reversDigit(long long x) {
		_digits.push_back(x);
	}
	int size() const{
		return this->_digits.size();
	}
	
private:
	Mvector<long long> _digits;
	bool _sign=true;
	int get_size() const;
	
	void resize_to(int i) {
		_digits.new_size(i,0);
	}
	void kill_zeroes();
	
};

BigInt::BigInt(){

}

BigInt::BigInt(long long a)
{
	_sign = a >= 0 ? true : false;
	long long t = a * (2 * _sign - 1);
	_digits.push_back(t % DIGIT_SIZE);
	if (t > DIGIT_SIZE) {
		t = t / DIGIT_SIZE;
		_digits.push_back(t % DIGIT_SIZE);
		if (t > DIGIT_SIZE) 
			_digits.push_back(t / DIGIT_SIZE);
	}
	//std::cout << _digits[1]<<" 1 "<<" 0-> " << _digits[0]<< " 2-> " << _digits[2] << "\n";
}

BigInt::BigInt(bool sign, const Mvector<long long> vec):
	_sign(sign),_digits(vec) {}

BigInt::~BigInt(){}

bool compare_abs(const BigInt& one, const BigInt& two)
{
	if (one.get_size()>two.get_size()) return true;
	if (one.get_size()<two.get_size()) return false;
	for (int i = one.get_size() - 1; i >= 0; i--) 
		if (one._digits[i]<=two._digits[i]) return false;
	
	return true;
	
}


inline int BigInt::get_size() const
{
	return this->_digits.size();
}

inline void BigInt::kill_zeroes()
{
	int i = this->get_size()-1;
	while (this->_digits[i] == 0 && i != 0) {
		this->_digits.pop();
		i--;
	}
}

BigInt::BigInt(const BigInt & other): 
	_sign(other._sign), _digits(other._digits) 
{
}

BigInt & BigInt::operator=(const BigInt & other)
{
	if (this != &other) {
		_digits = Mvector<long long>(other._digits);
		_sign = other._sign;
	}
	return *this;
}

/*
BigInt::BigInt(BigInt && moved)
{
}

BigInt & BigInt::operator=(BigInt && moved)
{
	// TODO: вставьте здесь оператор return
}*/


std::ostream & operator<<(std::ostream & out, const BigInt & b)
{
	if (!b._sign)
		out << '-';
	out << b._digits[b.size() - 1];
	//std::cout << b._digits[b.size() - 1] << " bdid " << '\n';
	for (int i = b.size() - 2; i >= 0; i--) {
		out << std::setfill('0');
		out << std::setw(BASE) << b._digits[i];
	}
	return out;
}

BigInt operator+(const BigInt & left, const BigInt & right)
{	
	//std::cout << right << " rht1" << '\n';
	if (compare_abs(right, left)) return (right + left);
	BigInt res,Temp;
	//std::cout << right << " rht" << '\n';
	long long rest = 0;
	int sze = 0;
	
	Temp = BigInt(right);
	Temp.resize_to(left.get_size());
	sze = left.get_size();
	
	
	if (left._sign != right._sign) {
		for (int i = 0; i < sze; i++) {
			long long tmp = (rest+left._digits[i] - Temp._digits[i]);
			//std::cout << left._digits[i] << " - " << Temp._digits[i]<< '\n';
			if (tmp <0) {
				tmp += DIGIT_SIZE;
				rest = -1;
			}
			else rest = 0;

			res._digits.push_back(tmp);
		}
		if (left._sign) {
			res._sign = true;
		}
		else res._sign = false;
		if (res.get_size() == 1 && res._digits[0] == 0) {
			res._sign = true;
		}
	}
	else {
			int i = 0;
			for (; i < sze; i++) {
				long long tmp = (left._digits[i] + Temp._digits[i]) % DIGIT_SIZE;
				res._digits.push_back(tmp + rest);
				rest = (left._digits[i] + right._digits[i]) / DIGIT_SIZE;
			}
			res._digits[i] += rest;

			if (left._sign) {
				res._sign = true;
			}
			else res._sign = false;
	}
	//res.kill_zeroes();
	return res;
}

BigInt operator-(const BigInt & left, const BigInt & right)
{
	return -right + left;
}

BigInt BigInt::operator-() const
{
	BigInt tmp(*this);
	tmp._sign = !_sign;
	return tmp;
}

bool BigInt::operator==(const BigInt & other) const
{
	if (_sign != other._sign) {
		return false;
	}
	if (get_size() != other.get_size())
		return false;

	for (int i = get_size()-1; i >= 0 ; i--) 
	{
		if (_digits[i] != other._digits[i]) {
			return false;
		}
	}
	return true;
}

bool BigInt::operator>=(const BigInt & other) const
{
	return!(*this < other);
}

bool BigInt::operator<=(const BigInt & other) const
{

	return !(*this>other);
}

bool BigInt::operator!=(const BigInt & other) const
{
	return !(*this == other);
}

bool BigInt::operator>(const BigInt & other) const
{
	return other<*this;
}

bool BigInt::operator<(const BigInt & other) const
{	
	if (_sign != other._sign)
		return !_sign;

	if (_sign) {
		if (get_size() < other.get_size())
			return true;
		if (get_size() > other.get_size())
			return false;
		for (int i = get_size()-1; i >= 0; i--)
		{
			if (_digits[i] < other._digits[i]) {
				//std::cout<<"le  "<< _digits[i]<<"r "<< other._digits[i]
				return true;
			}
			else if (_digits[i] > other._digits[i]) {
				return false;
			}
		}
		return false;
	}else {
		if (get_size() < other.get_size())
			return false;
		if (get_size() > other.get_size())
			return true;
		for (int i = get_size() - 1; i >= 0; i--)
		{
			if (_digits[i] < other._digits[i]) {
				return false;
			}
			else if (_digits[i] > other._digits[i]) {
				return true;
			}
		}
		return true;
	}
}

BigInt operator*(const BigInt & left, const BigInt & right)
{
	if (left == 0 || right == 0)
		return BigInt(0);

	Mvector<long long> r_copy = right._digits;
	Mvector<long long> l_copy = left._digits;
	bool sign = (right._sign == left._sign);

	size_t length = r_copy.size() + l_copy.size();
	Mvector<long long> res(length, 0);

	for (int i = 0; i < r_copy.size(); i++)
		for (int j = 0; j < l_copy.size(); j++) {
			
			res[i + j] += r_copy[i] * l_copy[j];
		}
	
	for (int i = 0; i < length - 1; i++)
	{
		res[i + 1] += res[i] / DIGIT_SIZE;
		res[i] %= DIGIT_SIZE;
	}
	BigInt rez(sign, res);
	rez.kill_zeroes();
	if (rez.get_size() == 1 && rez._digits[0] == 0) {
		rez._sign = true;
	}
	return rez;
}

inline long long binsearch(const BigInt & div, const BigInt & num) 
{
	long long rez = 0;
	long long min = 0;
	long long max = DIGIT_SIZE;
	//std::cout << "curr*" << num << "  <=" << div << '\n';
	while (min <= max)
	{
		long long curr = (max + min) / 2;
		if (BigInt(curr) * num <= div)
		{
			rez = curr;
			min = curr + 1;
		}
		else
			max = curr - 1;
	}
	return rez;

}

BigInt operator/(const BigInt & left, const BigInt & right)
{	
	BigInt quotient;
	BigInt param;
	BigInt abs_num(right);
	abs_num._sign = true;
	for (size_t i = 0; i < left.get_size(); i++)
	{
		param._digits.push_front(left._digits[left.get_size() - 1 - i]);
		//std::cout << "index -> " << left.get_size() - 1 - i << "  __left._digits[]  " << left._digits[left.get_size() - 1 - i] << '\n';
		//std::cout << "param  " << param  << "  _dig -> " << param._digits[0] << '\n';
		long long div = binsearch(param, abs_num);
		quotient._digits.push_front(div);
		param = param - abs_num * BigInt(div);
		//std::cout << " param after " << param << '\n';
		//std::cout << " div " << div << '\n';
		if (param == 0) {
			param._digits.pop();
		}
	}
	
	quotient._sign = left._sign == right._sign;
	quotient.kill_zeroes();
	if (quotient.get_size() == 1 && quotient._digits[0] == 0) {
		quotient._sign = true;
	}
	return quotient;
	
}
