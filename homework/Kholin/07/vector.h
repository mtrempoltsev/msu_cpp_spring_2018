#include <stdint.h>
#include <iterator>
#include <iostream>
#include <cstring>

template<class T>
class allocator {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = uint32_t;

    pointer allocate(size_type count) {
        pointer ptr = static_cast<T*>(malloc(count * sizeof(count)));
        return ptr;
    }

    void deallocate(pointer ptr, size_type count) {
        free(ptr);
    }
};

template<typename T>
class iterator
    : public std::iterator<std::forward_iterator_tag, T> {
public:
    using reference = T&;

    explicit iterator(T* ptr)
        : ptr_(ptr) {
    }

    bool operator==(const iterator<T>& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const iterator<T>& other) const {
        return !(*this == other);
    }

    reference operator*() const {
        return *ptr_;
    }

    iterator& operator++() {
        ++ptr_;
        return *this;
    }

    iterator& operator--() {
        --ptr_;
        return *this;
    }

    iterator& operator+(uint32_t i) {
        ptr_ += i;
        return *this;
    }

    iterator& operator-(uint32_t i) {
        --ptr_ -= i;
        return *this;
    }
private:
    T* ptr_;
};

template<typename T>
class reverse_iterator
    : public std::iterator<std::forward_iterator_tag, T> {
public:
    using reference = T&;

    explicit reverse_iterator(T* ptr)
        : ptr_(ptr) {
    }

    bool operator==(const reverse_iterator<T>& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const reverse_iterator<T>& other) const {
        return !(*this == other);
    }

    reference operator*() const {
        return *ptr_;
    }

    reverse_iterator& operator++() {
        --ptr_;
        return *this;
    }

    reverse_iterator& operator--() {
        ++ptr_;
        return *this;
    }

    reverse_iterator& operator+(uint32_t i) {
        ptr_ -= i;
        return *this;
    }

    reverse_iterator& operator-(uint32_t i) {
        ptr_ += i;
        return *this;
    }
private:
    T* ptr_;
};

template<typename T, typename Allocator = allocator<T> >
class Vector {
public:

    Vector() {
        resize_(1);
        size_ = 0;
    }

    Vector(const uint32_t n) {
        resize_(n);
        size_ = n;
    }

    T& operator[](const uint32_t i) {
        return *(data_ + i);
    }
    
    void push_back(const T& value) {
        if (size_ == length_) {
            resize_(length_ * 2);
        }
        *(data_ + size_) = value;
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ == length_) {
            resize_(length_ * 2);
        }
        *(data_ + size_) = std::move(value);
        ++size_;
    }
    
    void pop_back() {
        (data_ + (size_ - 1))->~T();
        --size_;
    }
    
    bool empty() {
        return (size_ == 0);
    }
    
    uint32_t size() {
        return size_;
    }

    void clear() {
        for (uint32_t i = 0; i < size_; ++i) {
            (data_ + i)->~T();
        }
        size_ = 0;
    }
    
    iterator<T> begin() {
        iterator<T> it(data_);
        return it;
    }
    
    iterator<T> end() {
        iterator<T> it(data_ + (size_));
        return it;
    }
    
    reverse_iterator<T> rbegin() {
        reverse_iterator<T> it(data_ + (size_ - 1));
        return it;
    }
    
    reverse_iterator<T> rend() {
        reverse_iterator<T> it(data_ - 1);
        return it;
    }
    
    void resize(uint32_t size) {
        if (length_ < size) {
            resize_(size);
        }
        for (uint32_t i = size_; i < size; ++i) {
            data_[i] = T();
        }
        for (uint32_t i = size; i < size_; ++i) {
            (data_ + i)->~T();
        }
        size_ = size;
    }

    void reserve(uint32_t size) {
        resize_(size);
    }
    
    uint32_t capacity() {
        return length_;
    }

    ~Vector() {
        clear();
        allocator_.deallocate(data_, length_);
    }
private:
    T* data_ = nullptr;
    uint32_t size_ = 0;
    uint32_t length_ = 0;
    Allocator allocator_;

    void resize_(size_t length) {
        if (length > size_) {
            T* tempData = allocator_.allocate(length);
            std::copy(data_, data_ + size_, tempData);
            for (T* it = data_; it != data_ + size_; ++it) {
                it->~T();
            }
            allocator_.deallocate(data_, length_);
            data_ = tempData;
            length_ = length;
        } else {
            T* tempData = allocator_.allocate(length);
            std::move(data_, data_ + length, tempData);
            for (T* it = data_; it != data_ + size_; ++it) {
                it->~T();
            }
            allocator_.deallocate(data_, length_);
            data_ = tempData;
            length_ = length;
        }
    }
};
