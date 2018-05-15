#ifndef HOMEWORK7_VECTOR_H
#define HOMEWORK7_VECTOR_H

#endif //HOMEWORK7_VECTOR_H

#include <iostream>


template<class T>
class Iterator{
    T* host_;
public:
    Iterator() noexcept : host_(nullptr){};
    Iterator(T* ptr) noexcept : host_(ptr){};
    Iterator(const Iterator& oth) noexcept = default;
    Iterator(Iterator&& moved_oth) noexcept = default;

    Iterator& operator=(const Iterator& oth) noexcept = default;
    Iterator& operator=(Iterator&& moved_oth) noexcept = default;

    Iterator& operator++(){
        ++host_;
        return *this;
    }

    Iterator operator++(int){
        Iterator temp(host_);
        ++host_;
        return temp;
    }

    Iterator& operator--(){
        --host_;
        return *this;
    }

    Iterator operator--(int){
        Iterator temp(host_);
        --host_;
        return temp;
    }

    Iterator operator+(int32_t step){
        return Iterator(host_ + step);
    }

    Iterator operator-(int32_t step){
        return Iterator(host_ - step);
    }

    Iterator& operator+=(int32_t step){
        host_ += step;
        return *this;
    }

    Iterator& operator-=(int32_t step){
        host_ -= step;
        return *this;
    }

    T& operator*(){
        return (*host_);
    }

    T* operator->(){
        return &(*host_);
    }

    bool operator==(const Iterator& oth) const{
        return host_ == oth.host_;
    }

    bool operator!=(const Iterator& oth) const{
        return host_ != oth.host_;
    }
};

template<class T>
class ReverseIterator{
    T* host_;
public:
    ReverseIterator() noexcept = default;
    ReverseIterator(T* ptr) noexcept : host_(ptr){};
    ReverseIterator(const ReverseIterator& oth) noexcept = default;
    ReverseIterator(ReverseIterator&& moved_oth) noexcept = default;

    ReverseIterator& operator=(const ReverseIterator& oth) noexcept = default;
    ReverseIterator& operator=(ReverseIterator&& moved_oth) noexcept = default;

    ReverseIterator& operator++(){
        --host_;
        return *this;
    }

    ReverseIterator operator++(int){
        ReverseIterator temp(host_);
        --host_;
        return temp;
    }

    ReverseIterator& operator--(){
        ++host_;
        return *this;
    }

    ReverseIterator operator--(int){
        ReverseIterator temp(host_);
        ++host_;
        return temp;
    }

    ReverseIterator operator+(int32_t step){
        return ReverseIterator(host_ - step);
    }

    ReverseIterator operator-(int32_t step){
        return ReverseIterator(host_ + step);
    }

    ReverseIterator& operator+=(int32_t step){
        host_ -= step;
        return *this;
    }

    ReverseIterator& operator-=(int32_t step){
        host_ += step;
        return *this;
    }

    T& operator*(){
        return (*host_);
    }

    T* operator->(){
        return &(*host_);
    }

    bool operator==(const ReverseIterator& oth) const{
        return host_ == oth.host_;
    }

    bool operator!=(const ReverseIterator& oth) const{
        return host_ != oth.host_;
    }
};

template<class T>
class Allocator{
public:
    T* allocate(size_t size){
        return static_cast<T*> (::operator new(sizeof(T) * size));
    }

    void deallocate(T* ptr){
        ::operator delete(ptr);
    }

    void construct(T *ptr){
        ptr = new(ptr)T();
    }

    void construct(T* ptr, const T& value){
        ptr = new(ptr)T(value);
    }

    void construct(T* ptr, T&& value){
        ptr = new(ptr)T(std::move(value));
    }

    void destroy(T* ptr){
        ptr -> ~T();
    }
};

template<class T, class Alloc=Allocator<T>>
class Vector{
    size_t size_;
    size_t capacity_;
    T* storage_;
    Alloc alloc_;

public:
    Vector(): size_(0),
              capacity_(0),
              storage_(nullptr){};

