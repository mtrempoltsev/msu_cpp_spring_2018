#include <iostream>
#include <limits>
#include <stdexcept>


template<class T>
class Allocator {
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = size_t;

    pointer allocate(size_type count) {
        if (count > max_size()) {
            throw std::length_error("count > max_size()");
        }
        return static_cast<pointer>(malloc(count * sizeof(value_type)));
    }

    void deallocate(pointer ptr, size_type count) {
        free(ptr);
    }

    void construct(pointer ptr) {
        ptr = new(ptr) T();
    }

    void destroy(pointer ptr) {
        ptr->~T();
    }

    size_t max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
};

template<class T>
class Iterator
        : public std::iterator<std::random_access_iterator_tag, T> {
    T *ptr_;
public:
    using reference = T &;
    using value_type = T;

    explicit Iterator(T *ptr)
            : ptr_(ptr) {
    }

    bool operator==(const Iterator<T> &other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T> &other) const {
        return !(*this == other);
    }

    reference operator*() {
        return *ptr_;
    }

    Iterator &operator++() {
        ++ptr_;
        return *this;
    }

    Iterator &operator--() {
        --ptr_;
        return *this;
    }
};


template<class T,
        class Alloc = Allocator<T>>
class Vector {
public:
    using size_type = size_t;
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_iterator = const Iterator<T>;
    using const_reverse_iterator = const std::reverse_iterator<iterator>;
    using pointer =  typename Alloc::pointer;
    using const_pointer = typename Alloc::const_pointer;


    explicit Vector(size_type count = 0) {
        if (count != 0) {
            data_ = alloc_.allocate(count);
        } else {
            data_ = nullptr;
        }
        size_ = count;
        capacity_ = count;
    }

    iterator begin() noexcept {
        return iterator(data_);
    }

    const_iterator begin() const noexcept {
        return const_iterator(data_);
    }

    iterator end() noexcept {
        return iterator(data_ + size_);
    }

    const_iterator end() const noexcept {
        return const_iterator(data_ + size_);
    }

    reverse_iterator rbegin() noexcept {
        return std::reverse_iterator<iterator>(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return std::reverse_iterator<iterator>(begin());
    }

    reference operator[](size_type pos) {
        return *(data_ + pos);
    }

    const_reference operator[](size_type pos) const {
        return *(data_ + pos);
    }

    void push_back(value_type &&value) {
        if (size_ == capacity_) {
            if (capacity_ == 0) {
                reserve(100);
            } else {
                reserve(2 * capacity_);
            }
        }
        data_[size_] = value;
        ++size_;

    }

    void push_back(const value_type &value) {
        if (size_ == capacity_) {
            if (capacity_ == 0) {
                reserve(100);
            } else {
                reserve(2 * capacity_);
            }
        }
        data_[size_] = value;
        ++size_;
    }

    void pop_back() {
        if (size_ != 0) {
//            data_[--size_].~T();
            alloc_.destroy(data_ + --size_);
        }
    }


    void reserve(size_type new_cap) {
        if (new_cap > capacity_) {
            auto newData = alloc_.allocate(new_cap);
//            std::copy(data_, data_ + size_ * sizeof(value_type), newData);
            for (int i = 0; i < size_; ++i) {
//                newData[i].~T();
                alloc_.destroy(newData + i);
                newData[i] = data_[i];
            }
            std::swap(data_, newData);
            alloc_.deallocate(newData, capacity_);
            capacity_ = new_cap;
        }
    }

    size_type capacity() const noexcept {
        return capacity_;
    }

    void resize(size_type newSize) {
        if (size_ > newSize) {
            for (size_type i = newSize; i < size_; ++i) {
//                data_[i].~T();
                alloc_.destroy(data_ + i);
            };
        } else if (newSize > capacity_) {
            reserve(newSize);
            for (int i = size_; i < newSize; ++i) {
//                data_[i] = T{};
                alloc_.construct(data_ + i);
            };
        } else {
            for (size_type i = size_; i < newSize; ++i) {
//                data_[i] = T{};
                alloc_.construct(data_ + i);
            };
        }
        size_ = newSize;
    }

    bool empty() {
        return size_ == 0;
    }

    size_type size() {
        return size_;
    }


    void clear() noexcept {
        for (int i = 0; i < size_; ++i) {
//            data_[i].~T();
            alloc_.destroy(data_ + i);
        };
        size_ = 0;
    }

    ~Vector() {
        clear();
        alloc_.deallocate(data_, capacity_);
        capacity_ = 0;
    }

private:
    Alloc alloc_;
    pointer data_;
    size_type size_;
    size_type capacity_;
};
