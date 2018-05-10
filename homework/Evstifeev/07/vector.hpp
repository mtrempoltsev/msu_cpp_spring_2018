#pragma once
#include <iostream>
#include "allocator.hpp"
#include "iterator.hpp"

template <class T, class Alloc = Allocator<T>>
class Vector {
   public:
    using iterator = Iterator<T>;
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using reverse_iterator = std::reverse_iterator<iterator>;

    Vector() : size_{0}, data_{nullptr}, capacity_{0} {}

    explicit Vector(size_type count)
        : size_{count}, data_{alloc_.allocate(count)}, capacity_{count} {
        for (size_type i = 0; i < size_; i++) {
            alloc_.construct(data_ + i);
        }
    }

    void reserve(size_type new_cap) {
        if (new_cap > capacity_) {
            pointer new_data = alloc_.allocate(new_cap);
            for (size_type i = 0; i < size_; i++) {
                alloc_.construct(new_data + i, data_[i]);
                alloc_.destruct(new_data + i);
            }
            alloc_.deallocate(data_);
            data_ = new_data;
            capacity_ = new_cap;
        }
    }

    void resize(size_type count) {
        if (count < size_) {
            for (size_type i = size_; i > count; i--) {
                alloc_.destruct(data_ + i);
            }
        } else if (count > size_) {
            if (count >= capacity_) reserve(count * 2);
            for (size_type i = size_; i < count; i++) {
                alloc_.construct(data_ + i);
            }
        }
        size_ = count;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) reserve(1 + size_ * 2);
        alloc_.construct(data_ + size_++, value);
    }

    void pop_back() {
        size_--;
        alloc_.destruct(data_ + size_);
    }

    iterator begin() noexcept { return iterator(data_); }

    iterator end() noexcept { return iterator(data_ + size_); }

    reverse_iterator rbegin() noexcept {
        return std::make_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return std::make_reverse_iterator(begin());
    }

    bool empty() const noexcept { return size_ == 0; }

    size_type size() const noexcept { return size_; }

    size_type capacity() const noexcept { return capacity_; }

    reference operator[](const size_type indx) { return data_[indx]; }

    void clear() {
        for (size_type i = 0; i < size_; i++) {
            alloc_.destruct(data_ + i);
        }
        size_ = 0;
    }

    ~Vector() {
        clear();
        alloc_.deallocate(data_);
    }

   private:
    pointer data_;
    size_type size_;
    size_type capacity_;
    Alloc alloc_;
};
