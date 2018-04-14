//
// Created by Sergey Petrenko on 12.04.2018.
//

#ifndef SPHERE_01_C_HW07_MY_VECT_H
#define SPHERE_01_C_HW07_MY_VECT_H

#include <iterator>
#include <memory>
#include <limits>

template <class T>
class Allocator
{
public:
    T* allocate(size_t count);

    void deallocate(T * ptr, size_t count);

    size_t max_size() const noexcept;
};

template <class T>
class Iterator : std::iterator<std::random_access_iterator_tag, T>
{
    T * ptr_;
public:
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;

    explicit Iterator(T * ptr);

    bool operator==(const Iterator<T> & other) const;

    bool operator!=(const Iterator<T> & other) const;

    T& operator*() const;

    T& operator[](size_t n) const;

    Iterator& operator++();

    const Iterator operator++(int);

    Iterator& operator--();

    const Iterator operator--(int);

    Iterator& operator+=(ssize_t n);

    Iterator& operator-=(ssize_t n);

    Iterator operator+(ssize_t n) const;

    Iterator operator-(ssize_t n) const;

};

template <class T, class Alloc = Allocator<T>>
class Vector
{
private:
    Alloc alloc_;
    size_t cap_;
    size_t size_;
    T * buf_;

    void realloc(size_t new_size);
public:
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;

    Vector();

    explicit Vector(size_t init_size, const Alloc & allocator = Alloc());

    Vector(size_t init_size, const T& def, const Alloc & allocator = Alloc());

    ~Vector();

    T& operator[](size_t n);

    void push_back(T & value);

    void push_back(T && value);

    void pop_back();

    bool empty() const noexcept;

    size_t size() const noexcept;

    size_t capacity() const noexcept;

    void clear() noexcept;

    iterator begin() noexcept;

    iterator end() noexcept;

    reverse_iterator rbegin() noexcept;

    reverse_iterator rend() noexcept;

    void reserve(size_t new_size);

    void resize(size_t count);

    void resize(size_t count, const T & value);

};

template<typename T>
T* Allocator<T>::allocate(size_t count) {
    return static_cast<T*>(operator new[](count * sizeof(T)));
}

template<typename T>
void Allocator<T>::deallocate(T * ptr, size_t count) {
    operator delete[](ptr);
}

template<typename T>
size_t Allocator<T>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}


template<typename T>
Iterator<T>::Iterator(T * ptr) : ptr_(ptr) {
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T> & other) const {
    return ptr_ == other.ptr_;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T> & other) const {
    return ptr_ != other.ptr_;
}

template<typename T>
T& Iterator<T>::operator*() const {
    return *ptr_;
}

template<typename T>
T& Iterator<T>::operator[](size_t n) const {
    return *(this->operator+(n));
}

template<typename T>
Iterator<T> & Iterator<T>::operator++() {
    ++ptr_;
    return *this;
}

template<typename T>
Iterator<T> & Iterator<T>::operator--() {
    --ptr_;
    return *this;
}

template<typename T>
const Iterator<T> Iterator<T>::operator++(int) {
    auto old = *this;
    ++ptr_;
    return old;
}

template<typename T>
const Iterator<T> Iterator<T>::operator--(int) {
    auto old = *this;
    --ptr_;
    return old;
}

template<typename T>
Iterator<T> & Iterator<T>::operator+=(ssize_t n) {
    ptr_ += n;
    return *this;
}

