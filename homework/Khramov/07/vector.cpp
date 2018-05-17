#include <limits>
#include <iterator>
#include <memory>
#include <algorithm>
#include <cstring>

template<class T>
class allocator
{
public:
	using value_type = T;
	using pointer = T * ;
	using size_type = size_t;

	pointer allocate(size_type count)
	{
		pointer ptr = (pointer)malloc(sizeof(value_type) * count);
		return ptr;
	}
	void deallocate(pointer ptr, size_type count) {
		free(ptr);
	}

	size_type max_size() const noexcept {

		return std::numeric_limits<size_type>::max();
	}

	void construct(pointer ptr)
	{
		ptr = new(ptr) value_type();
	}

	void construct(pointer ptr, const value_type& value)
	{
		ptr = new(ptr) value_type(value);
	}

	void destroy(pointer ptr)
	{
		ptr->~value_type();
	}
};

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag , T>
{
	T* ptr_;
public:
	using reference = T & ;
	explicit Iterator(T* ptr) : ptr_(ptr) {}

	bool operator==(const Iterator<T>& other) const
	{
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator<T>& other) const
	{
		return !(*this == other);
	}

	reference operator*() const
	{
		return *ptr_;
	}

	Iterator& operator++()
	{
		++ptr_;
		return *this;
	}

	Iterator& operator--()
	{
		--ptr_;
		return *this;
	}

	Iterator operator+(const size_t val)
	{
		ptr_ += val;
		return *this;
	}

	Iterator operator-(const size_t val)
	{
		ptr_ -= val;
		return *this;
	}

};


template<class T, class Allocator = allocator<T>>
class Vector
{
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T * ;
	using reference = T & ;
	using iterator = Iterator<T>;

	Vector();
	Vector(size_type count);
	Vector(const Vector<T, Allocator>& other);
	Vector<T, Allocator>& operator=(const Vector<T, Allocator>& other);
	~Vector();

	iterator begin() noexcept;
	iterator end() noexcept;
	std::reverse_iterator<Iterator<T>> rbegin() noexcept;
	std::reverse_iterator<Iterator<T>> rend() noexcept;

	T& operator[](size_type i);
	const T& operator[](size_type i) const;
	void push_back(const value_type& value);
	void pop_back();
	void resize(size_type newSize);
	size_type size() const noexcept;
	size_type capacity(){
		return _capacity;
	}
	void clear() noexcept;
	bool empty() const noexcept;
    void reserve(size_type newSize);


private:
	Allocator _alloc;
	pointer _array;
	size_type _size;
	size_type _capacity;
};

template<class T, class Allocator>
Vector<T, Allocator>::Vector()
	: _capacity(4)
	, _array(_alloc.allocate(4))
	, _size(0)
{
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count)
	: _capacity(count)
	, _array(_alloc.allocate(count))
	, _size(count)
{
	for (size_type i = 0; i < count; i++)
		_alloc.construct(_array + i);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector<T, Allocator> & other)
	: _capacity(other._capacity)
	, _size(other._size)
{
	_array = _alloc.allocate(other._capacity);
	std::memcpy(_array, other._array, other._size * sizeof(value_type));
}

template<class T, class Allocator>
Vector<T, Allocator> & Vector<T, Allocator>::operator=(const Vector<T, Allocator> & other)
{
	if (this != &other) {
		pointer newData = _alloc.allocate(other._capacity);
		std::memcpy(newData, other._array, other._size * sizeof(value_type));
		std::swap(_array, newData);
		_alloc.deallocate(newData, other._size);
		_capacity = other._capacity;
		_size = other._size;
	}
	return *this;
}

template<class T, class Allocator>
Vector<T, Allocator>::~Vector()
{
	clear();
	_alloc.deallocate(_array, 0);
}

template<class T, class Allocator>
Iterator<T> Vector<T, Allocator>::begin() noexcept
{
	return Iterator<T>(_array);
}

template<class T, class Allocator>
Iterator<T> Vector<T, Allocator>::end() noexcept
{
	return Iterator<T>(_array + _size);
}

template<class T, class Allocator>
std::reverse_iterator<Iterator<T>> Vector<T, Allocator>::rbegin() noexcept
{
	return std::reverse_iterator<Iterator<T>>(end());
}

template<class T, class Allocator>
std::reverse_iterator<Iterator<T>> Vector<T, Allocator>::rend() noexcept
{
	return std::reverse_iterator<Iterator<T>>(begin());
}

template<class T, class Allocator>
T & Vector<T, Allocator>::operator[](size_type i)
{
	return _array[i];
}

template<class T, class Allocator>
const T & Vector<T, Allocator>::operator[](size_type i) const
{
	return _array[i];
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(const value_type& x) {
	if (_size == _capacity) {
		if (_size == 0)
			reserve(1);
		else
			reserve(_capacity * 2);
	}
	_alloc.construct(_array + _size, x);
	_size++;

}

template<class T, class Allocator>
void Vector<T, Allocator>::pop_back()
{
	if (_size > 0)
		resize(_size - 1);
}

template<class T, class Allocator>
size_t Vector<T, Allocator>::size() const noexcept
{
	return _size;
}

template<class T, class Allocator>
void Vector<T, Allocator>::reserve(size_type newSize)
{
    if (newSize > _capacity){
        pointer newData = _alloc.allocate(newSize);
        std::memcpy(newData, _array, _size * sizeof(value_type));
        std::swap(_array, newData);
        _alloc.deallocate(newData, _size);
        _capacity = newSize;
    }
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_type newSize)
{
	if (newSize < _size) {
		for (size_type i = newSize; i < _size; i++)
			_alloc.destroy(_array + i);
	}
	else if (newSize > _size) {
		if (newSize > _capacity) {
			reserve(newSize);
		}
		for (size_type i = _size; i < newSize; i++)
			_alloc.construct(_array + i);
	}
	_size = newSize;
}

template<class T, class Allocator>
void Vector<T, Allocator>::clear() noexcept
{
	resize(0);
}

template<class T, class Allocator>
bool Vector<T, Allocator>::empty() const noexcept
{
	return _size == 0;
}
