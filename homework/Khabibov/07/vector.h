#pragma once
#include <iterator>
#include <memory>

template<class T>
class Allocator
{
public:
	using value_type = T;
	using const_pointer = const value_type*;
	using reference = value_type& ;
	using const_reference = const value_type&;
	using pointer = T * ;
	using size_type = size_t;

	pointer allocate(size_type cnt)
	{
		return reinterpret_cast<pointer>(::operator new(cnt * sizeof(value_type)));
	};

	void deallocate(pointer& p, size_type)
	{
		::operator delete(p);
	};

	void construct(pointer p)
	{
		p = new(p) value_type();
	};

	void construct(pointer p, const value_type& t)
	{
		p = new(p) value_type(t);
	};

	void destroy(pointer p)
	{
		p->~value_type();
	};
};

template<class T>
class Iterator
	: public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:
	using reference = T&;

	explicit Iterator(T* ptr)
		: ptr_(ptr)
	{
	};

	bool operator==(const Iterator<T>& other) const
	{
		return ptr_ == other.ptr_;
	};

	bool operator!=(const Iterator<T>& other) const
	{
		return !(*this == other);
	};

	reference operator*() const
	{
		return *ptr_;
	};

	Iterator& operator++()
	{
		++ptr_;
		return *this;
	};

	Iterator& operator--()
	{
		--ptr_;
		return *this;
	};

	Iterator operator+(size_t i) const
	{
		Iterator result;
		result.ptr_ = ptr_ + i;
		return result;
	};

	Iterator operator-(size_t i) const
	{
		Iterator result;
		result.ptr_ = ptr_ - i;
		return result;
	};
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
	Alloc alloc_;
	size_t size_; // Real size with memory that user unused yet
	size_t length_; // Used memory, length which user see
	T* data_;
public:
	Vector()
		: size_(1)
		, length_(0)
		, data_(alloc_.allocate(1))
	{
	};

	Vector(size_t length)
		: size_(length * 2)
		, length_(length)
		, data_(alloc_.allocate(length * 2))
	{
		for (size_t i = 0; i < length_; i++)
			alloc_.construct(data_ + i);
	};

	~Vector()
	{
		for (size_t i = 0; i < length_; i++)
			alloc_.destroy(data_ + i);
		alloc_.deallocate(data_, size_);
	};

	T& operator[](const size_t number)
	{
		return data_[number];
	};

	void push_back(const T& value)
	{
		if (size_ == length_)
			reserve(size_ * 2);
		alloc_.construct(data_ + length_, value);
		length_++;
	};

	void push_back(T&& value)
	{
		if (size_ == length_)
			reserve(size_ * 2);
		alloc_.construct(data_ + length_, value);
		length_++;
	};

	void pop_back()
	{
		if (length_ == 0)
		{
			length_ = 0;
			return;
		}
		else
		{
			alloc_.destroy(data_ + length_ - 2);
			length_ -= 1;
		}
	};

	bool empty()
	{
		return !length_;
	};

	size_t size()
	{
		return length_;
	};

	size_t capacity()
	{
		return size_;
	}

	void clear()
	{
		for (size_t i = 0; i < length_; i++)
			alloc_.destroy(data_ + i);
		length_ = 0;
	};

	Iterator<T> begin()
	{
		return Iterator<T>(data_);
	};

	Iterator<const T> begin() const
	{
		return Iterator<const T>(data_);
	};

	Iterator<T> end()
	{
		return Iterator<T>(data_ + length_);
	};

	Iterator<const T> end() const
	{
		return Iterator<const T>(data_ + length_);
	};

	std::reverse_iterator<Iterator<T>> rbegin()
	{
		return std::reverse_iterator<Iterator<T>>(end());
	};

	std::reverse_iterator<Iterator<const T>> rbegin() const
	{
		return std::reverse_iterator<Iterator<const T>>(end());
	};

	std::reverse_iterator<Iterator<T>> rend()
	{
		return std::reverse_iterator<Iterator<T>>(begin());
	};

	std::reverse_iterator<Iterator<const T>> rend() const
	{
		return std::reverse_iterator<Iterator<const T>>(begin());
	};

	void resize(const size_t& newSize)
	{
		if (newSize < length_)
			for (size_t i = newSize; i < length_; i++)
				alloc_.destroy(data_ + i);
		else
		{
			if (newSize > length_)
				if (newSize > size_)
					reserve(newSize);
			for (size_t i = length_; i < newSize; i++)
				alloc_.construct(data_ + i);
		}
		length_ = newSize;
	};

	void reserve(const size_t& newSize)
	{
		if (newSize > size_)
		{
			T* newData = alloc_.allocate(newSize);
			for (size_t i = 0; i < length_; i++)
			{
				alloc_.construct(newData + i, data_[i]);
				alloc_.destroy(data_ + i);
			}
			std::swap(data_, newData);
			alloc_.deallocate(newData, size_);
			size_ = newSize;
		}
	};

	void resize(size_t&& newSize)
	{
		if (newSize < length_)
			for (size_t i = newSize; i < length_; i++)
				alloc_.destroy(data_ + i);
		else
		{
			if (newSize > length_)
				if (newSize > size_)
					reserve(newSize);
			for (size_t i = length_; i < newSize; i++)
				alloc_.construct(data_ + i);
		}
		length_ = newSize;
	};

	void reserve(size_t&& newSize)
	{
		if (newSize > size_)
		{
			T* newData = alloc_.allocate(newSize);
			for (size_t i = 0; i < length_; i++)
			{
				alloc_.construct(newData + i, data_[i]);
				alloc_.destroy(data_ + i);
			}
			std::swap(data_, newData);
			alloc_.deallocate(newData, size_);
			size_ = newSize;
		}
	};
};
