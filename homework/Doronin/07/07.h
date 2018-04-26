#pragma once
#include <iostream>
#include <iterator>
#include <limits>
template <class T>
class Allocator
{
public:

    void construct(T* ptr) {
        ptr = new (ptr) T();
    }

    void construct(T* ptr, const T& val) {
        ptr = new (ptr) T(val);
    }

    void construct(T* ptr, T&& val) {
        ptr = new (ptr) T(std::move(val));
    }

    void destroy(T* ptr) {
        ptr->~T();
    }


    T* allocate(size_t count=1024)
    {
        T* ptr = (T*) malloc(sizeof(T) * count);
        return ptr;
    }

    void deallocate(T* ptr)
    {
        free(ptr);
    }

    size_t max_size() const noexcept
    {
        return std::numeric_limits<size_t>::max();
    }
};

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
    T* _ptr;
public:
    Iterator(T* ptr):
    _ptr(ptr)
    {}

    bool operator==(const Iterator<T> &that) const
    {
        return that._ptr == _ptr;
    }

    bool operator!=(const Iterator<T> &that) const
    {
        return !(that == *this);
    }

    T& operator*() const
    {
        return *_ptr;
    }

    Iterator& operator++()
    {
        ++_ptr;
        return *this;
    }

    Iterator& operator--()
    {
        --_ptr;
        return *this;
    }
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using type = T;

    Vector(size_t size = 0)
    {
        _data = alloc_.allocate(_capacity);
        _size = size;
    }

    ~Vector()
    {
        clear();
        alloc_.deallocate(_data);
    }

    const T& operator[](size_t i) const
    {
        return _data[i];
    }

    T& operator [](size_t i)
    {
        return _data[i];
    }


    void pop_back()
    {
        if(_size > 0)
            resize(_size-1);
    }

    void push_back(T&& elem)
    {
        if(_size != _capacity)
        {
            alloc_.construct(_data + _size, std::move(elem));
            _size++;
        }
        else
        {
            this->reserve(2*_capacity);
            alloc_.construct(_data + _size, std::move(elem));
            _size++;
        }
    }

    void push_back(const T& elem)
    {
        if(_size != _capacity)
        {
            alloc_.construct(_data+_size, elem);
            _size++;
        }
        else
        {
            this->reserve(2*_capacity);
            alloc_.construct(_data+_size, elem);
            _size++;
        }
    }

    bool empty() const noexcept
    {
        return _size == 0;
    }

    size_t size() const noexcept
    {
        return _size;
    }

    void clear() noexcept
    {
        resize(0);
    }

    iterator begin() noexcept
    {
        return iterator(_data);
    }

    const_iterator begin() const noexcept
    {
        return const_iterator(_data);
    }

    iterator end() noexcept
    {
        return iterator(_data+_size);
    }

    const_iterator end() const noexcept
    {
        return const_iterator(_data+_size);
    }

    std::reverse_iterator<iterator> rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    std::reverse_iterator<const_iterator>rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    std::reverse_iterator<iterator> rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    std::reverse_iterator<const_iterator> rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    void reserve(size_t new_size)
    {
        if(new_size > _capacity)
        {
            T* newData = alloc_.allocate(new_size);
            std::copy(_data, _data + _size, newData);
            std::swap(_data, newData);
            alloc_.deallocate(newData);
            _capacity = new_size;
        }
    }

    void resize(size_t new_size)
    {

        if(_capacity < new_size)
        {
            reserve(new_size);
        }
        if (new_size < _size)
        {
            for (size_t i = new_size; i < _size; i++)
                alloc_.destroy(_data+i);
        }
        if (new_size > _size)
        {
            for (size_t i = _size; i < new_size; i++)
                alloc_.construct(_data+i);
        }
        _size = new_size;
    }

    size_t capacity() const noexcept
    {
        return _capacity;
    }

private:
    Alloc alloc_;
    size_t _capacity = 1024;
    size_t _size = 0;
    T* _data = nullptr;
};