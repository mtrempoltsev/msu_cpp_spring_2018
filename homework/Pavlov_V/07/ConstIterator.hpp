#pragma once
#include "Iterator.hpp"
#include <vector>


template <class T> class ConstIterator {
private:
    const T *raw_;
public:
    typedef uint64_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef std::random_access_iterator_tag iterator_category;
    ConstIterator() noexcept = default;
    explicit ConstIterator(T *raw) noexcept : raw_(raw) {}
    ConstIterator(const ConstIterator &) noexcept = default;
    ConstIterator(const Iterator<T> &other) noexcept : raw_(other.raw_) {}
    ConstIterator(ConstIterator &&) noexcept = default;
    ConstIterator(Iterator<T> &&other) noexcept : raw_(other.raw_) {}
    ConstIterator &operator=(const ConstIterator &) noexcept = default;
    ConstIterator &operator=(const Iterator<T> &other) noexcept {
        raw_ = other.raw_;
    }
    ConstIterator &operator=(ConstIterator &&) noexcept = default;
    ConstIterator &operator=(Iterator<T> &&other) noexcept {
        raw_ = other.raw_;
    }
    
    const T &operator*() const noexcept { return *raw_; }
    ConstIterator &operator++() noexcept {
        ++raw_;
        return *this;
    }
    const ConstIterator operator++(int) noexcept {
        return ConstIterator(raw_++);
    }
    ConstIterator &operator--() noexcept {
        --raw_;
        return *this;
    }
    const ConstIterator operator--(int) noexcept {
        return ConstIterator(raw_--);
    }
    ConstIterator &operator+=(int64_t x) noexcept {
        raw_ += x;
        return *this;
    }
    ConstIterator &operator-=(int64_t x) noexcept {
        raw_ -= x;
        return *this;
    }
    ConstIterator operator+(int64_t x) noexcept {
        ConstIterator result(*this);
        return result += x;
    }
    ConstIterator operator-(int64_t x) noexcept {
        ConstIterator result(*this);
        return result -= x;
    }
    uint64_t operator-(const ConstIterator &other) const noexcept {
        return raw_ - other.raw_;
    }
    const T *data() const { return raw_; }
    
    bool operator==(const ConstIterator &other) const noexcept {
        return raw_ == other.raw_;
    }
    
    bool operator!=(const ConstIterator &other) const noexcept {
        return raw_ != other.raw_;
    }
};
