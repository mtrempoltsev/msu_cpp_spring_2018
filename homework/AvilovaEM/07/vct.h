#include <limits>
#include <iterator>
#include <cstring>

template <class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count) 
    {
         pointer ptr = (pointer) malloc(sizeof(value_type) * count);
         return ptr; 
    }
    
    void deallocate(pointer ptr)
    {
        free(ptr);
    }

    size_t max_size() const noexcept 
    {
        return std::numeric_limits<size_type>::max();
    }
};

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
    T* ptr_;
public:

    explicit Iterator(T* ptr): 
    ptr_(ptr) 
    {}

    bool operator==(const Iterator<T>& other) const 
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const 
    {
        return !(*this == other);
    }

    T& operator*() const 
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
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using value_type = T;
    using pointer = T*;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using size_type = size_t;
    
    Vector(size_type size = 0) 
    {
        if (size != 0) 
        {
            data_ = alloc_.allocate(size);
            size_ = size;
            capacity_ = size;
        }
    }
    
    value_type& operator[] (size_type n) 
    {
        return data_[n];
    }
    
    const value_type& operator[] (size_type n) const 
    {
        return data_[n];
    }
    
    bool empty() const noexcept 
    {
        return size_ == 0;
    }
    
    size_type size() const noexcept 
    {
        return size_;
    }
    
    size_type capacity() const noexcept 
    {
        return capacity_;
    }
    
    iterator begin() noexcept 
    {
        return iterator(data_);
    }
    
    const iterator begin() const noexcept 
    {
        return const_iterator(data_);
    }
    
    iterator end() noexcept 
    {
        return iterator(data_ + size_);
    }
    
    const iterator end() const noexcept 
    {
        return const_iterator(data_ + size_);
    }
    
    reverse_iterator rbegin() noexcept 
    {
        return reverse_iterator(end());
    }
    
    const reverse_iterator rbegin() const noexcept 
    {
        return std::reverse_iterator<const iterator>(end());
    }
    
    reverse_iterator rend() noexcept 
    {
        return reverse_iterator(begin());
    }
    
    const reverse_iterator rend() const noexcept 
    {
        return std::reverse_iterator<const iterator>(begin());
    }
    
    void reserve(size_type n) 
    {
        if (n > capacity_) 
        {
            pointer newData = alloc_.allocate(n);
            std::memcpy(newData, data_, size_ * sizeof(value_type));
            std::swap(data_, newData);
            alloc_.deallocate(newData);    
            capacity_ = n;
        }
    }
    
    void resize(size_type n) 
    {
        if (n < size_) 
            for (size_type i = n; i < size_; i++)
                data_[i].~value_type();
        if (n > capacity_) 
            reserve(n);
        if (n > size_) 
            for (size_type i = size_; i < n; ++i) 
                data_[i] = value_type();
        size_ = n;
    }

    void clear() noexcept 
    {
        resize(0);
    }
    
    ~Vector() 
    {
        clear();
        alloc_.deallocate(data_);
    }
    
    void push_back (const value_type& val) 
    {
        if (size_ == capacity_) 
            if (size_ == 0)
                reserve(1);
            else
                reserve(size_+1);
        data_[size_] = val;
        ++size_;
        
    }
    
    void push_back (value_type&& val) 
    {
        if (size_ == capacity_) 
            if (size_ == 0)
                reserve(1);
            else
                reserve(size_+1);
        data_[size_] = val;
        ++size_;
    }
    
    void pop_back() 
    {
        if (size_ > 0)
            resize(size_ - 1);
    }
private:
    Alloc alloc_;
    pointer data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;
};