    Vector(size_t size, const T& value = T()): size_(size),
                                        capacity_(size),
                                        storage_(alloc_.allocate(capacity_)){
        for(size_t it = 0; it < size; ++it){
            alloc_.construct(storage_ + it, value);
        }
    }

    Vector(const Vector& oth): size_(oth.size_),
                               capacity_(oth.size_),
                               storage_(alloc_.allocate(capacity_)){
        for(size_t it = 0; it < size_; ++it){
            alloc_.construct(storage_ + it, oth.storage_[it]);
        }
    }

    Vector(Vector&& oth): size_(oth.size_),
                          capacity_(oth.capacity_),
                          storage_(oth.storage_){
        oth.storage_ = nullptr;
        oth.size_ = 0;
        oth.capacity_ = 0;
    }


    ~Vector(){
        for(size_t it = 0; it < size_; ++it){
            alloc_.destroy(storage_ + it);
        }
        alloc_.deallocate(storage_);
    }

    T& operator[](size_t ind){
        return storage_[ind];
    }

    const T& operator[](size_t ind) const {
        return storage_[ind];
    }

    void push_back(const T& obj){
        if(size_ == capacity_){
            size_t new_capacity = capacity_ * 2 + 1;
            T* ptr = alloc_.allocate(new_capacity);

            for(size_t it = 0; it < size_; ++it) {
                alloc_.construct(ptr + it, storage_[it]);
                alloc_.destroy(storage_ + it);
            }

            alloc_.deallocate(storage_);

            capacity_ = new_capacity;
            storage_ = ptr;
        }
        alloc_.construct(storage_ + size_, obj);
        ++size_;
    }

    void push_back(T&& obj){
        if(size_ == capacity_){
            size_t new_capacity = capacity_ * 2 + 1;
            T* ptr = alloc_.allocate(new_capacity);

            for(size_t it = 0; it < size_; ++it) {
                alloc_.construct(ptr + it, storage_[it]);
                alloc_.destroy(storage_ + it);
            }

            alloc_.deallocate(storage_);

            capacity_ = new_capacity;
            storage_ = ptr;
        }
        alloc_.construct(storage_ + size_, std::move(obj));
        ++size_;
    }

    void pop_back(){
        if(size_){
            --size_;
            alloc_.destroy(storage_ + size_);
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity(){
        return capacity_;
    }

    void clear(){
        for(size_t it = 0; it < size_; ++it){
            alloc_.destroy(storage_ + it);
        }
        size_ = 0;
    }

    void resize(size_t new_size, const T& value = T()){
        if(new_size <= size_){
            for(size_t it = new_size; it < size_; ++it){
                alloc_.destroy(storage_ + it);
            }
            size_ = new_size;
        }else{
            if(new_size > capacity_){
                size_t new_capacity = new_size;
                T* ptr = alloc_.allocate(new_capacity);

                for(size_t it = 0; it < size_; ++it) {
                    alloc_.construct(ptr + it, storage_[it]);
                    alloc_.destroy(storage_ + it);
                }

                alloc_.deallocate(storage_);

                capacity_ = new_capacity;
                storage_ = ptr;
            }
            for(size_t it = size_; it < new_size; ++it)
                alloc_.construct(storage_ + it, value);
            size_ = new_size;
        }
    }

    void reserve(size_t new_capacity){
        if(new_capacity > capacity_){
            T* ptr = alloc_.allocate(new_capacity);

            for(size_t it = 0; it < size_; ++it) {
                alloc_.construct(ptr + it, storage_[it]);
                alloc_.destroy(storage_ + it);
            }

            alloc_.deallocate(storage_);

            capacity_ = new_capacity;
            storage_ = ptr;
        }
    }

    Iterator<T> begin(){
        if(!storage_)
            return nullptr;
        return Iterator<T>(storage_);
    }

    Iterator<T> end(){
        if(!storage_)
            return nullptr;
        return Iterator<T>(storage_ + size_);
    }

    ReverseIterator<T> rbegin(){
        if(!storage_)
            return nullptr;
        return ReverseIterator<T>((storage_ + size_) - 1);
    }

    ReverseIterator<T> rend(){
        if(!storage_)
            return nullptr;
        return ReverseIterator<T>(storage_ - 1);
    }

};