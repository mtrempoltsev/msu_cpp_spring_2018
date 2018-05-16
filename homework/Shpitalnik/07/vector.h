#include <memory>
#include <cstring>
template <class T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;
    pointer allocate(size_type count){
        pointer ptr;
        ptr = (pointer)malloc(count * sizeof(value_type));
        return ptr;
    }
    void construct(pointer ptr, const value_type &val){
        ptr = new(ptr) value_type(val);
    }
    void construct(pointer ptr)
    {
        ptr = new(ptr) value_type();
    }
    void destroy(pointer ptr){
        ptr -> ~value_type();
    }
    void deallocate(pointer ptr){
        free(ptr);
    }

};



template <class T>
class Iterator {
    T* ptr_;
public:
    using reference = T&;
    explicit Iterator(T* ptr) : ptr_(ptr){}

    bool operator==(const Iterator<T>& other) const{
        return ptr_ == other.ptr_;
    }
    bool operator!=(const Iterator<T>& other) const{
        return !(*this == other);
    }
    reference operator*() const{
        return *ptr_;
    }
    Iterator& operator++(){
        ++ptr_;
        return *this;
    }
    Iterator& operator--(){
        --ptr_;
        return  *this;
    }
   
};

template<typename T>
class ReverseIterator{
    T* ptr_;
public:
    using reference = T&;
    explicit ReverseIterator(T* ptr) : ptr_(ptr){}

    bool operator==(const ReverseIterator<T>& other) const{
        return ptr_ == other.ptr_;
    }
    bool operator!=(const ReverseIterator<T>& other) const{
        return !(*this == other);
    }
    reference operator*() const{
        return *ptr_;
    }
    ReverseIterator& operator++(){
        --ptr_;
        return *this;
    }
    ReverseIterator& operator--(){
        ++ptr_;
        return  *this;
    }
  
};



template <class T, class Alloc = Allocator<T>>
class Vector
{

public:
    using iterator = Iterator<T>;
    using riterator = ReverseIterator<T>;
    using size_type = size_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Vector(size_t init_cap = 10): vec_size(0), vec_cap(init_cap), data(alloc_.allocate(init_cap)){
        //for(int i = 0; i<vec_size; i++)
        //    alloc_.construct(data+i, NULL);
    }

    T& operator[](size_t ind){
        return data[ind];
    }

    void push_back(const value_type &val){
        if(vec_size == vec_cap)
            reserve(vec_cap*2);
        alloc_.construct(data+vec_size, val);
        vec_size++;
    }

    void pop_back(){
        resize(vec_size-1);
    }

    size_type size() const{
        return vec_size;
    }

    size_type capacity() const{
        return vec_cap;
    }

    bool empty() const{
        return (vec_size == 0);
    }

    void clear(){
        resize(0);
    }

    iterator begin() const {
        return iterator(data);
    }

    iterator end() const{
        return iterator(data+vec_size);
    }

    riterator rbegin() const{
        return riterator(data+vec_size-1);
    }

    riterator rend() const{
        return riterator(data-1);
    }

    void resize(size_type new_size){
        if (new_size > vec_cap)
            reserve(new_size);
        if(new_size > vec_size)
            for(size_type i = vec_size; i < new_size; i++)
                alloc_.construct(data + i);
        else if (new_size < vec_size)
            for(size_type i = new_size; i < vec_size; i++)
                alloc_.destroy(data + i);
        vec_size = new_size;

    }

    void reserve(size_type new_cap){
        if(new_cap > vec_cap){
            pointer tmp_data = alloc_.allocate(new_cap);
            memcpy(tmp_data, data, vec_size * sizeof(value_type));
            std::swap(data, tmp_data);
            alloc_.deallocate(tmp_data);
            vec_cap = new_cap;
        }else
            throw std::length_error("Can't resize capacity");
    }

    ~Vector(){
        clear();
        alloc_.deallocate(data);
    }

private:
    Alloc alloc_;
    pointer data;
    size_type vec_size;
    size_type vec_cap;
};
