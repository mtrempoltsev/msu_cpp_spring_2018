#include <iostream>
#include <limits>
#include <memory>
#include <algorithm>

template <class T>
class Allocator {
public:
    T* allocate(size_t count) {
        return new T[count];
    }
    void deallocate(T* ptr, size_t count) {
        delete[] ptr;
    }
    size_t max_size() const noexcept {
        return std::numeric_limits<size_t>::max();
    }
};

template <class T>
class Iterator {
    T* ptr;
public:
    explicit Iterator(const Iterator<T>& mid): ptr(mid.ptr) {}
    explicit Iterator(const T* midptr): ptr(midptr) {}
    bool operator==(const Iterator<T>& mid) const {
        return ptr == mid.ptr;
    }
    bool operator!=(const Iterator<T>& mid) const {
        return !(*this == mid);
    }
    T& operator*() const{
        return *ptr;
    }
    Iterator& operator++() {
        ++ptr;
        return *this;
    }
    Iterator& operator--() {
        --ptr;
        return *this;
    }
    Iterator operator+(size_t step) const {
        return Iterator<T>(ptr + step);
    }
    Iterator operator-(size_t step) const {
        return Iterator<T>(ptr - step);
    }
    size_t operator-(const Iterator<T>& mid) const {
        return ptr - mid.ptr;
    }
};


template <class T, class Alloc = Allocator<T> >
class Vector {
    size_t sz, cp;
    T* ptr;
public:
    Vector(size_t _sz = 0) {
        sz = _sz;
        cp = sz * 2 + 10;
    }
    ~Vector() {
    }
    bool empty() const noexcept{
        return !(sz);
    }
    size_t size() const noexcept{
        return sz;
    }
};

int main(int argc, char *argv[]) {
    return 0;
}