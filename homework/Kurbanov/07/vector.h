#pragma once
#include "allocator.h"
#include "Iterator.h"
#include <cstring>

template<class T, class Alloc = Allocator<T>, class iterator = Iterator<T>>
	class Vector {
	public:
		using size_type = size_t;
		using value_type = T;
		using pointer = T * ;
		using reference = T & ;

	private:
		Alloc _al;
		size_type _cap = 64;
		size_type size_ = 0;
		pointer _data;
	public:
		explicit Vector(size_type count)
		{
			if (count != 0) {
				_data = _al.allocate(count);
				size_ = count;
				_cap = count;
			}
		}

		explicit Vector()
		{
			_data = _al.allocate(_cap);
		}

		Iterator<T> begin() noexcept
		{
			return Iterator<T>(_data);
		}

		Iterator<T> end() noexcept
		{
			return Iterator<T>(_data + size_);
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
			return _data[id];
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
			return _cap;
		}

		void push_back(const value_type& value)
		{
			if (_cap == size_)
				reserve(_cap * 2);
			_data[size_] = value;
			size_++;
		}

		void pop_back()
		{
			resize(size_ - 1);
		}

		void reserve(size_type count)
		{
			if (count > _cap)
			{
				pointer newData = _al.allocate(count);
				memcpy(newData, _data, size_ * sizeof(value_type));
				std::swap(_data, newData);
				_al.deallocate(newData, size_);
				_cap = count;
			}
		}

		void resize(size_type newSize)
		{
			if (size_ < newSize)
			{
				if (_cap < newSize)
				{
					reserve(newSize);
				}
				for (size_type i = size_; i < newSize; i++)
					_data[i] = value_type();
			}
			else if (size_ > newSize)
			{
				for (size_type i = newSize; i < size_; i++)
					_data[i].~value_type();
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
		}
};
