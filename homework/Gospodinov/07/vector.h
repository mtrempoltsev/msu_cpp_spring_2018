#pragma once

#include <iterator>
#include <stdexcept>
#include <limits>

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
	using size_type = size_t;
	using pointer = T*;
	using reference = T&;

	Iterator(pointer p) : p_(p) {}

	Iterator(const Iterator& it) : p_(it.p_) {}

	bool operator==(const Iterator& it)
	{
		return p_ == it.p_;
	}

	bool operator!=(const Iterator& it)
	{
		return p_ != it.p_;
	}

	Iterator operator++()
	{
		++p_;
		return *this;
	}

	Iterator operator+=(size_type n)
	{
		p_ += n;
		return *this;
	}

	Iterator operator--()
	{
		--p_;
		return *this;
	}

	Iterator operator-=(size_type n)
	{
		p_ -= n;
		return *this;
	}

	reference operator*()
	{
		return *p_;
	}

private:
	pointer p_;
};

template <class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;

	void construct(pointer p) 
	{
		p = new (p) value_type();
	}

	void construct(pointer p, const value_type& value) 
	{
		p = new (p) value_type(value);
	}
	
	void construct(pointer p, value_type&& value)
	{
		p = new (p) value_type(std::move(value));
	}
	
	void destruct(pointer p)
	{
		p->~value_type();
	}

	pointer allocate(size_type count) 
	{
		if (count > max_size())
			throw std::bad_alloc();
		pointer p = (pointer)malloc(sizeof(value_type) * count);
		return p;
	}

	void deallocate(pointer p, size_type count) 
	{
		free(p);
	}

	size_type max_size()
	{
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using size_type = size_t;
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using iterator = Iterator<T>;
	using reverse_iterator = std::reverse_iterator<iterator>;

	Vector()
	{
		data_ = allocator_.allocate(capacity_);
	}

	Vector(size_type count)
	{
		data_ = allocator_.allocate(count);
		for (size_type i = 0; i < count; i++)
			allocator_.construct(data_ + i);
		size_ = count;
		capacity_ = count;
	}

	void reserve(size_type count)
	{
		if (count > capacity_)
		{
			pointer newData = allocator_.allocate(count);
			for (size_type i = 0; i < size_; i++)
			{
				allocator_.construct(newData + i, data_[i]);
				allocator_.destruct(data_ + i);
			}

			std::swap(data_, newData);
			allocator_.deallocate(newData, size_);

			capacity_ = count;
		}
	}

	void resize(size_type newSize)
	{
		if (newSize > size_)
		{
			reserve(newSize);
			for (size_type i = size_; i < newSize; i++)
				allocator_.construct(data_ + i);
		}
		else
		{
			for (size_type i = newSize; i < size_; i++)
				allocator_.destruct(data_ + i);
		}
		size_ = newSize;
	}

	~Vector()
	{
		resize(0);
		allocator_.deallocate(data_, 0);
	}

	size_type capacity()
	{
		return capacity_;
	}

	size_type size()
	{
		return size_;
	}

	bool empty()
	{
		return size_ == 0;
	}

	void clear()
	{
		resize(0);
	}

	reference at(size_type i) 
	{
		if (i < size_)
			return data_[i];
		throw std::out_of_range();
	}

	reference operator[](size_type i)
	{
		return data_[i];
	}

	iterator begin()
	{
		return iterator(data_);
	}

	iterator end() 
	{
		return iterator(data_ + size_);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend() 
	{
		return reverse_iterator(begin());
	}

	void push_back(const value_type& val) 
	{
		if (size_ == capacity_) 
			reserve(2 * size_ + 1);
		allocator_.construct(data_ + size_, val);
		size_++;
	}

	void pop_back() 
	{
		resize(size_ - 1);
	}

private:
	Alloc allocator_;
	pointer data_;
	size_type size_ = 0;
	size_type capacity_ = 32;
};