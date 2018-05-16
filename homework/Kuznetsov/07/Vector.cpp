#include <iostream>
#include <utility>

template <class T> class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count){
        pointer ptr = (pointer) malloc(sizeof(value_type) * count);
        return ptr;
    }
    void deallocate(pointer ptr){
        free(ptr);
    };

    size_t max_size() const noexcept{
        return std::numeric_limits<size_type>::max();
    };

    void construct(pointer ptr, const value_type &val){
        ptr = new(ptr) value_type(val);
    }
    void construct(pointer ptr) {
        ptr = new(ptr) value_type();
    }

    void destroy(pointer ptr){
        ptr->~value_type();
    }
};

template <class T> class Iterator {
private:
    T *pointer;
public:
    Iterator(T* pointer):pointer(pointer){}
    bool operator==(const Iterator<T> &other) const{
        return pointer == other.pointer;
    }

    bool operator!=(const Iterator<T> &other) const{
        return pointer != other.pointer;
    }

    T& operator*() const{
        return *pointer;
    }

    Iterator& operator++(){
        ++pointer;
        return *this;
    }

    Iterator&operator--(){
        --pointer;
        return *this;
    }

    Iterator operator+(size_t step){
        return Iterator(pointer + step);
    }
    Iterator operator-(size_t step){
        return Iterator(pointer - step);
    }
};

template <class T> class ReverseIterator{
private:
    T *pointer;
public:
    ReverseIterator(T* pointer):pointer(pointer){}
    bool operator==(const ReverseIterator<T> &other) const{
        return pointer == other.pointer;
    }

    bool operator!=(const ReverseIterator<T> &other) const{
        return pointer != other.pointer;
    }

    T& operator*() const{
        return *pointer;
    }

    ReverseIterator& operator++(){
        --pointer;
        return *this;
    }

    ReverseIterator& operator--(){
        ++pointer;
        return *this;
    }

    ReverseIterator operator+(size_t step){
        return ReverseIterator(pointer - step);
    }
    ReverseIterator operator-(size_t step){
        return ReverseIterator(pointer + step);
    }
};

template <class T, class Alloc = Allocator<T> > class Vector {
public:
    using iterator = Iterator<T>;
    using reverse_iterator = ReverseIterator<T>;
    using size_type = size_t;

    Vector(size_type init_capacity = 2):capacity_(init_capacity), size_(0), data_(allocator_.allocate(init_capacity)){
        //empty constructor
    }

    ~Vector(){
        clear();
        allocator_.deallocate(data_);
    }
    T& operator[](size_type i){
        return data_[i];
    }
    const T& operator[](size_type i) const{
        return data_[i];
    }

    bool empty() const{
        return size_ == 0;
    }

    size_type size() const{
        return size_;
    }

    iterator begin() const{
        return iterator(data_);
    }
    iterator end() const{
        return iterator(data_ + size_);
    }

    reverse_iterator rbegin() const{
        return reverse_iterator(data_+size_-1);
    }
    reverse_iterator rend() const{
        return reverse_iterator(data_-1);
    }

    size_type capacity() const{
        return capacity_;
    }

    void reserve(size_type new_capacity) {
        if (capacity_ < new_capacity) {
            T* new_data = allocator_.allocate(new_capacity);
            memcpy(new_data, data_, size_ * sizeof(T));
            std::swap(data_, new_data);
            capacity_ = new_capacity;
            allocator_.deallocate(new_data);
        }
    }
    void resize(size_type new_size){
        if (size_ < new_size)
            reserve(new_size);
        if(new_size > size_)
            for(size_type i = size_; i < new_size; i++)
                allocator_.construct(data_ + i);
        else if(new_size < size_){
            for(size_type i = new_size; i < size_; i++)
                allocator_.destroy(data_ + i);
        }
        size_ = new_size;
    }

    void resize(size_type new_size, T& init){
        if (size_ < new_size)
            reserve(new_size);
        if(new_size > size_)
            for(size_type i = size_; i < new_size; i++)
                allocator_.construct(data_ + i, init);
        else if(new_size < size_){
            for(size_type i = new_size; i < size_; i++)
                allocator_.destroy(data_ + i);
        }
        size_ = new_size;
    }
    void clear(){
        resize(0);
    }

    void push_back(const T& element){
        if(size_ == capacity_)
            reserve(capacity_*2);
        data_[size_] = element;
        ++size_;
    }
    void push_back(T&& element){
        if(size_ == capacity_)
            reserve(capacity_*2);
        data_[size_] = std::move(element);
        ++size_;
    }
    void pop_back(){
        resize(size_ - 1);
    }

private:
    Alloc allocator_;
    T* data_;
    size_type capacity_;
    size_type size_;
};