#include <iostream>
#include <iterator>

template <class T>
class Allocator {
public:
    T* allocate(size_t size) { return static_cast<T*> (::operator new(sizeof(T) * size)); }
    void construct(T* ptr) {
        ptr = new (ptr) T();
    }
    
    void construct(T* ptr, const T& val) {
        ptr = new (ptr) T(val);
    }
    
    void destroy(T* ptr, const size_t i) {
        (ptr + i)->~T();
    }
    
    void deallocate(T*& ptr, size_t len) {
        if (ptr) {
            ::operator delete(ptr);
            ptr = nullptr;
        }
    }
};

template<class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T> {
private:
    T* p;
public:
    explicit Iterator(T* ptr): p(ptr) {}
    Iterator& operator ++ () {
        ++p;
        return (*this);
    }
    Iterator& operator -- () {
        --p;
        return (*this);
    }
    Iterator operator + (T x) { return Iterator(p + x); }
    Iterator operator - (T x) { return Iterator(p - x); }
    Iterator& operator += (T x) {
        p += x;
        return (*this);
    }
    Iterator& operator -= (T x) {
        p -= x;
        return (*this);
    }
    bool operator == (const Iterator& it) { return (p == it.p); }
    bool operator != (const Iterator& it) { return (p != it.p); }
    T& operator * () { return (*p); }
    T* operator -> () { return p; }
};

template<class T>
class ReverseIterator: public std::iterator<std::random_access_iterator_tag, T> {
private:
    T* p;
public:
    explicit ReverseIterator(T* ptr) : p(ptr) {}
    ReverseIterator& operator ++ () {
        --p;
        return (*this);
    }
    ReverseIterator& operator -- () {
        ++p;
        return (*this);
    }
    ReverseIterator& operator += (T x) {
        p -= x;
        return (*this);
    }
    
    ReverseIterator& operator -= (T x) {
        p += x;
        return (*this);
    }
    ReverseIterator operator + (T x) { return ReverseIterator(p - x); }
    ReverseIterator operator - (T x) { return ReverseIterator(p + x); }
    T& operator * () { return (*p); }
    T* operator -> () { return p; }
    bool operator == (const ReverseIterator& it) { return (p == it.p); }
    bool operator != (const ReverseIterator& it) { return (p != it.p); }
};


template <class T, class Alloc = Allocator<T>>
class Vector {
private:
    T* data_;
    Alloc alloc_;
    size_t len;
    size_t capacity_;
public:
    Vector(): data_(nullptr), len(0), capacity_(0) {}
    Vector(size_t size): len(size), capacity_(len * 2), data_(alloc_.allocate(capacity_)) {
        for (size_t i = 0; i < size; i++) {
            alloc_.construct(data_ + i);
        }
    }
    Vector(const Vector& vector): Vector() {
        (*this) = vector;
    }
    Vector(const size_t size, const T& default_value) {
        if(size) {
            reserve(size + 1);
            len = size;
            for(int i = 0; i < size; ++i) {
                alloc_.construct(data_ + i, default_value);
            }
        }
    }
    const T* data() const {
        return data_;
    }
    T& operator [] (const size_t position) {
        return data_[position];
    }
    const T& operator [] (const size_t position) const {
        return data_[position];
    }
    void push_back(const T& num) {
        if (len == capacity_) {
            reserve(std::max((size_t)8, len) * 2);
        }
        alloc_.construct(data_ + len, num);
        len++;
    }
    void pop_back() {
        if (len == 1) {
            clear();
        } else if (len > 1) {
            alloc_.destroy(data_, len-- - 1);
        }
    }
    void resize(const size_t new_size) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        for (size_t i = std::min(len, new_size); i < len; i++) {
            alloc_.destroy(data_, i);
        }
        for (size_t i = std::min(len, new_size); i < new_size; ++i) {
            alloc_.construct(data_ + i);
        }
        len = new_size;
    }
    void reserve(const size_t new_size) {
        if (new_size > capacity_) {
            T* new_data = alloc_.allocate(new_size);
            for (size_t i = 0; i < len; i++) {
                alloc_.construct(new_data + i, data_[i]);
                alloc_.destroy(data_, i);
            }
            std::swap(data_, new_data);
            alloc_.deallocate(new_data, len);
            capacity_ = new_size;
        }
    }
    bool empty() const noexcept {
        return len == 0;
    }
    size_t size() const noexcept {
        return len;
    }
    size_t capacity() const noexcept {
        return capacity_;
    }
    void clear() {
        for (size_t i = 0; i < len; i++) {
            alloc_.destroy(data_, i);
        }
        len = 0;
        capacity_ = 0;
        alloc_.deallocate(data_, len);
    }
    
    Iterator<T> begin() noexcept {
        return Iterator<T>(data_);
    }
    Iterator<T> end() noexcept {
        return Iterator<T>(data_ + len);
    }
    ReverseIterator<T> rbegin() noexcept {
        return ReverseIterator<T>(data_ + len - 1);
    }
    ReverseIterator<T> rend() noexcept {
        return ReverseIterator<T>(data_ - 1);
    }
    ~Vector() {
        clear();
    }
};


