#pragma once

template <class T> class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
private:
    T* p;
public:
    explicit Iterator<T>(T* ptr) {
        p = ptr;
    }
    
    Iterator<T> operator ++ () {
        ++p;
        return *this;
    }
    
    Iterator<T> operator -- (int) {
        return Iterator(p--);
    }
    
    Iterator<T> operator ++ (int) {
        return Iterator(p++);;
    }
    
    Iterator<T> operator -- () {
        --p;
        return *this;
    }
    
    bool operator == (const Iterator& tmp) {
        return p == tmp.p;
    }
    
    bool operator != (const Iterator& tmp) {
        return p != tmp.p;
    }
    
    T& operator * () {
        return *p;
    }
    
    Iterator &operator+=(int64_t x) noexcept {
        p += x;
        return *this;
    }
    Iterator &operator-=(int64_t x) noexcept {
        p -= x;
        return *this;
    }
    Iterator operator+(int64_t x) noexcept {
        Iterator result(*this);
        return result += x;
    }
    Iterator operator-(int64_t x) noexcept {
        Iterator result(*this);
        return result -= x;
    }
    uint64_t operator-(const Iterator &other) const noexcept {
        return p - other.p;
    }
    
};

