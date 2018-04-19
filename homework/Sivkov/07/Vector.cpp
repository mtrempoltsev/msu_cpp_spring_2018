#include <iostream>
#include <algorithm>


template<class T>
class my_allocator {
    size_t size = 0;
public:
    using value_type = T;
    using pointer = T *;
    using size_type = size_t;

    pointer allocate(size_type count) {
        size = count;
        return static_cast<T *>(malloc(count * sizeof(T)));
    }

    void deallocate(pointer ptr) {
        free(ptr);
    }

    size_t max_size() const noexcept { return size; }
};

template<class T, class Alloc>
class Vector;

template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {

public:
    Iterator(T *p) : p(p) {}

    Iterator(const Iterator<T> &other) : p(other.p) {}

    Iterator &operator=(const T *const p_) {
        p = p_;
        return *this;
    }

    Iterator &operator=(const Iterator<T> &other) {
        p = other.p;
        return *this;
    }

    bool operator!=(const Iterator<T> &other) const {
        return p != other;
    }

    template<class U>
    friend bool operator!=(const U *first, const Iterator<U> &second);

    template<class U>
    friend bool operator==(const U *first, const Iterator<U> &second);

    bool operator==(const Iterator<T> &other) const {
        return p == other;
    }

    typename Iterator<T>::reference operator*() const {
        return *p;
    }

    Iterator &operator++() {
        ++p;
        return *this;
    }

    Iterator &operator--() {
        --p;
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp(*this);
        ++p;
        return tmp;
    }

    Iterator operator--(int) {
        Iterator tmp(*this);
        --p;
        return tmp;
    }

    Iterator operator+(const size_t rhs) {
        return Iterator(p + rhs);
    }

    Iterator operator-(const size_t rhs) {
        return Iterator(p - rhs);
    }

    long int operator-(const Iterator<T> &other) {
        return static_cast<long int>(p - other.p);
    }

private:
    T *p;
};

template<class U>
bool operator!=(const U *first, const Iterator<U> &second) {
    return first != second.p;
}

template<class U>
bool operator==(const U *first, const Iterator<U> &second) {
    return first == second.p;
}


template<class T>
class ReverseIterator : public std::iterator<std::random_access_iterator_tag, T> {

public:

    ReverseIterator(T *p) : p(p) {}

    ReverseIterator(const ReverseIterator<T> &other) : p(other.p) {}

    ReverseIterator &operator=(const T *const p_) {
        p = p_;
        return *this;
    }

    ReverseIterator &operator=(const ReverseIterator<T> &other) {
        p = other.p;
        return *this;
    }

    bool operator!=(const ReverseIterator<T> &other) const {
        return p != other;
    }

    template<class U>
    friend bool operator!=(const U *first, const ReverseIterator<U> &second);

    template<class U>
    friend bool operator==(const U *first, const ReverseIterator<U> &second);

    bool operator==(const ReverseIterator<T> &other) const {
        return p == other;
    }

    typename ReverseIterator<T>::reference operator*() const {
        return *p;
    }

    ReverseIterator &operator++() {
        --p;
        return *this;
    }

    ReverseIterator &operator--() {
        ++p;
        return *this;
    }

    ReverseIterator operator++(int) {
        ReverseIterator tmp(*this);
        --p;
        return tmp;
    }

    ReverseIterator operator--(int) {
        ReverseIterator tmp(*this);
        ++p;
        return tmp;
    }

    ReverseIterator operator+(const size_t rhs) {
        return ReverseIterator(p - rhs);
    }

    ReverseIterator operator-(const size_t rhs) {
        return ReverseIterator(p + rhs);
    }

    long int operator-(const ReverseIterator<T> &other) {
        return static_cast<long int>(other.p - p);
    }

private:
    T *p;
};

template<class U>
bool operator!=(const U *first, const ReverseIterator<U> &second) {
    return first != second.p;
}

template<class U>
bool operator==(const U *first, const ReverseIterator<U> &second) {
    return first == second.p;
}


template<class T, class Alloc=my_allocator<T>>
class Vector {
private:
    T *data_;
    size_t size_ = 0;
    Alloc alloc_;
public:
    Vector() : data_(nullptr), alloc_(Alloc()) {}

    explicit Vector(size_t size, const Alloc &alloc = Alloc()) : alloc_(alloc), size_(size) {
        data_ = alloc_.allocate(size);
        for (size_t i = 0; i < alloc_.max_size(); ++i) {
            new(&data_[i]) T();
        }
    }

    Vector(size_t size, const T &value, const Alloc &alloc = Alloc()) : alloc_(alloc), size_(size) {
        data_ = alloc_.allocate(size);
        for (size_t i = 0; i < alloc_.max_size(); ++i) {
            new(&data_[i]) T(value);
        }
    }

    Vector(Vector<T, Alloc> &other) {
        data_ = alloc_.allocate(other.alloc_.max_size());
        size_ = other.size_;
        for (size_t i = 0; i < other.size_; ++i) new(&data_[i]) T(other.data_[i]);
    }

    Vector(Vector<T, Alloc> &&movable) noexcept {
        data_ = movable.data_;
        size_ = movable.size_;
        movable.data_ = nullptr;
    }

    Iterator<T> begin() { return Iterator<T>(data_); }

    Iterator<T> end() { return Iterator<T>(data_ + size_); }

    ReverseIterator<T> rbegin() { return ReverseIterator<T>(data_ + size_ - 1); }

    ReverseIterator<T> rend() { return ReverseIterator<T>(data_ - 1); }

    void reserve(size_t new_max_size) {
        if (new_max_size > alloc_.max_size()) {
            T *tmp = alloc_.allocate(new_max_size);
            for (size_t i = 0; i < size_; ++i) {
                new(&tmp[i]) T(data_[i]);
                data_[i].~T();
            }
            alloc_.deallocate(data_);
            data_ = tmp;
        }
    }

    void resize(size_t count) {

        if (count > alloc_.max_size()) {
            this->reserve(count);
        }

        if (count > size_) {
            for (size_t i = size_; i < count; ++i) {
                new(&data_[i]) T();
            }
        } else if (count < size_) {
            for (size_t i = count; i < size_; ++i) {
                data_[i].~T();
            }
        }
        size_ = count;
    }

    void push_back(const T &elem) {

        if (size_ == 0) {
            this->reserve(2);
        }

        if (size_ == alloc_.max_size()) {
            this->reserve(size_ * 2);
        }
        new(&data_[size_]) T(elem);
        size_++;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
            data_[size_].~T();
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return alloc_.max_size();
    }

    T &operator[](size_t index) {
        return data_[index];
    }

    const T &operator[](size_t index) const {
        return data_[index];
    }

    ~Vector() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        alloc_.deallocate(data_);
    }
};
