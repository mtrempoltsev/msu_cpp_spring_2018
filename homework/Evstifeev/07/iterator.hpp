#pragma once
#include <iterator>

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
   public:
    using reference = T&;
    explicit Iterator(T* ptr) : ptr_(ptr) {}

    Iterator(const Iterator<T>& other) : Iterator(other.ptr_) {}
    
    void operator=(const Iterator& other)
    {
      ptr_ = other.ptr_;
    }

    bool operator==(const Iterator<T>& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const {
        return !(*this == other);
    }

    reference operator*() const { return *ptr_; }

    Iterator& operator++() {
        ++ptr_;
        return *this;
    }

    Iterator& operator--() {
        --ptr_;
        return *this;
    }

   private:
    T* ptr_;
};
