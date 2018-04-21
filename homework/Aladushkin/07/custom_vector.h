#pragma once

#include <limits>
#include <iterator>
#include <memory>

template<class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;

	pointer allocate(size_type count)
	{
		pointer ptr = (pointer)malloc(sizeof(value_type) * count);
		return ptr;
	}

	void deallocate(pointer ptr, size_type count)
	{
		free(ptr);
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

	size_t max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
	}
};


template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:
	using reference = T&;

	explicit Iterator(T* ptr) : ptr_(ptr)
	{}

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

	Iterator& operator+(size_t& val)
	{
		ptr_ += val;
		return *this;
	}

	Iterator& operator-(size_t& val)
	{
		ptr_ -= val;
		return *this;
	}
};

template<class T, class allocator = Allocator<T>>
class Vector
{
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	explicit Vector(size_type count)
	{
		if (count != 0)
		{
			data_ = allocator_.allocate(count);
			size_ = count;
			capacity_ = count;
		}
	}

	explicit Vector()
	{
		data_ = allocator_.allocate(capacity_);
	}

	~Vector()
	{
		clear();
		allocator_.deallocate(data_, 0);
	}

	Iterator<T> begin() noexcept {return Iterator<T>(data_);}
	Iterator<T> end() noexcept   {return Iterator<T>(data_ + size_);}

	std::reverse_iterator<Iterator<T>> rbegin() noexcept {return std::reverse_iterator<Iterator<T>>(end());}
	std::reverse_iterator<Iterator<T>> rend() noexcept   {return std::reverse_iterator<Iterator<T>>(begin());}

	reference operator[] (size_type index)	       {return data_[index];}
	const reference operator[](size_t index) const {return data_[index];}

	size_type size() const noexcept { return size_; }
	size_type capacity() const noexcept { return capacity_; }

	void reserve(size_type count)
	{
		if (count > capacity_)
		{
			pointer newData = allocator_.allocate(count);
			//std::copy(data_, data_ + size_, newData);
			memcpy(newData, data_, size_ * sizeof(value_type));
			data_ = std::move(newData);
			capacity_ = count;
		}
	}

	void resize(size_type new_size)
	{
		if (size_ < new_size)
		{
			if (capacity_ < new_size)
			{
				reserve(new_size);
			}

			for (size_type i = size_; i < new_size; i++)
				allocator_.construct(data_ + i);
		}
		else if (size_ > new_size)
		{
			for (size_type i = new_size; i < size_; i++)
				allocator_.destroy(data_ + i);
		}

		size_ = new_size;
	}

	void push_back(const value_type& value)
	{
		if (capacity_ == size_)
			reserve(capacity_ * 2);

		allocator_.construct(data_ + size_, value);
		size_++;
	}

	void pop_back()
	{
		resize(size_ - 1);
	}

	void clear() noexcept
	{
		resize(0);
	}

	bool empty() const noexcept 
	{
		return size_ == 0;
	}

private:
	allocator allocator_;
	size_type capacity_ = 100;
	size_type size_ = 0;
	pointer data_;
};