#include <limits>
#include <iterator>
#include <memory>
template <class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;

	void construct(pointer ptr)
	{
		ptr = new (ptr) value_type();
	}

	void construct(pointer ptr, const value_type& v)
	{
		ptr = new (ptr) value_type(v);
	}

	void construct(T* ptr, T&& v)
	{
		ptr = new (ptr) T(std::move(v));
	}

	void destroy(pointer ptr)
	{
		ptr->~value_type();
	}

	pointer allocate(size_type count)
	{
		pointer ptr = (pointer)malloc(sizeof(value_type) * count);
		return ptr;
	}
	void deallocate(pointer ptr, size_type count)
	{
		free(ptr);
	}
	size_t max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
	}
};

template <class T>
class Iterator
	: public std::iterator<std::forward_iterator_tag, T>
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
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	explicit Vector()
	{
		data_ = alloc_.allocate(capacity_);
	}

	explicit Vector(size_type count)
	{
		if (count)
		{
			data_ = alloc_.allocate(count);
			for (size_type i = 0; i < count; i++)
			{
				alloc_.construct(data_ + i);
			}
			size_ = count;
			capacity_ = count;
		}
	}
	explicit Vector(size_type count, const value_type& v)
	{
		if (count)
		{
			data_ = alloc_.allocate(count);
			for (int i = 0; i < count; i++)
			{
				alloc_.construct(data_ + i, v);
			}
			size_ = count;
			capacity_ = count;
		}
	}

	reference operator[] (size_type pos)
	{
		return data_[pos];
	}

	void push_back(const value_type& value)
	{
		if (capacity_ == size_)
		{
			if (size_ == 0)
			{
				reserve(1);
			}
			else
			{
				reserve(capacity_ * 2);
			}
		}
		alloc_.construct(data_ + size_, value);
		size_++;
	}

	void pop_back()
	{
		resize(size_ - 1);
	}

	bool empty() const noexcept
	{
		if (size_ != 0)
		{
			return false;
		}
		return true;
	}

	size_type size() const noexcept
	{
		return size_;
	}

	void clear() noexcept
	{
		resize(0);
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

	void resize(size_type newSize)
	{
		if (size_ > newSize)
		{
			for (size_type i = newSize; i < size_; i++)
			{
				alloc_.destroy(data_ + i);
			}
		}
		if (size_ < newSize)
		{
			if (capacity_ < newSize)
			{
				reserve(newSize);
			}
			for (size_type i = size_; i < newSize; i++)
			{
				alloc_.construct(data_ + i);
			}
		}
		size_ = newSize;
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

	size_type capacity() const noexcept
	{
		return capacity_;
	}

	~Vector()
	{
		clear();
		alloc_.deallocate(data_, 0);
	}
private:
	Alloc alloc_;
	size_type capacity_ = 0;
	size_type size_ = 0;
	pointer data_;
};
