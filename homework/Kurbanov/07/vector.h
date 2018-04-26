#pragma once
#include "allocator.h"
#include "Iterator.h"
#include <cstring>
template<class T, class Alloc = Allocator<T>, class iterator = Iterator<T>>
	class Vector 
	{
	public:
		using size_type = size_t;
		using value_type = T;
		using pointer = T* ;
		using reference = T & ;

	private:
		Alloc _al;
		size_type _cap = 64;
		size_type _size = 0;
		pointer _data;
	public:
		explicit Vector(size_type count)
		{
			if (count != 0) {
				_data = _al.allocate(count);
				_size = count;
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
			return Iterator<T>(_data + _size);
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
			if (_size == 0)
				return true;
			return false;
		}

		size_type size() const noexcept
		{
			return _size;
		}

		size_type capacity() const noexcept
		{
			return _cap;
		}

		void push_back(const value_type& value)
		{
			if (_cap == _size)
				reserve(_cap * 2);
			_al.construct(_data + (_size++), value);
		}

		void pop_back()
		{
			resize(_size - 1);
		}

		void reserve(size_type count)
		{
			if (_size < count)
			{
				auto newData = _al.allocate(count);
				std::memcpy(newData, _data, sizeof(value_type) * _size);
				_al.deallocate(_data, _cap);
				std::swap(_data, newData);
				_cap = count;
				return;
			}

			throw std::length_error("Can't reduce memory capacity of Vector");
		}
	void resize(size_type newSize)
		{
		if (newSize > _cap)
			reserve(newSize);
		if (newSize < _size) {
			for (size_type i = newSize; i < _size; i++) 
			{
				_al.destroy(_data+i);
			}
		}
		else {
			for (size_type i = _size; i < newSize; i++) 
			{
				_al.construct(_data+i);
			}
		}
		_size = newSize;
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
