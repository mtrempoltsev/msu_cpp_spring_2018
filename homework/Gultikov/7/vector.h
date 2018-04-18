#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#pragma once

#include <iterator>
#include <stdexcept>
#include <cstring>
#include <limits>

template <class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

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

    pointer allocate(size_type size)
    {
        if(size > max_size())
            throw std::length_error("Not enougth memory");
        pointer ptr = (pointer) malloc(sizeof(value_type) * size);
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

template <class T>
class Iterator
    : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    using size_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
    using pointer = typename std::iterator<std::random_access_iterator_tag, T>::pointer;
    using reference = typename std::iterator<std::random_access_iterator_tag, T>::reference;

    explicit Iterator(pointer ptr)
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

private:
    pointer ptr_;

};

template <class T>
class Reverse_Iterator
    : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    using size_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
    using pointer = typename std::iterator<std::random_access_iterator_tag, T>::pointer;
    using reference = typename std::iterator<std::random_access_iterator_tag, T>::reference;

    explicit Reverse_Iterator(pointer ptr)
        : ptr_(ptr)
    {
    }

    bool operator==(const Reverse_Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Reverse_Iterator<T>& other) const
    {
        return !(*this == other);
    }

    reference operator*() const
    {
        return *ptr_;
    }

    Reverse_Iterator& operator++()
    {
        --ptr_;
        return *this;
    }

    Reverse_Iterator& operator--()
    {
        ++ptr_;
        return *this;
    }

private:
    pointer ptr_;
};

template <class T, class Alloc = Allocator<T>, class iterator = Iterator<T>, class reverse_iterator = Reverse_Iterator<T>>
class Vector
{

public:
    using value_type = typename Alloc::value_type;
    using pointer = typename Alloc::pointer;
    using size_type = typename Alloc::size_type;
    using reference = typename iterator::reference;

    Vector(size_type initial_cap = 4):
        alloc_(),
        size_(0),
        cap_(initial_cap),
        data_(alloc_.allocate(cap_))
    {
    }

    ~Vector()
    {
        clear();
        alloc_.deallocate(data_, cap_);
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
        return reverse_iterator(data_ + size_ - 1);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(data_ - 1);
    }

    bool empty()
    {
        return (size_ == 0);
    }

    size_type size()
    {
        return size_;
    }

    size_type capacity()
    {
        return cap_;
    }

    void push_back(const value_type& value)
    {
        if(size_ >= cap_)
            reserve(2 * cap_);
        alloc_.construct(data_ + (size_++), value);
    }

    void pop_back()
    {
        if(size_ > 0)
            resize(size_ - 1);
    }

    void resize(size_type new_size)
    {
        if(new_size > cap_)
            reserve(new_size);

        if(new_size < size_){
            for(size_type i = new_size; i < size_; i++){
                alloc_.destroy(data_ + i);
            }
        }
        else{
            for(size_type i = size_; i < new_size; i++){
                alloc_.construct(data_ + i);
            }
        }
        size_ = new_size;
    }

    void reserve(size_type new_cap)
    {
        if(new_cap > cap_){
            auto new_data = alloc_.allocate(new_cap);
            std::memcpy(new_data, data_, sizeof(value_type) * size_);
            alloc_.deallocate(data_, cap_);
            std::swap(data_, new_data);
            cap_ = new_cap;
            return;
        }
        throw std::length_error("Can't reduce memory capacity of Vector");
    }

    void clear()
    {
        resize(0);
    }

private:
    Alloc alloc_;
    size_type size_;
    size_type cap_;
    pointer data_;
};


#endif // VECTOR_H_INCLUDED
