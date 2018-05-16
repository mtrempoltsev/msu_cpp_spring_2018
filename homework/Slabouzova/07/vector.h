#include <iostream>
#include <stdexcept>
#include <utility>
#include <limits>
#include <cstring>


template<class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

	pointer allocate(size_type count){ 
		pointer ptr = (pointer) malloc(sizeof(value_type) * count); 
		return ptr; 
	} 

	void deallocate(pointer ptr){ 
		free(ptr); 
	};


	void construct(pointer ptr)
	{ 
		ptr = new(ptr) value_type(); 
	}

	void construct(pointer ptr, const value_type &init_val)
	{ 
		ptr = new(ptr) value_type(init_val); 
	} 

    void destroy(pointer ptr)
    {
        ptr->~value_type();
    }

    size_t max_size() const noexcept
    {
    	return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
};

template <class T>
class Iterator
{
	T* pointer;
public:
	Iterator(T* pointer) :
		pointer(pointer)
	{ }

	T& operator*()
	{
		return *pointer;
	}

	const T& operator*() const
	{
		return *pointer;
	}

	Iterator& operator++()
	{
		pointer++;
		return *this;
	}

	Iterator& operator--()
	{
		pointer--;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator iter(pointer);
		pointer++;
		return iter;
	}

	Iterator operator--(int)
	{
		Iterator iter(pointer);
		pointer--;
		return iter;
	}

	Iterator operator+(size_t n) const
	{
		return Iterator(pointer + n);
	}

	Iterator operator-(size_t n) const
	{
		return Iterator(pointer - n);
	}

	bool operator==(const Iterator<T> &other)
	{ 
		return pointer == other.pointer; 
	} 

	bool operator!=(const Iterator<T> &other) const
	{ 
		return pointer != other.pointer; 
	}


};



template <class T>
class ReverseIterator
{
	T* pointer;
public:
	ReverseIterator(T* pointer) :
		pointer(pointer)
	{ }

	T& operator*()
	{
		return *pointer;
	}

	const T& operator*() const
	{
		return *pointer;
	}

	ReverseIterator& operator++()
	{
		pointer--;
		return *this;
	}

	ReverseIterator& operator--()
	{
		pointer++;
		return *this;
	}

	ReverseIterator operator++(int)
	{
		ReverseIterator iter(pointer);
		pointer--;
		return iter;
	}

	ReverseIterator operator--(int)
	{
		ReverseIterator iter(pointer);
		pointer++;
		return iter;
	}

	ReverseIterator operator+(size_t n) const
	{
		return ReverseIterator(pointer - n);
	}

	ReverseIterator operator-(size_t n) const
	{
		return ReverseIterator(pointer + n);
	}

	bool operator==(const ReverseIterator<T> &other)
	{ 
		return pointer == other.pointer; 
	} 

	bool operator!=(const ReverseIterator<T> &other) const
	{ 
		return pointer != other.pointer; 
	}
};




template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;
    using reverse_iterator = ReverseIterator<T>;
    using size_type = size_t;
    using value_type = T;
    using pointer = T*;

private:
	T* buffer;
	size_type size_;
	size_type capacity_;
    Alloc alloc_;

public:

	Vector(size_type capacity = 10) :
		capacity_(capacity),
		size_(0)
	{ 
		buffer = alloc_.allocate(capacity_);
	}

	~Vector()
	{ 
		for(int i = 0; i < size_; i++) {
			alloc_.destroy(buffer+i);
		}
		alloc_.deallocate(buffer);
		size_ = 0;
		capacity_ = 0;
	}

	iterator begin()
	{
		return iterator(buffer);
	}

	const iterator begin() const 
	{
		return iterator(buffer);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(buffer + size_ - 1);
	}

	const reverse_iterator rbegin() const 
	{
		return reverse_iterator(buffer + size_ - 1);
	}

	iterator end()
	{
		return iterator(buffer + size_);
	}

	const iterator end() const 
	{
		return iterator(buffer + size_ );
	}

	reverse_iterator rend()
	{
		return reverse_iterator(buffer - 1);
	}

	const reverse_iterator rend() const 
	{
		return reverse_iterator(buffer - 1);
	}

	size_t size() const
	{
		return size_;
	}

	bool empty() const
	{
		return (size_ == 0);
	}

	T& operator[](size_t i)
	{
		if (i >= size_)
			throw std::out_of_range ("check operator[]");
		return buffer[i];
	}

	const T& operator[](size_t i) const
	{
		if (i >= size_)
			throw std::out_of_range ("check operator[]");
		return buffer[i];
	}

    void reserve(size_type new_capacity)
    {

		if (capacity_ < new_capacity) { 
			T* new_data = alloc_.allocate(new_capacity); 
			std::memcpy(new_data, buffer, size_ * sizeof(T)); 
			std::swap(buffer, new_data); 
			alloc_.deallocate(new_data); 
			capacity_ = new_capacity; 
		}

    }


	void resize(size_type new_size)
	{
        if (new_size > capacity_) {
            reserve(new_size);
        }
        
        for(int i = size_; i < new_size; i++)
            alloc_.construct(buffer + i);
        
        for(int i = new_size; i < size_; i++)
            alloc_.destroy(buffer + i);

        size_ = new_size;
	}

	void push_back(const value_type& el)
	{ 
		if (size_ == capacity_) 
			reserve(capacity_ * 2); 
		alloc_.construct(buffer + size_, el);
		size_++; 
	} 

	void push_back(value_type&& el)
	{ 
		if (size_ == capacity_) 
			reserve(capacity_ * 2); 
		alloc_.construct(buffer + size_, std::move(el));
		size_++; 
	} 

	void pop_back()
	{
		resize(size_-1);	
	}

	void clear()
	{
		resize(0);
	}

	size_type capacity()
	{
		return capacity_;
	}
};
