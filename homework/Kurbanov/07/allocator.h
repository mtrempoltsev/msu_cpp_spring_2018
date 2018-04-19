#include<iostream>
#include <memory>
#include <stdexcept>

template <class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T* ;
	using size_type = size_t;

	pointer allocate(size_type size)
	{
		if (size > max_size())
			throw std::length_error("Not enougth memory");
		pointer ptr = (pointer)malloc(sizeof(value_type) * size);
		return ptr;
	}

	void deallocate(pointer ptr, size_type count)
	{
		free(ptr);
	}

	size_type max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
	}
};