template<typename T>
Iterator<T> & Iterator<T>::operator-=(ssize_t n) {
    ptr_ -= n;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator+(ssize_t n) const {
    auto other = *this;
    return other.operator+=(n);
}

template<typename T>
Iterator<T> Iterator<T>::operator-(ssize_t n) const {
    auto other = *this;
    return other.operator-=(n);
}


template<class T, class Alloc>
Vector<T, Alloc>::Vector()
        : alloc_(),
          cap_(16),
          size_(0),
          buf_(alloc_.allocate(cap_)) {
}

template<class T, class Alloc>
Vector<T, Alloc>::Vector(size_t init_size, const Alloc &allocator)
        : alloc_(allocator),
          cap_(init_size),
          size_(init_size),
          buf_(alloc_.allocate(cap_)) {

}

template<class T, class Alloc>
Vector<T, Alloc>::Vector(size_t init_size, const T &def, const Alloc &allocator)
        : alloc_(allocator),
          cap_(init_size),
          size_(init_size),
          buf_(alloc_.allocate(cap_)) {
    new (buf_) T(def);
}

template<class T, class Alloc>
Vector<T, Alloc>::~Vector() {
    for(size_t j = 0; j < size_; ++j) {
        buf_[j].~T();
    }
    alloc_.deallocate(buf_, cap_);
}

template<class T, class Alloc>
void Vector<T, Alloc>::realloc(size_t new_cap) {
    T* new_buf = alloc_.allocate(new_cap);
    std::copy(buf_, buf_ + std::min(size_, new_cap), new_buf);
    for(size_t j = 0; j < size_; ++j) {
        buf_[j].~T();
    }
    alloc_.deallocate(buf_, cap_);
    buf_ = new_buf;
    cap_ = new_cap;
    size_ = std::min(size_, new_cap);
}

template<class T, class Alloc>
T &Vector<T, Alloc>::operator[](size_t n) {
    return *(buf_ + n);
}

template<class T, class Alloc>
void Vector<T, Alloc>::push_back(T &value) {
    if(size_ == cap_) {
        realloc(2 * cap_);
    }
    buf_[size_++] = value;
}

template<class T, class Alloc>
void Vector<T, Alloc>::push_back(T &&value) {
    if(size_ == cap_) {
        realloc(2 * cap_);
    }
    new (buf_ + size_++) T(std::move(value));
}

template<class T, class Alloc>
void Vector<T, Alloc>::pop_back() {
    if(size_ > 0) {
        buf_[--size_].~T();
    }
}

template<class T, class Alloc>
bool Vector<T, Alloc>::empty() const noexcept {
    return size_ == 0;
}

template<class T, class Alloc>
size_t Vector<T, Alloc>::size() const noexcept {
    return size_;
}

template<class T, class Alloc>
size_t Vector<T, Alloc>::capacity() const noexcept {
    return cap_;
}

template<class T, class Alloc>
void Vector<T, Alloc>::clear() noexcept {
    for(size_t i = 0; i < size_; ++i) {
        buf_[i].~T();
    }
    size_ = 0;
}

template<class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::begin() noexcept {
    return Vector::iterator(buf_);
}

template<class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::end() noexcept {
    return Vector::iterator(buf_ + size_);
}

template<class T, class Alloc>
typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rbegin() noexcept {
    return std::reverse_iterator<iterator>(end());
}

template<class T, class Alloc>
typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rend() noexcept {
    return std::reverse_iterator<iterator>(begin());
}

template<class T, class Alloc>
void Vector<T, Alloc>::reserve(size_t new_cap) {
    if(new_cap > cap_)
        realloc(new_cap);
}

template<class T, class Alloc>
void Vector<T, Alloc>::resize(size_t count) {
    if(count < size_) {
        for(size_t j = count; j < size_; ++j) {
            buf_[j].~T();
        }
    } else if(count > size_) {
        if(count > cap_) {
            realloc(std::max(2 * cap_, count));
        }
        new (buf_ + size_) T[count - size_]();
    }
    size_ = count;
}

template<class T, class Alloc>
void Vector<T, Alloc>::resize(size_t count, const T &value) {
    if(count < size_) {
        for(size_t j = count; j < size_; ++j) {
            buf_[j].~T();
        }
    } else if(count > size_) {
        if(count > cap_) {
            realloc(std::max(2 * cap_, count));
        }
        for(size_t j = size_; j < count; ++j) {
            new(buf_ + j) T(value);
        }
    }
    size_ = count;
};

#endif //SPHERE_01_C_HW07_MY_VECT_H