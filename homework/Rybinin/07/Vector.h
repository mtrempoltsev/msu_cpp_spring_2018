#include <stdexcept>
#include <limits>
#include <iterator>
#include <cstring>
#include<stdexcept>

class AllocatorError : std::exception{};
template <class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count)
    {
        if(count > max_size()){
            throw AllocatorError();
        }
        return static_cast<pointer>(::operator new(count * sizeof(value_type)));
    }

    void deallocate(pointer ptr)
    {
        ::operator delete(ptr);
    }

    template<class... Args>
    void construct(pointer ptr, Args&&... args)
    {
        ::new (ptr) value_type(std::forward<Args>(args)...);
    }

    void destroy(pointer ptr)
    {
        ptr->~value_type();
    }

    size_t max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
};

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
     T* ptr_;
public:
    using reference = T&;

    explicit Iterator(T* ptr)
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

    Iterator& operator+= (int m)
    {
        ptr_ += m;
        return *this;
    }

    Iterator& operator-= (int n)
    {
        return *this += -n;
    }

    Iterator operator+ (int n)
    {
        Iterator temp = *this;
        return *this += n;
    }

    Iterator operator- (int n)
    {
        Iterator temp = *this;
        return temp -= n;
    }
};

class VectorError : std::exception {};
template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type = size_t;
    using value_type = T;
    using pointer = T*;

    Vector(size_type size = 0)
    {
        if(size != 0)
        {
            data_ = alloc_.allocate(size);
            size_ = size;
            capacity_ = size;
        }else{
            data_ = alloc_.allocate(1);
            size_ = 0;
            capacity_ = 1;
        }
        for(size_type i = 0; i < size_; ++i)
            data_[i] = value_type();
    }

    size_type size() const
    {
        return size_;
    }

    size_type capacity() const
    {
        return capacity_;
    }
    bool empty() const noexcept
    {
        return size_ == 0;
    }

    iterator begin() noexcept
    {
        return iterator(data_);
    }

    const_iterator begin() const noexcept
    {
        return const_iterator(data_);
    }

    iterator end() noexcept
    {
        return iterator(data_ + size_);
    }

    const_iterator end() const noexcept
    {
        return const_iterator(data_ + size_);
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator(end());
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    value_type& operator[](size_type n)
    {
        if(n >= size_)
            throw std::out_of_range("Out of range");
        return data_[n];
    }

    const value_type& operator[](size_type n) const
    {
        if(n >= size_)
            throw std::out_of_range("Out of range");
        return data_[n];
    }

    void resize(size_type newSize)
    {
        if(newSize > capacity_){
            reserve(newSize);
        }
        for(size_type i = size_; i < newSize; ++i)
            alloc_.construct(data_ + i);
        for(size_type i = newSize; i < size_; ++i)
            alloc_.destroy(data_ + i);
        size_ = newSize;
    }

    void reserve(size_type n)
    {
        if(n > size_){
            pointer newData = alloc_.allocate(n);
            std::copy(data_, data_ + size_, newData);
            std::swap(data_, newData);
            for(size_type i = 0; i < size_; ++i)
                alloc_.destroy(data_ + i);
            alloc_.deallocate(newData);
            capacity_ = n;
        }
    }

    void clear() noexcept
    {
        resize(0);
    }

    ~Vector()
    {
        for(int i = 0; i < size_ ;++i)
            data_[i].~value_type();
        alloc_.deallocate(data_);
    }

    void push_back (const value_type& val)
    {
        if(size_ == capacity_)
            reserve(size_ * 2);
        data_[size_] = val;
        ++size_;
    }

    void push_back (value_type&& val)
    {
        if(size_ == capacity_)
            reserve(size_ * 2);
        data_[size_] = std::move(val);
        ++size_;
    }

    void pop_back()
    {
        if(size_ > 0){
            data_[size_].~value_type();
            size_--;
        }else
            throw VectorError();
    }

private:
    Alloc alloc_;
    value_type* data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;
};
