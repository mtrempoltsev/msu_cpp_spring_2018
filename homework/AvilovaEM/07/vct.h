#include <stdexcept>
#include <limits>
#include <iterator>
#include <cstring>

template <class T>
class Allocator
{
public:
  
    void construct(T* ptr) 
    {
        ptr = new (ptr) T();
    }
    
    void construct(T* ptr, const T& val) 
    {
        ptr = new (ptr) T(val);
    }
    
    void construct(T* ptr, T&& val) 
    {
        ptr = new (ptr) T(std::move(val));
    }
    
    void destroy(T* ptr) 
    {
        ptr->~T();
    }

    T* allocate(size_t count) 
    {
        if (count > max_size())
            throw std::length_error("max size");
        T* ptr = (T*) malloc(sizeof(T) * count);
        return ptr;
    }
    
    void deallocate(T* ptr, size_t count) 
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
    T* ptr_;
public:

    explicit Iterator(T* ptr): ptr_(ptr) 
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
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = 	std::reverse_iterator<const_iterator>;

    Vector(size_t count = 0) 
    {
        if (count != 0) 
        {
            data_ = alloc_.allocate(count);
            for (size_t i = 0; i < count; i++)
                alloc_.construct(data_ + i);
            size_ = count;
            capacity_ = count;
        }
    }
    
    T& operator[] (size_t n) 
    {
        if (n >= size_)
            throw std::out_of_range("out");
        return data_[n];
    }
    
    const T& operator[] (size_t n) const 
    {
        if (n >= size_)
            throw std::out_of_range("out");
        return data_[n];
    }
    
    bool empty() const noexcept 
    {
        return size_ == 0;
    }
    
    size_t size() const noexcept 
    {
        return size_;
    }
    
    size_t capacity() const noexcept 
    {
        return capacity_;
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
        return const_reverse_iterator(end());
    }
    
    reverse_iterator rend() noexcept 
    {
        return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const noexcept 
    {
        return const_reverse_iterator(begin());
    }
    
    void reserve(size_t n) 
    {
        if (n > capacity_) 
        {
            T* newData = alloc_.allocate(n);
            for (size_t i = 0; i < size_; i++) 
            {
                alloc_.construct(newData + i, data_[i]);
                alloc_.destroy(data_ + i);
            }
            std::swap(data_, newData);
            alloc_.deallocate(newData, size_);
            
            capacity_ = n;
        }
    }
    
    void resize(size_t n) 
    {
        if (n < size_) 
            for (size_t i = n; i < size_; i++)
                alloc_.destroy(data_ + i);
        
        if (n > capacity_) 
            reserve(n);
        
        if (n > size_) 
            for (size_t i = size_; i < n; ++i) 
                alloc_.construct(data_ + i);
            
        
        size_ = n;
    }

    void clear() noexcept 
    {
        resize(0);
    }
    
    ~Vector() 
    {
        clear();
        alloc_.deallocate(data_, 0);
    }
    
    void push_back (const T& val) 
    {
        if (size_ == capacity_)
        { 
            if (size_ == 0)
                reserve(1);
            else
                reserve(2 * size_);
        }
        alloc_.construct(data_ + size_, val);
        ++size_;
        
    }
    
    void push_back (T&& val) 
    {
        if (size_ == capacity_)
        { 
            if (size_ == 0)
                reserve(1);
            else
                reserve(2 * size_);
        }
        alloc_.construct(data_ + size_, std::move(val));
        ++size_;
    }
    
    void pop_back() 
    {
        if (size_ > 0)
            resize(size_ - 1);
    }
    
private:
    Alloc alloc_;
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};
