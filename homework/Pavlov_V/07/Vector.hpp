
#include "Iterator.hpp"
#include "Allocator.hpp"
#include "ConstIterator.hpp"
#include <iostream>

template <class T, class Alloc = Allocator<T>>
class  Vector {
private:
    T* data;
    size_t len;
    size_t capacity_;
    Alloc alloc_;
public:
    using iterator = Iterator<T>;
    Vector(): len(0), capacity_(0) {}
    Vector(size_t val ,const T& defaultValue = T()): len(val), capacity_(val) {
        if (val != 0) {
            data = alloc_.allocate(val);
            for (int i = 0; i < val; i++) {
                *(data + i) = T(defaultValue);
            }
        }
    }
    
    size_t size() const noexcept {
        return len;
    }
    
    size_t capacity() const noexcept {
        return capacity_;
    }
    
    T& operator [] (size_t position) {
        return data[position];
    }
    
    const T& operator [] (size_t position) const {
        return data[position];
    }
    
    Iterator<T> begin() noexcept {
        return Iterator<T> (data);
    }
    
    Iterator<T> end() noexcept {
        return Iterator<T>(data + len);
    }
    
    ConstIterator<T> begin() const noexcept {
        return ConstIterator<T> (data);
    }
    
    ConstIterator<T> end() const noexcept {
        return ConstIterator<T>(data + len);
    }
    
    void resize(size_t new_len){
        if (new_len > size()) {
            if (new_len > capacity_) {
                while (data - (data + len) < capacity_) {
                    *(data + len) = T();
                    ++len;
                }
                allocate(new_len);
            }
            while ((data + len) - data < new_len) {
                *(data + len) = T();
                ++len;
            }
        } else {
            while (len > new_len) {
                (data + (--len))->~T();
            }
        }
        len = new_len;
    }
    
    void resize(size_t count, const T &value) {
        if (count <= size()) {
            len = count;
        } else {
            if (count > capacity_) {
                allocate(count);
            }
            while (len < count) {
                *(data + len) = value;
                ++len;
            }
        }
    }
    
    bool empty(){
        return len == 0;
    }
    
    void clear() {
        while ((data + len) != data) {
            (data + (--len))->~T();
        }
    }
    
    std::reverse_iterator<iterator> rbegin() noexcept {
        return std::reverse_iterator<iterator>(end());
    }
    
    std::reverse_iterator<iterator> rend() noexcept {
        return std::reverse_iterator<iterator>(begin());
    }
    
    void reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            allocate(new_cap);
        }
    }
    
    void allocate(size_t new_cap) {
        T* new_begin = alloc_.allocate(new_cap);
        std::memcpy(new_begin, data, len * sizeof(T));
        if (data)
            alloc_.deallocate(data);
        data = new_begin;
        capacity_ = new_cap;
    }
    
    void push_back(T& value) {
        if (size() == capacity_) {
            allocate(capacity_ != 0 ? 2 * capacity_ : 2 * capacity_ + 1);
        }
        *(data + len) = value;
        ++(data + len);
    }
    
    void push_back(T&& value) {
        if (size() == capacity_) {
            allocate(capacity_ != 0 ? 2 * capacity_ : 2 * capacity_ + 1);
        }
        *(data + len) = std::move(value);
        ++len;
    }
    
    void pop_back() {
        (data + (--len))->~T();
    }
    
    ~Vector() {
        clear();
        if (data)
            alloc_.deallocate(data);
    }
    
};



