#pragma once

#include <iterator>
#include <limits>
#include <stdlib.h>
#include <memory>
#include <stdexcept>
#include <new>

template <class T>
class Allocator
{
public:
    template<class U, class... Args> static void construct(U *p, Args&&... args) {
        new(reinterpret_cast<void *>(p)) U(std::forward<Args>(args)...);
    }

    template<class U> static void destroy(U * p) { p->~U(); }

    template<class... Args> static T* allocate(const size_t count, Args&&... args) {
        if (count == 0) {
            return nullptr;
        }

        auto memory = static_cast<T*>(operator new[] (count * sizeof(T)));

        for (int i = 0; i < count; ++i) {
            construct(memory + i, std::forward<Args>(args)...);
        }

        return memory;
    }

    static void deallocate(T* ptr, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            destroy(ptr + i);
        }

        operator delete[] (ptr);
    }

    static size_t max_size() noexcept { return std::numeric_limits<size_t>::max(); }
};

template <class T>
class Iterator : public std::iterator<std::input_iterator_tag, T>
{
    T* p;
public:
    Iterator(T* x) : p (x) {}
    Iterator(const Iterator& mit) : p(mit.p) {}

    Iterator& operator++() {
        ++p;
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp(*this);
        operator++();
        return tmp;
    }

    Iterator& operator--() {
        --p;
        return *this;
    }

    Iterator operator--(int) {
        Iterator tmp(*this);
        operator--();
        return tmp;
    }

    bool operator==(const Iterator& rhs) const {return p==rhs.p;}
    bool operator!=(const Iterator& rhs) const {return p!=rhs.p;}

    T& operator*() { return *p; }
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;

    Vector(const size_t capacity = 0) : capacity_(capacity), data_(alloc_.allocate(capacity)), size_(0) {}

    ~Vector() { clear(); alloc_.deallocate(data_, size_); }

    iterator begin() noexcept { return iterator(data_); }
    iterator end() noexcept { return iterator(data_ + size_); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    bool empty() const noexcept { return size_ == 0; }
    size_t capacity() const noexcept { return capacity_; }
    size_t size() const noexcept { return size_; }

    T& operator[] (const size_t i) {
        if (i >= size_) {
            throw std::out_of_range("Index is out range in vector");
        }
        return data_[i];
    }

    const T& operator[] (const size_t i) const {
        if (i >= size_) {
            throw std::out_of_range("Index is out range in vector");
        }
        return data_[i];
    }

    void pop_back() {
        if (size_ > 0) {
            resize(size_ - 1);
        }
    }

    void push_back (const T& val)
    {
        if (size_ + 1 > capacity_)
        {
            safe_allocation(size_ + 1, val);
            capacity_ = size_ + 1;
            size_ = capacity_;
        } else {
            data_[size_] = val;
            ++size_;
        }
    }

    void reserve(const size_t size)
    {
        if (size > capacity_)
        {
            safe_allocation(size);
            capacity_ = size;
        }
    }

    void resize(const size_t newSize)
    {
        if (size_ < newSize)
        {
            if (capacity_ >= newSize) {
                for (size_t i = size_; i < newSize; ++i) {
                    alloc_.construct(data_ + i);
                }
                size_ = newSize;
                return;
            }

            safe_allocation(newSize);
            size_ = newSize;
            capacity_= newSize;
        } else {
            for (size_t i = newSize; i < size_; ++i) {
                alloc_.destroy(data_ + i);
            }

            size_ = newSize;
        }
    }

    void clear() { resize(0); }

private:
    void safe_allocation(const size_t size)
    {
        auto newData = alloc_.allocate(size);
        std::memcpy(newData, data_, size_ * sizeof(T));
        std::swap(newData, data_);
        alloc_.deallocate(newData, size_);
    }

    void safe_allocation(const size_t size, const T& value)
    {
        auto newData = alloc_.allocate(size, value);
        std::memcpy(newData, data_, size_ * sizeof(T));
        std::swap(newData, data_);
        alloc_.deallocate(newData, size_);
    }

    T* data_;
    size_t size_;
    size_t capacity_;

    Alloc alloc_;
};
