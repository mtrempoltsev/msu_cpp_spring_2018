#include <iterator>
#include <limits>

template <class T>
struct Allocator
{
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;
    pointer allocate(size_type count);
    void deallocate(pointer ptr, size_type count);
    template<class U, class... Args> void construct(U *p, Args&&... args);
    template<class U> void destroy(U *p);
    size_t max_size() const noexcept;
};

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;

    explicit Iterator(pointer ptr_): ptr(ptr_) {}

    // Iterator
    reference operator*() const;
    Iterator &operator++();

    // ForwardIterator
    bool operator==(const Iterator<T> &other) const;
    bool operator!=(const Iterator<T> &other) const;
    Iterator operator++(int);
    pointer operator->() const;

    // BidirectionalIterator
    Iterator &operator--();
    Iterator operator--(int);

    // RandomAccessIterator
    Iterator operator+(int n) const;
    Iterator operator-(int n) const;
    Iterator &operator+=(int n);
    Iterator &operator-=(int n);
    difference_type operator-(const Iterator &other);
    reference operator[](size_t n);
    const_reference operator[](size_t n) const;
    bool operator>(const Iterator<T> &other) const;
    bool operator<(const Iterator<T> &other) const;
    bool operator>=(const Iterator<T> &other) const;
    bool operator<=(const Iterator<T> &other) const;

    template <class U>
    friend Iterator<U> operator+(int n, const Iterator<U> &it);
private:
    pointer ptr = nullptr;
};


template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using value_type = T;
    using allocator_type = Alloc;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr size_type MIN_SIZE = 10;
    static constexpr size_type MIN_DELTA = 1;
    static constexpr size_type MULTIPLIER = 2;

    explicit Vector(size_type count = 0);
    Vector(size_type count, const value_type& value);
    Vector(const Vector &other);
    Vector(Vector &&other);
    ~Vector();

    reference operator[](size_t n);
    const_reference operator[](size_t n) const;
    void push_back(const_reference value);
    void pop_back();
    bool empty() const;
    size_type size() const;
    size_type capacity() const;
    void clear();
    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();
    void resize(size_type count);
    void resize(size_type count, const value_type& value);
    void reserve(size_type new_cap);
private:
    allocator_type alloc;
    pointer data = nullptr;
    size_type cur_size = 0;
    size_type cur_capacity = 0;
};

// Class Allocator
// 
template <class T>
typename Allocator<T>::pointer
Allocator<T>::address(reference x) const noexcept
{
    return reinterpret_cast<pointer>(
        &const_cast<char&>(reinterpret_cast<const volatile char&>(x))
    );
}

template <class T>
typename Allocator<T>::const_pointer
Allocator<T>::address(const_reference x) const noexcept
{
    return reinterpret_cast<const_pointer>(
        &const_cast<char&>(reinterpret_cast<const volatile char&>(x))
    );
}

template <class T>
typename Allocator<T>::pointer Allocator<T>::allocate(size_type count)
{
    return static_cast<pointer>(::operator new(count * sizeof(T)));
}

template <class T>
void Allocator<T>::deallocate(pointer ptr, size_type count)
{
    ::operator delete(ptr);
}

template <class T>
template <class U, class... Args>
void Allocator<T>::construct(U *p, Args&&... args)
{
    ::new(reinterpret_cast<void *>(p)) U(std::forward<Args>(args)...);
}

template <class T>
template <class U>
void Allocator<T>::destroy(U *p)
{
    p->~U();
}

template <class T>
size_t Allocator<T>::max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
}

// Class Iterator
// 
template <class T>
typename Iterator<T>::reference Iterator<T>::operator*() const
{
    return *ptr;
}

template <class T>
Iterator<T> &Iterator<T>::operator++()
{
    ++ptr;
    return *this;
}

