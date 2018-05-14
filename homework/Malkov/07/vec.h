#pragma once

#include <iterator>
#include <algorithm>


template <class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T *;
    using size_type = size_t;

    pointer allocate(size_type count)
    {
        if (count > max_size()) {
            throw std::invalid_argument("size <= max size!");
        }
        return static_cast<pointer>(::operator new(count * sizeof(value_type)));
    }

    void deallocate(pointer ptr, size_type count)
    {
        ::operator delete(ptr);
    }

    template <class... Args>
    void construct(T *ptr, Args&&... args)
    {
        ::new (ptr) T(std::forward<Args>(args)...);
    }

    void destroy(pointer ptr)
    {
        ptr->~T();
    }

    size_type max_size() const noexcept
    {
        return (static_cast<size_type>(0) - static_cast<size_type>(1)) / sizeof(T);
    }
};


template <class T>
class Iterator : public std::iterator<std::forward_iterator_tag, T>
{
private:
    T *ptr_;

public:
    using reference = T&;

    explicit Iterator(T *ptr) : ptr_(ptr) {}

    reference operator * () const
    {
        return *ptr_;
    }

    Iterator &operator ++ ()
    {
        ++ptr_;
        return *this;
    }

    Iterator &operator -- ()
    {
        --ptr_;
        return *this;
    }

    bool operator == (const Iterator<T> &other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator != (const Iterator<T> &other) const
    {
        return !(*this == other);
    }
};

template <class T, class Alloc = std::allocator<T>>
class Vector
{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using pointer =  typename Alloc::pointer;

private:
    pointer vec = nullptr;
    size_type mem = 0, sz = 0;
    Alloc alloc_;

public:
    explicit Vector(size_type count = 0)
    {
        vec = alloc_.allocate(count);
        mem = sz = count;
        for (size_type i = 0; i < sz; ++i) {
            alloc_.construct(vec + i);
        }
    }

    Vector(size_type count, const value_type &defaultValue)
    {
        vec = alloc_.allocate(count);
        mem = sz = count;
        for (size_type i = 0; i < sz; ++i) {
            alloc_.construct(vec + i, defaultValue);
        }
    }

    iterator begin() noexcept
    {
        return iterator(vec);
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    Iterator<T> end() noexcept
    {
        return iterator(vec + sz);
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    size_type size() const noexcept
    {
        return sz;
    }

    bool empty() const noexcept
    {
        return size() == 0;
    }

    size_type capacity() const noexcept
    {
        return mem;
    }

    void reserve(size_type count)
    {
        if (mem != count) {
            auto tmp = alloc_.allocate(count);

            if (sz > count) {
                sz = count;
            }
            for (size_type i = 0; i < sz; ++i) {
                alloc_.construct(tmp + i, vec[i]);
                alloc_.destroy(vec + i);
            }
            alloc_.deallocate(vec, mem);

            vec = tmp;
            mem = count;
        }
    }

    void resize(size_type new_size, const value_type& defaultValue = value_type())
    {
        if (new_size >= sz) {
            if (mem < new_size) {
                reserve(new_size);
            }

            for (size_type i = sz; i < new_size; ++i) {
                alloc_.construct(vec + i, defaultValue);
            }
        } else {
            for (size_type i = new_size; i < sz; ++i) {
                alloc_.destroy(vec + i);
            }
        }
        sz = new_size;
    }

    void push_back(const value_type &value)
    {
        if (sz >= mem) {
            reserve(2 * mem + 1);
        }
        vec[sz] = value;
        ++sz;
    }

    void push_back(value_type &&value)
    {
        if (sz >= mem) {
            reserve(2 * mem + 1);
        }
        vec[sz] = std::move(value);
        ++sz;
    }

    void clear() noexcept
    {
        while (sz > 0) {
            alloc_.destroy(vec + sz);
            --sz;
        }
    }

    void pop_back()
    {
        --sz;
        alloc_.destroy(vec + sz);
    }

    const_reference operator[] (size_type i) const
    {
        return vec[i];
    }

    reference operator[] (size_type i)
    {
        return vec[i];
    }

    ~Vector()
    {
        clear();
        alloc_.deallocate(vec, mem);
    }
};
