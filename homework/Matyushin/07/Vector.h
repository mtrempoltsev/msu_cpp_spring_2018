#include <iostream>
#include <iterator>
#include <limits>

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>{
private:    
    T* ptr;
public:
    Iterator(T* pointer):
                        ptr(pointer){}

    bool operator==(const Iterator<T> &other) const{
        return other.ptr == ptr;
    }

    bool operator!=(const Iterator<T> &other) const{
        return !(other == *this);
    }

    T& operator*() const{
        return *ptr;
    }

    Iterator& operator++(){
        ptr++;
        return *this;
    }

    Iterator& operator--(){
        ptr--;
        return *this;
    }
};


template <class T>
class Allocator{
public:
    void construct(T* ptr){
        ptr = new (ptr)T();
    }

    void construct(T* ptr, const T& val){
        ptr = new (ptr)T(val);
    }

    void construct(T* ptr, T&& val){
        ptr = new (ptr)T(std::move(val));
    }

    void destroy(T* ptr){
        ptr->~T();
    }


    T* allocate(long int count=1024){
        T* ptr = (T*)malloc(sizeof(T)*count);
        return ptr;
    }

    void deallocate(T* ptr){
        free(ptr);
    }

    long int max_size() const noexcept{
        return std::numeric_limits<long int>::max();
    }
};

template <class T, class Alloc = Allocator<T>>
class Vector{
private:
    Alloc all;
    long int capct = 1024;
    long int sz = 0;
    T* data = nullptr;
public:
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using type = T;

    Vector(long int initsize = 0){
        data = all.allocate(capct);
        sz = initsize;
    }

    const T& operator[](long int i) const{
        return data[i];
    }

    T& operator[](long int i){
        return data[i];
    }

    void reserve(long int nsize){
        if (nsize > capct){
            T* newData = all.allocate(nsize);
            std::copy(data, data + sz, newData);
            std::swap(data, newData);
            all.deallocate(newData);
            capct = nsize;
        }
    }
    
    void resize(long int nsize){
        if(capct < nsize)
            reserve(nsize);
        
        if (nsize < sz)
            for (long int i = nsize; i < sz; i++)
                all.destroy(data + i);
        
        if (nsize > sz)
            for (long int i = sz; i < nsize; i++)
                all.construct(data + i);
        
        sz = nsize;
    }

    void pop_back(){
        if(sz > 0)
            resize(sz-1);
    }

    void push_back(T&& elem){
        if(sz != capct){
            all.construct(data + sz, std::move(elem));
            sz++;
        }
        
        else{
            this->reserve(2*capct);
            all.construct(data + sz, std::move(elem));
            sz++;
        }
    }

    void push_back(const T& elem){
        if(sz != capct){
            all.construct(data + sz, elem);
            sz++;
        }
        
        else{
            this->reserve(2*capct);
            all.construct(data + sz, elem);
            sz++;
        }
    }

    bool empty() const noexcept{
        return (sz == 0);
    }

    void clear() noexcept{
        resize(0);
    }

    long int size() const noexcept{
        return sz;
    }
    
    long int capacity() const noexcept{
        return capct;
    }
    
    iterator begin() noexcept{
        return iterator(data);
    }

    iterator end() noexcept{
        return iterator(data + sz);
    }

    std::reverse_iterator<iterator> rbegin() noexcept{
        return std::reverse_iterator<iterator>(end());
    }

    std::reverse_iterator<iterator> rend() noexcept{
        return std::reverse_iterator<iterator>(begin());
    }
    const_iterator begin() const noexcept{
        return const_iterator(data);
    }

    const_iterator end() const noexcept{
        return const_iterator(data+sz);
    }
    
    std::reverse_iterator<const_iterator>rbegin() const noexcept{
        return std::reverse_iterator<const_iterator>(end());
    }

    std::reverse_iterator<const_iterator> rend() const noexcept{
        return std::reverse_iterator<const_iterator>(begin());
    }
    
    ~Vector(){
        clear();
        all.deallocate(data);
    }
};
