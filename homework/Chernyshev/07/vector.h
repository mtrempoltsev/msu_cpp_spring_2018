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
            throw std::invalid_argument("size should be not greater than max size");
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

    bool operator == (const Iterator<T> &other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator != (const Iterator<T> &other) const
    {
        return !(*this == other);
    }

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


    explicit Vector(size_type count = 0)
    {
        data = alloc_.allocate(count);
        alloc = used = count;
        for (size_type i = 0; i < used; ++i) {
            alloc_.construct(data + i);
        }
    }

    Vector(size_type count, const value_type &defaultValue)
    {
        data = alloc_.allocate(count);
        alloc = used = count;
        for (size_type i = 0; i < used; ++i) {
            alloc_.construct(data + i, defaultValue);
        }
    }


    size_type capacity() const noexcept
    {
        return alloc;
    }

    size_type size() const noexcept
    {
        return used;
    }

    bool empty() const noexcept
    {
        return used == 0;
    }


    iterator begin() noexcept
    {
        return iterator(data);
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    Iterator<T> end() noexcept
    {
        return iterator(data + used);
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }


    void resize(size_type new_size, const value_type& defaultValue = value_type())
    {
        if (used > new_size) {
            for (size_type i = new_size; i < used; ++i) {
                alloc_.destroy(data + i);
            }
        } else {
            if (alloc < new_size) {
                reserve(new_size);
            }

            for (size_type i = used; i < new_size; ++i) {
                alloc_.construct(data + i, defaultValue);
            }
        }
        used = new_size;
    }

    void reserve(size_type count)
    {
        if (alloc != count) {
            auto tmp = alloc_.allocate(count);

            if (used > count) {
                used = count;
            }
            for (size_type i = 0; i < used; ++i) {
                alloc_.construct(tmp + i, data[i]);
                alloc_.destroy(data + i);
            }
            alloc_.deallocate(data, alloc);

            data = tmp;
            alloc = count;
        }
    }

    void clear() noexcept
    {
        while (used > 0) {
            alloc_.destroy(data + used);
            --used;
        }
    }


    void push_back(const value_type &value)
    {
        if (used >= alloc) {
            reserve(2 * alloc + 1);
        }
        data[used] = value;
        ++used;
    }

    void push_back(value_type &&value)
    {
        if (used >= alloc) {
            reserve(2 * alloc + 1);
        }
        data[used] = std::move(value);
        ++used;
    }

    void pop_back()
    {
        --used;
        alloc_.destroy(data + used);
    }

    reference operator[] (size_type i)
    {
        return data[i];
    }

    const_reference operator[] (size_type i) const
    {
        return data[i];
    }


    ~Vector()
    {
        clear();
        alloc_.deallocate(data, alloc);
    }


private:
    pointer data = nullptr;
    size_type alloc = 0, used = 0;
    Alloc alloc_;
};
