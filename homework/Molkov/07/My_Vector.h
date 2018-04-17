#include <limits>
#include <iterator>
#include <memory>

template<class T>
class allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;

	pointer allocate(size_type count) {
		pointer p = new T[count];
		return p;
	}
	void deallocate(pointer ptr, size_type count) {
		delete[] ptr;
	}

	size_t max_size() const noexcept {
		return std::numeric_limits<size_type>::max();
	}
};


template <class T>
class Iterator
	: public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:
	using reference = T&;

	explicit Iterator(T* ptr)
		: ptr_(ptr)
	{
	}

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


template<class T,
	class Alloc = std::allocator<T>>
class Vector {
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	explicit Vector(size_type count)
	{
		if (count != 0) {
			data_ = alloc_.allocate(count);
			size_ = count;
			capacity_ = count;
		}
	}

	explicit Vector()
	{
		data_ = alloc_.allocate(capacity_);
	}
	//Vector(size_type count, const value_type& defaultValue);

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

	reference operator[] (size_type id)
	{
		return data_[id];
	}

	bool empty() const noexcept 
	{
		if (size_ == 0)
			return true;
		return false;
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
			reserve(capacity_ * 2);
		data_[size_] = value;
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
			memcpy(newData, data_, size_ * sizeof(value_type));
			std::swap(data_, newData);
			alloc_.deallocate(newData, size_);
			capacity_ = count;
		}
	}

	//void resize(size_type newsize, const value_type& defaultValue);
	void resize(size_type newSize)
	{
		if (size_ < newSize)
		{
			if (capacity_ < newSize) 
			{
				reserve(newSize);
			}
			for (size_type i = size_; i < newSize; i++)
				data_[i] = value_type();
		}
		else if (size_ > newSize)
		{
			for (size_type i = newSize; i < size_; i++)
				data_[i].~value_type();
		}
		size_ = newSize;
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
	Alloc alloc_;
	size_type capacity_ = 32;
	size_type size_ = 0;
	pointer data_;
};