template <class T>
bool Iterator<T>::operator==(const Iterator<T>& other) const
{
    return ptr == other.ptr;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const
{
    return !(*this == other);
}

template <class T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <class T>
typename Iterator<T>::pointer Iterator<T>::operator->() const
{
    return ptr;
}

template <class T>
Iterator<T> &Iterator<T>::operator--()
{
    --ptr;
    return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator--(int)
{
    Iterator tmp(*this);
    --(*this);
    return tmp;
}

template <class T>
Iterator<T> Iterator<T>::operator+(int n) const
{
    return Iterator<T>(ptr + n);
}

template <class T>
Iterator<T> Iterator<T>::operator-(int n) const
{
    return Iterator<T>(ptr - n);
}

template <class T>
Iterator<T> &Iterator<T>::operator+=(int n)
{
    ptr += n;
    return *this;
}

template <class T>
Iterator<T> &Iterator<T>::operator-=(int n)
{
    ptr -= n;
    return *this;
}

template <class T>
typename Iterator<T>::difference_type
Iterator<T>::operator-(const Iterator<T>& other)
{
    return ptr - other.ptr;
}

template <class T>
typename Iterator<T>::reference Iterator<T>::operator[](size_t n)
{
    return *(ptr + n);
}

template <class T>
typename Iterator<T>::const_reference Iterator<T>::operator[](size_t n) const
{
    return *(ptr + n);
}

template <class T>
bool Iterator<T>::operator>(const Iterator<T> &other) const
{
    return ptr > other.ptr;
}

template <class T>
bool Iterator<T>::operator<(const Iterator<T> &other) const
{
    return ptr < other.ptr;
}

template <class T>
bool Iterator<T>::operator>=(const Iterator<T> &other) const
{
    return !(ptr < other.ptr);
}

template <class T>
bool Iterator<T>::operator<=(const Iterator<T> &other) const
{
    return !(ptr > other.ptr);
}

template <class U>
Iterator<U> operator+(int n, const Iterator<U> &it)
{
    return it + n;
}

// Class Vector
// 
template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_type count)
{
    if(count) {
        reserve(count + MIN_DELTA);
        cur_size = count;
        for(int i = 0; i < cur_size; ++i) {
            alloc.construct(data + i);
        }
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_type count, const value_type& value)
{
    if(count) {
        reserve(count + MIN_DELTA);
        cur_size = count;
        for(int i = 0; i < cur_size; ++i) {
            alloc.construct(data + i, value);
        }
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(const Vector &other)
{
    pointer tmp_data = nullptr;
    if(other.cur_capacity) {
        tmp_data = alloc.allocate(cur_capacity);
    }
    clear();
    alloc.deallocate(data, cur_size);
    cur_size = other.cur_size;
    cur_capacity = other.cur_capacity;
    data = tmp_data;
    for(int i = 0; i < cur_size; ++i) {
        alloc.construct(data + i, other[i]);
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(Vector &&other)
{
    clear();
    alloc.deallocate(data, cur_size);
    cur_size = other.cur_size;
    cur_capacity = other.cur_capacity;
    data = other.data;

    other.cur_size = 0;
    other.cur_capacity = 0;
    other.data = nullptr;
}

template <class T, class Alloc>
Vector<T, Alloc>::~Vector()
{
    clear();
    alloc.deallocate(data, cur_size);
}

template <class T, class Alloc>
typename Vector<T, Alloc>::reference
Vector<T, Alloc>::operator[](size_t n)
{
    return data[n];
}

template <class T, class Alloc>
typename Vector<T, Alloc>::const_reference
Vector<T, Alloc>::operator[](size_t n) const
{
    return data[n];
}

template <class T, class Alloc>
void Vector<T, Alloc>::push_back(const_reference value)
{
    if(cur_size == cur_capacity) {
        reserve(cur_capacity * MULTIPLIER);
    }
    data[cur_size] = value;
    ++cur_size;
}

template <class T, class Alloc>
void Vector<T, Alloc>::pop_back()
{
    if(cur_size > 0) {
        --cur_size;
        alloc.destroy(data + cur_size);
    }
}

template <class T, class Alloc>
bool Vector<T, Alloc>::empty() const
{
    return cur_size == 0;
}

template <class T, class Alloc>
typename Vector<T, Alloc>::size_type Vector<T, Alloc>::size() const
{
    return cur_size;
}

template <class T, class Alloc>
typename Vector<T, Alloc>::size_type Vector<T, Alloc>::capacity() const
{
    return cur_capacity;
}

template <class T, class Alloc>
void Vector<T, Alloc>::clear()
{
    while(cur_size) {
        --cur_size;
        alloc.destroy(data + cur_size);
    }
}

template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::begin()
{
    return iterator(data);
}

template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::end()
{
    return iterator(data + cur_size);
}

template <class T, class Alloc>
typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rbegin()
{
    return reverse_iterator(iterator(data + cur_size));
}

template <class T, class Alloc>
typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rend()
{
    return reverse_iterator(iterator(data));
}

template <class T, class Alloc>
void Vector<T, Alloc>::resize(size_type count)
{
    if(cur_size > count) {
        for(int i = count; i < cur_size; ++i) {
            alloc.destroy(data + i);
        }
        cur_size = count;
    } else {
        if(cur_capacity < count) {
            reserve(count + MIN_DELTA);
        }
        for(int i = cur_size; i < count; ++i) {
            alloc.construct(data + i);
        }
        cur_size = count;
    }
}

template <class T, class Alloc>
void Vector<T, Alloc>::resize(size_type count, const value_type& value)
{
    if(cur_size > count) {
        for(int i = count; i < cur_size; ++i) {
            alloc.destroy(data + i);
        }
        cur_size = count;
    } else {
        if(cur_capacity < count) {
            reserve(count + MIN_DELTA);
        }
        for(int i = cur_size; i < count; ++i) {
            alloc.construct(data + i, value);
        }
        cur_size = count;
    }
}

template <class T, class Alloc>
void Vector<T, Alloc>::reserve(size_type new_cap)
{
    if(new_cap < MIN_SIZE) {
        new_cap = MIN_SIZE;
    }
    if(cur_capacity < new_cap) {
        pointer tmp_data = alloc.allocate(new_cap);
        for(int i = 0; i < cur_size; ++i) {
            alloc.construct(tmp_data + i, data[i]);
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, cur_capacity);
        data = tmp_data;
        cur_capacity = new_cap;
    }
}
