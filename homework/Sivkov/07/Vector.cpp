#include <iostream>
#include <algorithm>


template<class T>
class my_allocator {
public:
    using value_type = T;
    using pointer = T *;
    using size_type = size_t;

    pointer allocate(size_type count) {
        return static_cast<pointer>(malloc(count * sizeof(value_type)));
    }

    template< class U, class... Args >
    void construct( U* ptr, Args&&... args ){
        new(ptr) U(std::forward<Args>(args)...);
    }

    void destruct(pointer ptr) {
        (*ptr).~T();
    }

    void deallocate(pointer ptr) {
        free(ptr);
    }
};

template<class T, class Alloc>
class Vector;

template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {

public:
    Iterator(typename Iterator::pointer p) : p(p) {}

    Iterator(const Iterator<typename Iterator::value_type> &other) : p(other.p) {}

    Iterator &operator=(const typename Iterator::pointer p_) {
        p = p_;
        return *this;
    }

    Iterator &operator=(const Iterator<typename Iterator::value_type > &other) {
        p = other.p;
        return *this;
    }

    bool operator!=(const Iterator<typename Iterator::value_type > &other) const {
        return p != other;
    }

    template<class U>
    friend bool operator!=(const U *first, const Iterator<U> &second);

    template<class U>
    friend bool operator==(const U *first, const Iterator<U> &second);

    bool operator==(const Iterator<typename Iterator::value_type > &other) const {
        return p == other;
    }

    typename Iterator<typename Iterator::value_type >::reference operator*() const {
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

    typename Iterator::difference_type operator-(const Iterator<typename Iterator::value_type > &other) {
        return static_cast<typename Iterator::difference_type >(p - other.p);
    }

private:
    typename Iterator::pointer p;
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

    ReverseIterator(typename ReverseIterator::pointer p) : p(p) {}

    ReverseIterator(const ReverseIterator<typename ReverseIterator::value_type > &other) : p(other.p) {}

    ReverseIterator &operator=(const typename ReverseIterator::pointer p_) {
        p = p_;
        return *this;
    }

    ReverseIterator &operator=(const ReverseIterator<typename ReverseIterator::value_type> &other) {
        p = other.p;
        return *this;
    }

    bool operator!=(const ReverseIterator<typename ReverseIterator::value_type > &other) const {
        return p != other;
    }

    template<class U>
    friend bool operator!=(const U *first, const ReverseIterator<U> &second);

    template<class U>
    friend bool operator==(const U *first, const ReverseIterator<U> &second);

    bool operator==(const ReverseIterator<typename ReverseIterator::value_type > &other) const {
        return p == other;
    }

    typename ReverseIterator<typename ReverseIterator::value_type >::reference operator*() const {
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

    typename ReverseIterator::difference_type operator-(const ReverseIterator<typename ReverseIterator::value_type > &other) {
        return static_cast<typename ReverseIterator::difference_type>(other.p - p);
    }

private:
    typename ReverseIterator::pointer p;
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
    size_t capacity_ = 0;
    Alloc alloc_;
public:
    Vector() : data_(nullptr), alloc_(Alloc()) {}

    explicit Vector(size_t size, const Alloc &alloc = Alloc()) : alloc_(alloc), size_(size), capacity_(size) {
        data_ = alloc_.allocate(size);
        for (size_t i = 0; i < capacity_; ++i) {
            alloc_.construct(&data_[i]);
        }
    }

    Vector(size_t size, const T &value, const Alloc &alloc = Alloc()) : alloc_(alloc), size_(size), capacity_(size) {
        data_ = alloc_.allocate(size);
        for (size_t i = 0; i < capacity_; ++i) {
            alloc_.construct(&data_[i], value);
        }
    }

    Vector(Vector<T, Alloc> &other) {
        data_ = alloc_.allocate(other.capacity_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (size_t i = 0; i < other.size_; ++i) alloc_.construct(&data_[i], other.data_[i]);
    }

    Vector(Vector<T, Alloc> &&movable) noexcept {
        data_ = movable.data_;
        size_ = movable.size_;
        movable.data_ = nullptr;
        movable.size_ = 0;
        movable.capacity_ = 0;
    }

    Iterator<T> begin() { return Iterator<T>(data_); }

    Iterator<T> end() { return Iterator<T>(data_ + size_); }

    ReverseIterator<T> rbegin() { return ReverseIterator<T>(data_ + size_ - 1); }

    ReverseIterator<T> rend() { return ReverseIterator<T>(data_ - 1); }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T *tmp = alloc_.allocate(new_capacity);
            for (size_t i = 0; i < size_; ++i) {
                alloc_.construct(&tmp[i], data_[i]);
                alloc_.destruct(&data_[i]);
            }
            alloc_.deallocate(data_);
            data_ = tmp;
            capacity_ = new_capacity;
        }
    }

    void resize(size_t count) {

        if (count > capacity_) {
            this->reserve(count);
        }

        if (count > size_) {
            for (size_t i = size_; i < count; ++i) {
                alloc_.construct(&data_[i]);
            }
        } else if (count < size_) {
            for (size_t i = count; i < size_; ++i) {
                alloc_.destruct(&data_[i]);
            }
        }
        size_ = count;
    }

    void push_back(const T &elem) {

        if (size_ == 0) {
            this->reserve(2);
        }

        if (size_ == capacity_) {
            this->reserve(size_ * 2);
        }
        alloc_.construct(&data_[size_], elem);
        size_++;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
            alloc_.destruct(&data_[size_]);
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            alloc_.destruct(&data_[i]);
        }
        size_ = 0;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    T &operator[](size_t index) {
        return data_[index];
    }

    const T &operator[](size_t index) const {
        return data_[index];
    }

    ~Vector() {
        for (size_t i = 0; i < size_; ++i) {
            alloc_.destruct(&data_[i]);
        }
        alloc_.deallocate(data_);
    }
};


int main() {
    return 0;
}