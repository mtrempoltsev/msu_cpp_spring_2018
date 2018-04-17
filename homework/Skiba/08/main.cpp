#include <iostream>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstring>


class v_err{
    std::string err;
public:
    v_err(const std::string& _err) {
        err = _err;
    }
    std::string get() {
        return err;
    }
};
template <class T>
class Allocator {
public:
    T* allocate(size_t count) {
        return (T*) malloc(sizeof(T) * count);
    }
    void deallocate(T* ptr, size_t count) {
        free(ptr);
    }
    size_t max_size() const noexcept {
        return std::numeric_limits<size_t>::max();
    }
    void construct(T* ptr) {
        new (ptr) T{};
    }
    void destroy(T* ptr) {
        (ptr)->~T();
    }
};

template <class T>
class Iterator {
    T* ptr;
    bool dir = false;
public:
    Iterator(T* midptr, bool _dir = true): ptr(midptr), dir(_dir) {}
    Iterator(const Iterator<T>& mid) {
        dir = mid.dir;
        ptr = mid.ptr;
    }
    bool operator==(const Iterator<T>& mid) const {
        return (ptr == mid.ptr) && (dir == mid.dir);
    }
    bool operator!=(const Iterator<T>& mid) const {
        return !(*this == mid);
    }
    T& operator*() const{
        return *ptr;
    }
    Iterator& operator++() {
        if (dir) {
            ++ptr;
        } else {
            --ptr;
        }
        return *this;
    }
    Iterator& operator--() {
        if (dir) {
            --ptr;
        } else {
            ++ptr;
        }
        return *this;
    }
    Iterator operator+(size_t step) const {
        if (dir) {
            return Iterator<T>(ptr + step);
        } else {
            return Iterator<T>(ptr - step);
        }
    }
    Iterator operator-(size_t step) const {
        if (dir) {
            return Iterator<T>(ptr - step);
        } else {
            return Iterator<T>(ptr + step);
        }
    }
    size_t operator-(const Iterator<T>& mid) const {
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
        sz = _sz + 1;
        cp = sz * 2 + 10;
        ptr = alloc.allocate(cp);
    }
    ~Vector() {
        for (size_t i = 1; i < sz; i++) {
            (ptr + i)->~T();
        }
        alloc.deallocate(ptr, cp);
    }
    bool empty() const noexcept{
        return !(sz - 1);
    }
    size_t size() const noexcept{
        return sz - 1;
    }
    size_t capacity() const noexcept{
        return cp;
    }
    T& operator[](size_t ind) {
        ind++;
        if (ind < sz) {
            return *(ptr + ind);
        } else {
            throw(v_err("Invalig index"));
        }
    }
    const T& operator[](size_t ind) const {
        ind++;
        if (ind < sz) {
            return *(ptr + ind);
        } else {
            throw(v_err("Invalig index"));
        }
    }
    void clear() {
        for (size_t i = 1; i < sz; i++) {
            (ptr + i)->~T();
        }
        sz = 1;
    }
    void pop_back() {
        (ptr + sz - 1)->~T();
        sz--;
    }
    void push_back(const T& arg) {
        sz++;
        if (sz >= cp) {
            resize(sz, 0);
        }
        ptr[sz - 1] = arg;
    }
    void resize(size_t newsz, size_t add = 1) {
        newsz += add;
        if (cp <= newsz) {
            reserve(newsz * 2 + 10);
        }
        for (size_t j = sz; j < newsz; j++) {
            //new (ptr + j) T{};
            alloc.construct(ptr + j);
        }
        for (size_t j = newsz; j < sz; j++) {
            //(ptr + j)->~T();
            alloc.destroy(ptr + j);
        }
        sz = newsz;
    }
    void reserve(size_t newcp) {
        if (cp <= newcp) {
            T* newptr = alloc.allocate(newcp);
            std::memcpy(newptr, ptr, sizeof(T) * cp);
            std::swap(ptr, newptr);
            alloc.deallocate(newptr, cp);
            cp = newcp;
        }
    }
    Iterator<T> begin() const {
        return Iterator<T>(ptr + 1, true);
    }
    Iterator<T> end() const {
        return Iterator<T>(ptr + sz, true);
    }
    Iterator<T> rbegin() const {
        return Iterator<T>(ptr + sz - 1, false);
    }
    Iterator<T> rend() const {
        return Iterator<T>(ptr, false);
    }
};

int main(int argc, char *argv[]) {
    Vector<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    int m = 0;
    for (auto i = a.begin(); (i != a.end()) && (m < 100); ++i) {
        std::cout << *(i) << std::endl;
        m++;
    }
    for (auto i = a.rbegin(); (i != a.rend()) && (m < 100); ++i) {
        std::cout << *(i) << std::endl;
        m++;
    }
    return 0;
}