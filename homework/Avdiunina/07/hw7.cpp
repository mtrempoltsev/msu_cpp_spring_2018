#include <iostream>
#include <limits>
#include <stdexcept>
#include <iterator>
#include <algorithm>

template <typename T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;
    using const_refer = const T&;

    void construct(pointer ptr)
    {
        ptr = new (ptr) T();
    }

    void construct(pointer ptr, const_refer val)
    {
        ptr = new (ptr) T(val);
    }

    void destroy(pointer ptr)
    {
        ptr->~T();
    }

    pointer allocate(size_type count)
    {
        if (count > max_size())
            throw std::bad_alloc();                                                            //std::length_error("Exceeds the maximum size allowed!");
        auto ptr = (pointer) malloc(count * sizeof(value_type));
        return ptr;
    }

    void deallocate(pointer ptr, size_type count)
    {
        ::operator delete(ptr);
    }

    size_t max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
};

template <typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{ T* ptr_;

public:
    using reference = T&;
    using size_type = size_t;

    explicit Iterator(T* ptr) : ptr_(ptr) {

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

    Iterator &operator++() {
        ++ptr_;
        return *this;
    }

    Iterator &operator--() {
        --ptr_;
        return *this;
    }

    Iterator operator+=(size_type n)
    {
        ptr_ += n;
        return *this;
    }

    Iterator operator-=(size_type n)
    {
        ptr_ -= n;
        return *this;
    }
};

template <typename T, typename Alloc = Allocator<T>>
class Vector
{
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = T*;
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using size_type = size_t;

private:
    Alloc alloc_;
    pointer data_;
    size_type size_ = 0;
    size_type capacity_ = 0;

public:
    explicit Vector(size_type count = 0)
    {
        if (count != 0)
        {
            data_ = alloc_.allocate(count);
            for (size_type i = 0; i < count; i++)
                alloc_.construct(data_ + i);
        }
        else
        {
            data_ = nullptr;
        }
        size_ = count;
        capacity_ = count;
    }

    reference operator[] (size_type n)
    {
        if (n >= size_)
            throw std::out_of_range("Error: OUT!");
        return data_[n];
    }

    void push_back(const_reference val)
    {
        if (size_ == capacity_) {
            reserve(2 * size_ + 1);
        }
        alloc_.construct(data_ + size_, val);
        size_++;
    }

    void pop_back()
    {
        if (size_ != 0)
            resize(size_ - 1);
    }

    bool empty() const
    {
        return size_ == 0;
    }

    size_type size() const
    {
        return size_;
    }

    size_type capacity() const
    {
        return capacity_;
    }

    iterator begin() noexcept
    {
        return iterator(data_);
    }

    iterator end() noexcept
    {
        return iterator(data_ + size_);
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }


    void reserve(size_type n)
    {
        if (n > capacity_)
        {
            pointer newData = alloc_.allocate(n);
            for (int i = 0; i < size_; ++i)
            {
                alloc_.construct(newData + i, data_[i]);
                alloc_.destroy(newData + i);
            }
            std::swap(data_, newData);
            alloc_.deallocate(newData, capacity_);

            capacity_ = n;
        }
    }

    void resize(size_type n)
    {
        if (n > size_)
        {
            reserve(n);
            for (size_type i = size_; i < n; i++)
                alloc_.construct(data_ + i);
        }
        else
        {
            for (size_type i = n; i < size_; i++)
                alloc_.destroy(data_ + i);
        }
        size_ = n;
    }


    void clear() noexcept {

        while (size_ > 0) {

            alloc_.destroy(data_ + size_);
            --size_;
        }
        size_ = 0;
    }

    ~Vector() {
        clear();
        alloc_.deallocate(data_, 0);
    }
};
