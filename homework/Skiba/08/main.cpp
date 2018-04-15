#include <iostream>
#include <limits>
#include <algorithm>
#include <string>

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

template <class T>
class ReIterator {
    T* ptr;
public:
    explicit ReIterator(const ReIterator<T>& mid): ptr(mid.ptr) {}
    explicit ReIterator(const T* midptr): ptr(midptr) {}
    bool operator==(const ReIterator<T>& mid) const {
        return ptr == mid.ptr;
    }
    bool operator!=(const ReIterator<T>& mid) const {
        return !(*this == mid);
    }
    T& operator*() const{
        return *ptr;
    }
    ReIterator& operator++() {
        --ptr;
        return *this;
    }
    ReIterator& operator--() {
        ++ptr;
        return *this;
    }
    ReIterator operator+(size_t step) const {
        return ReIterator<T>(ptr - step);
    }
    ReIterator operator-(size_t step) const {
        return Iterator<T>(ptr + step);
    }
    size_t operator-(const ReIterator<T>& mid) const {
        return ptr - mid.ptr;
    }
};


template <class T, class Alloc = Allocator<T> >
class Vector {
    size_t sz, cp;
    T* ptr;
    Alloc alloc;
public:
    Vector(size_t _sz = 0) {
        sz = _sz;
        cp = sz * 2 + 10;
        ptr = alloc.allocate(cp);
    }
    ~Vector() {
        alloc.deallocate(ptr, cp);
    }
    bool empty() const noexcept{
        return !(sz);
    }
    size_t size() const noexcept{
        return sz;
    }
    T& operator[](size_t ind) {
        if (ind < sz) {
            return *(ptr + ind);
        } else {
            throw("Invalig index");
        }
    }
    const T& operator[](size_t ind) const {
        if (ind < sz) {
            return *(ptr + ind);
        } else {
            throw("Invalig index");
        }
    }
    void clear() {
        sz = 0;
    }
    void pop_back() {
        sz--;
    }
    void push_back(const T& arg) {
        resize(sz + 1);
        ptr[sz - 1] = arg;
    }
    void resize(size_t newsz) {
        if (cp < newsz + 1) {
            size_t newcp = newcp * 2 + 10;
            T* newptr = alloc.allocate(newcp);
            std::copy(ptr, ptr + cp, newptr);
            std::swap(ptr, newptr);
            alloc.deallocate(newptr, cp);
            cp = newcp;
            sz = newsz;
        } else {
            sz = newsz;
        }
    }
    void reserve(size_t newcp) {
        if (cp < newcp + 1) {
            T* newptr = alloc.allocate(newcp);
            std::copy(ptr, ptr + cp, newptr);
            std::swap(ptr, newptr);
            alloc.deallocate(newptr, cp);
            cp = newcp;
        }
    }
    Iterator<T> begin() const {
        return Iterator<T>(ptr);
    }
    Iterator<T> end() const {
        return Iterator<T>(ptr + sz + 1);
    }
    ReIterator<T> rbegin() const {
        return ReIterator<T>(ptr + sz + 1);
    }
    ReIterator<T> rend() const {
        return ReIterator<T>(ptr);
    }
};

int main(int argc, char *argv[]) {
    std::string s = {"KEK"};
    std::cout << s << std::endl;
    return 0;
}