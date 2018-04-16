#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#pragma once

#include <iostream>
#include <iterator>
#include <cassert>
#include <cstring>
#include <limits>

template <class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type size)
    {
        //pointer ptr = new value_type[size];
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
    T* ptr_;
public:
    using value_type = T;
    using size_type = size_t;
    using pointer = T*;
    using reference = T&;

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

    Iterator& operator+=(size_type n)
    {
        ptr_ += n;
        return *this;
    }

    Iterator& operator-=(size_type n)
    {
        ptr_ -= n;
        return *this;
    }

    Iterator operator+(size_type n) const
    {
        auto other = *this;
        return other.operator+=(n);
    }

    Iterator operator-(size_type n) const
    {
        auto other = *this;
        return other.operator-=(n);
    }


};

template <class T>
class Reverse_Iterator
    : public std::iterator<std::random_access_iterator_tag, T>
{
    T* ptr_;
public:
    using value_type = T;
    using size_type = size_t;
    using pointer = T*;
    using reference = T&;

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

    Reverse_Iterator& operator+=(size_type n)
    {
        ptr_ -= n;
        return *this;
    }

    Reverse_Iterator& operator-=(size_type n)
    {
        ptr_ += n;
        return *this;
    }

    Reverse_Iterator operator+(size_type n) const
    {
        auto other = *this;
        return other.operator+=(n);
    }

    Reverse_Iterator operator-(size_type n) const
    {
        auto other = *this;
        return other.operator-=(n);
    }
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
private:
    Alloc alloc_;
    size_t size_;
    size_t cap_;
    T* data_;

public:
    using iterator = Iterator<T>;
    using reverse_iterator = Reverse_Iterator<T>;
    using value_type = T;
    using size_type = size_t;
    using reference = T&;

    Vector(size_t initial_cap = 4):
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
        data_[size_++] = value;
    }

    pop_back()
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
                data_[i].~value_type();
            }
        }
        else{
            for(size_type i = size_; i < new_size; i++){
                data_[i] = value_type();
            }
        }
        size_ = new_size;
    }

    void reserve(size_type new_cap)
    {
        if((new_cap > cap_) && (new_cap <= alloc_.max_size())){
            auto new_data = alloc_.allocate(new_cap);
            std::memcpy(new_data, data_, sizeof(value_type) * size_);
            alloc_.deallocate(data_, cap_);
            std::swap(data_, new_data);
            cap_ = new_cap;
            return;
        }
        assert(!"Can't change capacity");
    }

    void clear()
    {
        resize(0);
    }

};


#endif // VECTOR_H_INCLUDED
