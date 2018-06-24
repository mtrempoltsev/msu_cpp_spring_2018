#include <iostream>
#include <stdexcept>
#include <utility>
#include <limits>
#include <cstring>


template<class T>
class Allocator
{
public:
	T * allocate(size_t count);
	void deallocate(T* p);
	void construct(T* p);
	void construct(T* p, const T &init_val);
	void destroy(T* p);
	size_t max_size() const noexcept;
};

template <class T>
class Iterator
{
	T* pointer;
public:
	Iterator(T* pointer);
	T& operator*();
	const T& operator*() const;
	Iterator& operator++();
	Iterator& operator--();
	Iterator operator++(int);
	Iterator operator--(int);
	Iterator operator+(size_t n) const;
	Iterator operator-(size_t n) const;
	bool operator==(const Iterator<T> &a);
	bool operator!=(const Iterator<T> &a) const;
};

template <class T>
class RIterator
{
	T* pointer;
public:
	RIterator(T* pointer);
	T& operator*();
	const T& operator*() const;
	RIterator& operator++();
	RIterator& operator--();
	RIterator operator++(int);
	RIterator operator--(int);
	RIterator operator+(size_t n) const;
	RIterator operator-(size_t n) const;
	bool operator==(const RIterator<T> &a);
	bool operator!=(const RIterator<T> &a) const;
};


template <class T>
T* Allocator<T>::allocate(size_t count) {
	T* p = (T*)malloc(sizeof(T) * count);
	return p;
}

template <class T>
void Allocator<T>::deallocate(T* p) { free(p); }

template <class T>
void Allocator<T>::construct(T* p) { p = new(p) T(); }

template <class T>
void Allocator<T>::construct(T* p, const T &init_val) { p = new(p) T(init_val); }

template <class T>
void Allocator<T>::destroy(T* p) { p->~T(); }

template <class T>
size_t Allocator<T>::max_size() const noexcept { return std::numeric_limits<size_t>::max() / sizeof(T); }



template <class T>
Iterator<T>::Iterator(T* pointer) { this->pointer = pointer; }

template <class T>
T& Iterator<T>::operator*() { return *pointer; }

template <class T>
const T& Iterator<T>::operator*() const { return *pointer; }

template <class T>
Iterator<T>& Iterator<T>::operator++() {
	pointer++;
	return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator--() {
	pointer--;
	return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator++(int) {
	Iterator<T> iterator(pointer);
	pointer++;
	return iterator;
}

template <class T>
Iterator<T> Iterator<T>::operator--(int) {
	Iterator<T> iterator(pointer);
	pointer--;
	return iterator;
}

template <class T>
Iterator<T> Iterator<T>::operator+(size_t n) const { return Iterator(pointer + n); }

template <class T>
Iterator<T> Iterator<T>::operator-(size_t n) const { return Iterator<T>(pointer - n); }

template <class T>
bool Iterator<T>::operator==(const Iterator<T> &a) { return pointer == a.pointer; }

template <class T>
bool Iterator<T>::operator!=(const Iterator<T> &a) const { return pointer != a.pointer; }


template <class T>
RIterator<T>::RIterator(T* pointer) { this->pointer = pointer; }

template <class T>
T& RIterator<T>::operator*() { return *pointer; }

template <class T>
const T& RIterator<T>::operator*() const { return *pointer; }

template <class T>
RIterator<T>& RIterator<T>::operator++() {
	pointer--;
	return *this;
}

template <class T>
RIterator<T>& RIterator<T>::operator--() {
	pointer++;
	return *this;
}

template <class T>
RIterator<T> RIterator<T>::operator++(int) {
	RIterator<T> iter(pointer);
	pointer--;
	return iter;
}

template <class T>
RIterator<T> RIterator<T>::operator--(int) {
	RIterator<T> iter(pointer);
	pointer++;
	return iter;
}

template <class T>
RIterator<T> RIterator<T>::operator+(size_t n) const { return RIterator<T>(pointer - n); }

template <class T>
RIterator<T> RIterator<T>::operator-(size_t n) const { return RIterator<T>(pointer + n); }

template <class T>
bool RIterator<T>::operator==(const RIterator<T> &a) { return pointer == a.pointer; }

template <class T>
bool RIterator<T>::operator!=(const RIterator<T> &a) const { return pointer != a.pointer; }


template <class T>
class Vector
{
private:
	T* buffer;
	size_t lenght;
	size_t cap;
	Allocator<T> alloc;

public:

	Vector(size_t cap = 10) {
		this->cap = cap;
		lenght = 0;
		buffer = alloc.allocate(this->cap);
	}

	~Vector() {
		for (int i = 0; i < lenght; i++) {
			alloc.destroy(buffer + i);
		}
		alloc.deallocate(buffer);
		lenght = 0;
		cap = 0;
	}

	Iterator<T> begin() { return Iterator<T>(buffer); }
	const Iterator<T> begin() const { return Iterator<T>(buffer); }
	RIterator<T> rbegin() { return RIterator<T>(buffer + lenght - 1); }
	const RIterator<T> rbegin() const { return RIterator<T>(buffer + lenght - 1); }
	Iterator<T> end() { return Iterator<T>(buffer + lenght); }
	const Iterator<T> end() const { return Iterator<T>(buffer + lenght); }
	RIterator<T> rend() { return RIterator<T>(buffer - 1); }
	const RIterator<T> rend() const { return RIterator<T>(buffer - 1); }
	size_t size() const { return lenght; }
	bool empty() const { return (lenght == 0); }

	T& operator[](size_t i) {
		if (i >= lenght) {
			throw std::out_of_range("");
		}
		return buffer[i];
	}

	const T& operator[](size_t i) const {
		if (i >= lenght) {
			throw std::out_of_range("");
		}
		return buffer[i];
	}

	void reserve(size_t cap) {
		if (this->cap < cap) {
			T* new_data = alloc.allocate(cap);
			std::memcpy(new_data, buffer, lenght * sizeof(T));
			std::swap(buffer, new_data);
			alloc.deallocate(new_data);
			this->cap = cap;
		}
	}

	void resize(size_t new_lenght) {
		if (new_lenght > cap) {
			reserve(new_lenght);
		}

		for (int i = lenght; i < new_lenght; i++) {
			alloc.construct(buffer + i);
		}

		for (int i = new_lenght; i < lenght; i++) {
			alloc.destroy(buffer + i);
		}

		lenght = new_lenght;
	}

	void push_back(const T& val) {
		if (lenght == cap) {
			reserve(cap * 2);
		}
		alloc.construct(buffer + lenght, val);
		lenght++;
	}

	void pop_back() { resize(lenght - 1); }
	void clear() { resize(0); }
	size_t capacity() { return cap; }
};
