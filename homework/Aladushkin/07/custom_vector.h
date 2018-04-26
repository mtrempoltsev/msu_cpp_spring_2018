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
		data_ = alloc_.allocate(count);
		size_ = count;
		capacity_ = count;
	}

	explicit Vector()
	{
		data_ = alloc_.allocate(capacity_);
	}

	Iterator<T> begin() noexcept
	{
		return Iterator<T>(data_);
	}

	Iterator<T> end() noexcept
	{
		return Iterator<T>(data_ + size_);
	}

	std::reverse_iterator<Iterator<T>> rbegin() noexcept
	{
		return std::reverse_iterator<Iterator<T>>(end());
	}

	std::reverse_iterator<Iterator<T>> rend() noexcept
	{
		return std::reverse_iterator<Iterator<T>>(begin());
	}

	reference operator[] (size_type index)
	{
		return data_[index];
	}

	const reference operator[](size_t index) const
	{
		return data_[index];
	}

	bool empty() const noexcept
	{
		return size_ == 0;
	}

	size_type size() const noexcept
	{
		return size_;
	}

	size_type capacity() const noexcept
	{
		return capacity_;
	}

	void push_back(const value_type& value)
	{
		if (capacity_ == size_)
			reserve(capacity_ * 2 + 1);

		alloc_.construct(data_ + size_, value);
		size_++;
	}

	void pop_back()
	{
		resize(size_ - 1);
	}

	void reserve(size_type count)
	{
		if (count > capacity_)
		{
			pointer newData = alloc_.allocate(count);
			for (int i = 0; i < size_; i++)
				alloc_.construct(newData + i, data_[i]);

			for (size_type i = 0; i < size_; i++)
				alloc_.destroy(data_ + i);
			alloc_.deallocate(data_, size_);

			data_ = newData;
			capacity_ = count;
		}
	}

	void resize(size_type new_size)
	{
		if (new_size > size_)
		{
			if (capacity_ < new_size)
			{
				reserve(new_size);
			}

			for (size_type i = size_; i < new_size; i++)
				alloc_.construct(data_ + i);
		}
		else if (new_size < size_)
		{
			for (size_type i = new_size; i < size_; i++)
				alloc_.destroy(data_ + i);
		}

		size_ = new_size;
	}

	void clear() noexcept
	{
		resize(0);
	}

	~Vector()
	{
		clear();
		alloc_.deallocate(data_, 0);
	}

private:
	allocator alloc_;
	size_type capacity_;
	size_type size_ = 0;
	pointer data_;
};