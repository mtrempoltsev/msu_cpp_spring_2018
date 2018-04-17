#pragma once
#include <vector>
#include <cstring>

template <class T> class Allocator {
  public:
    typedef T value_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;

    Allocator() noexcept = default;
    Allocator(const Allocator &) noexcept = default;
    template <class U> explicit Allocator(const Allocator<U> &) noexcept {};

    T *allocate(size_t n) { return static_cast<T*> (::operator new(sizeof(T) * n)); }
    void deallocate(T *p, size_t n) { free(p); }
};

template <class T1, class T2>
bool operator==(const Allocator<T1> &lhs, const Allocator<T2> &rhs) {
    return true;
}

template <class T1, class T2>
bool operator!=(const Allocator<T1> &lhs, const Allocator<T2> &rhs) {
    return false;
}

template <class T> class Iterator {
  public:
    typedef uint64_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef std::random_access_iterator_tag iterator_category;

    Iterator() noexcept = default;
    Iterator(T *raw) noexcept : raw_(raw) {}
    Iterator(const Iterator &) noexcept = default;
    Iterator(Iterator &&) noexcept = default;
    Iterator &operator=(const Iterator &) noexcept = default;
    Iterator &operator=(Iterator &&) noexcept = default;

    T &operator*() const noexcept { return *raw_; }
    Iterator &operator++() noexcept {
        ++raw_;
        return *this;
    }
    const Iterator operator++(int) noexcept { return Iterator(raw_++); }
    Iterator &operator--() noexcept {
        --raw_;
        return *this;
    }
    const Iterator operator--(int) noexcept { return Iterator(raw_--); }
    Iterator &operator+=(int64_t x) noexcept {
        raw_ += x;
        return *this;
    }
    Iterator &operator-=(int64_t x) noexcept {
        raw_ -= x;
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
        return raw_ - other.raw_;
    }
    T *data() const { return raw_; }

    bool operator==(const Iterator &other) const noexcept {
        return raw_ == other.raw_;
    }

    bool operator!=(const Iterator &other) const noexcept {
        return raw_ != other.raw_;
    }

  private:
    T *raw_;
};

template <class T> class ConstIterator {
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

  private:
    const T *raw_;
};

template <class T, class Alloc = Allocator<T>> class Vector {
  public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef T &&move_reference;
    typedef typename std::allocator_traits<Alloc>::pointer pointer;
    typedef typename std::allocator_traits<Alloc>::const_pointer const_pointer;
    typedef Iterator<T> iterator;
    typedef ConstIterator<T> const_iterator;
    typedef typename std::reverse_iterator<iterator> reverse_iterator;
    typedef typename std::reverse_iterator<const_iterator>
        const_reverse_iterator;

    Vector() noexcept(noexcept(allocator_type()))
        : begin_(nullptr), end_(nullptr), capacity_(0){};
    explicit Vector(const allocator_type &alloc) noexcept : alloc_(alloc) {}

    Vector(size_type count, const_reference value)
        : begin_(nullptr), end_(nullptr), capacity_(0) {
        resize(count, value);
    }

    explicit Vector(size_type count)
        : begin_(nullptr), end_(nullptr), capacity_(0) {
        resize(count);
    }

    template <class InputIt> Vector(InputIt first, InputIt last) {
        auto size_ = std::distance(first, last);
        resize(size_);
        for (size_type i = 0; i < size_; ++i) {
            *(begin_ + i) = *first;
            ++first;
        }
    }
    Vector(const Vector &other) : Vector(other.begin_, other.end_) {}
    Vector(Vector &&other) noexcept
        : begin_(std::move(other.begin_)), end_(std::move(other.end_)), capacity_(std::move(other.capacity_)) {
        other.begin_ = nullptr;
        other.end_ = nullptr;
    }

    Vector(std::initializer_list<T> init) : Vector(init.begin(), init.end()) {}

    reference operator[](size_type pos) { return *(begin_ + pos); }
    const_reference operator[](size_type pos) const { return *(begin_ + pos); }

    void push_back(const_reference value) {
        if (size() == capacity_) {
            allocate(capacity_ != 0 ? 2 * capacity_ : 2 * capacity_ + 1);
        }
        *end_ = value;
        ++end_;
    }

    void push_back(move_reference value) {
        if (size() == capacity_) {
            allocate(capacity_ != 0 ? 2 * capacity_ : 2 * capacity_ + 1);
        }
        *end_ = std::move(value);
        ++end_;
    }

    void pop_back() { (--end_)->~value_type(); }

    bool empty() const noexcept { return begin_ == end_; }

    size_type size() const noexcept { return end_ - begin_; }

    void clear() noexcept {
        while (end_ != begin_) {
            (--end_)->~value_type();
        }
    }
    iterator begin() noexcept { return begin_; }
    const_iterator cbegin() const noexcept { return begin_; }
    iterator end() noexcept { return end_; }
    const_iterator cend() const noexcept { return end_; }
    reverse_iterator rbegin() noexcept {
        return std::make_reverse_iterator(end_);
    }
    const_reverse_iterator crbegin() const noexcept {
        return std::make_reverse_iterator(ConstIterator<T>(end_));
    }
    reverse_iterator rend() noexcept {
        return std::make_reverse_iterator(begin_);
    }
    const_reverse_iterator crend() const noexcept {
        return std::make_reverse_iterator(ConstIterator<T>(begin_));
    }

    void resize(size_type count) {
        if (count > size()) {
            if (count > capacity_) {
                while (end_ - begin_ < capacity_) {
                    *end_ = value_type();
                    ++end_;
                }
                allocate(count);
            }
            while (end_ - begin_ < count) {
                *end_ = value_type();
                ++end_;
            }
        } else {
            while (end_ - begin_ > count) {
                (--end_)->~value_type();
            }
        }
        end_ = begin_ + count;
    }
    void resize(size_type count, const value_type &value) {
        if (count <= size()) {
            end_ = begin_ + count;
        } else {
            if (count > capacity_) {
                allocate(count);
            }
            while (end_ - begin_ < count) {
                *end_ = value;
                ++end_;
            }
        }
    }

    void reserve(size_type new_cap) {
        if (new_cap > capacity_) {
            allocate(new_cap);
        }
    }

    size_type capacity() const noexcept { return capacity_; }

    ~Vector() {
        clear();
        if (begin_)
            alloc_.deallocate(begin_, capacity_);
    }

  private:
    void allocate(size_type new_cap) {
        auto size_ = size();
        pointer new_begin = alloc_.allocate(new_cap);
        std::memcpy(new_begin, begin_, size_ * sizeof(value_type));
        if (begin_)
            alloc_.deallocate(begin_, capacity_);
        begin_ = new_begin;
        end_ = begin_ + size_;
        capacity_ = new_cap;
    }

    pointer begin_;
    pointer end_;
    size_type capacity_;
    Alloc alloc_;
};

