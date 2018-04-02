#pragma once
#include<iostream>

template<class T>
class Mvector
{
public:
	Mvector();
	Mvector(const Mvector<T>& other);
	Mvector(Mvector<T>&& moved);
	Mvector<T>& operator=(const Mvector<T>& other);
	Mvector<T>& operator=(Mvector<T>&& moved);
	~Mvector();

	T& operator[](size_t i);
	T& operator[](size_t i) const;
	void push_back(T x);
	size_t size();
	size_t capacity();


private:
	T * _array;
	size_t _size;
	size_t _capacity;
	void resize();
};

template<class T>
Mvector<T>::Mvector()
{
	_capacity = 4;
	T* _array = new T[_capacity];
	_size = 0;
}

template<class T>
 Mvector<T>::Mvector(const Mvector<T> & other): 
	 _capacity(other._capacity), _size(other._size)
{
	 T* _array = new T[_capacity];
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
 inline Mvector<T>& Mvector<T>::operator=(Mvector<T>&& moved)
 {
	 if (this != &moved) {
		 delete[] _array;
		 _array = moved._array;
		 _capacity = moved._capacity;
		 _size = moved.size_;
		 moved.data_ = nullptr;
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
 size_t Mvector<T>::size()
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
