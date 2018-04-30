#include <limits>
#include <iterator>
#include <memory>
#include <algorithm>

template<class T>
class allocator
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
    void deallocate(pointer ptr, size_type count){
        free(ptr);
    }

    size_type max_size() const noexcept{

		return std::numeric_limits<size_type>::max();
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
};


template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:
    using reference = T&;
    explicit Iterator(T* ptr): ptr_(ptr) {}

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


template<class T, class Allocator = allocator<T>>
class Vector
{
public:
    using size_type = size_t;
	using value_type = T;
	using pointer = T*;
    using reference = T&;
    using iterator = Iterator<T>;

	Vector();
	Vector(size_type count);
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

//  begin, end, rbegin, rend
    iterator begin() noexcept;
    iterator end() noexcept;
    iterator rbegin()noexcept;
    iterator rend()noexcept;

    T& operator[](size_type i);
    const T& operator[](size_type i) const;
    void push_back(const reference value);
    void pop_back();
    void resize(size_type newSize);
    size_type size() const noexcept;
    void clear() noexcept;
    bool empty() const noexcept;

private:
    void reserve(size_type newSize);
    Allocator _alloc;
	pointer _array;
	size_type _size;
	size_type _capacity;
};

template<class T>
Vector<T>::Vector()
  : _capacity(4)
  , _array(_alloc.allocate(4))
  , _size(0)
{
}

template<class T>
Vector<T>::Vector(size_type count)
  : _capacity(count)
  , _array(alloc.allocate(count))
  , _size(count)
{
    for (size_type i = 0; i < count; i++)
        alloc_.construct(data_ + i);
}

template<class T>
Vector<T>::Vector(const Vector<T> & other)
: _capacity(other._capacity)
, _size(other._size)
, _array(other._array)
{
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector<T> & other)
{
	if (this != &other) {
		newData = alloc.allocate(other._capacity);
        std::copy(other._array , other._array + other._size, newData);
        std::swap(_array , newData);
        alloc_.deallocate(newData, other._size); // нужно ли это делать или оно и так удалит правильно newData?
		_capacity = other._capacity;
		_size = other._size;
	}
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
		clear();
		alloc_.deallocate(data_, 0);
}

template<class T>
iterator Vector<T>::begin() noexcept
{
    return Iterator<T>(_data);
}

template<class T>
iterator Vector<T>::end() noexcept
{
    return Iterator<T>(_data + _size);
}

template<class T>
std::reverse_iterator<Iterator<T>> Vector<T>::rbegin() noexcept
{
    return std::reverse_iterator<Iterator<T>>(end());
}

template<class T>
std::reverse_iterator<Iterator<T>> Vector<T>::rend() noexcept
{
    return std::reverse_iterator<Iterator<T>>(begin());
}

template<class T>
reference Vector<T>::operator[](size_type i)
{
	return _array[i];
}

template<class T>
const reference Vector<T>::operator[](size_type i) const
{
	return _array[i];
}

template<class T>
void Vector<T>::push_back (const reference x) {
        if (_size == _capacity) {
            if (size_ == 0)
                reserve(1);
            else
                reserve(_size * 2);
        }
        _alloc.construct(_array + _size, x);
        _size++;

}

template<class T>
void Vector<T>::pop_back()
{
	if (_size > 0) {
		resize(_size - 1);;
	}
}

template<class T>
size_type Vector<T>::size() const noexcept
{
	return _size;
}

template<class T>
void Vector<T>::reserve(size_type newSize)
{
    if (newSize > _capacity)
		{
			pointer newData = alloc_.allocate(newSize);
			std::copy(_array, _array + _size, newData);
			std::swap(_array, newData);
			alloc_.deallocate(newData, _size);
			_capacity = newSize;
        }
}

template<class T>
void Vector<T>::resize(size_type newSize)
{
    if (newSize < _size){
        for (size_type i = newSize; i < _size; i++)
            _alloc.destroy(_array + i);
    }else if (newSize > _size){
        if(newSize > _capacity){
            reserve(newSize)
        }
        for (size_type i = _size; i < newSize; i++)
            _alloc.construct(_array + i);
    }
    _size = newSize;
}

template<class T>
void Vector<T>::clear() noexcept
{
    resize(0);
}

template<class T>
bool Vector<T>::empty() const noexcept
{
    return size_ == 0;
}
