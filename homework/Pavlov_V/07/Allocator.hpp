const long long max_value = std::numeric_limits<size_t>::max();

template <class T> class Allocator {
public:
    T* allocate(size_t count) {
        if (count > max_value)
            throw std::length_error("Error size");
        auto ptr = static_cast<T*>(operator new(sizeof(T) * count));
        return ptr;
    }
    
    void deallocate(T* ptr) {
        operator delete(ptr);
    }
};
