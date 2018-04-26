#pragma once
#include <iterator>

template<class T>
class Iterator :
	public std::iterator<std::random_access_iterator_tag, T>
{
public:
	using size_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
	using pointer = typename std::iterator<std::random_access_iterator_tag, T>::pointer;
	using reference = typename std::iterator<std::random_access_iterator_tag, T>::reference;

private: pointer _ptr;
public:
	explicit Iterator(pointer ptr) :
		_ptr(ptr) {}

	bool operator==(const Iterator<T>& other) const
	{
		return _ptr == other._ptr;
	}

	bool operator!=(const Iterator<T>& other) const
	{
		return !(_ptr == other._ptr);
	}

	reference operator*() const
	{
		return *_ptr;
	}


	Iterator & operator+(size_t& val)
	{
		ptr_ += val;
		return *this;
	}

	Iterator & operator-(size_t& val)
	{
		ptr_ -= val;
		return *this;
	}
	Iterator & operator++()
	{
		++_ptr;
		return *this;
	}
	Iterator & operator--()
	{
		--_ptr;
		return *this;
	}
};