#pragma once
#include <iostream>

template <class T>
class Allocator {
   public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count) {
        return static_cast<pointer>(::operator new(count * sizeof(value_type)));
    }

    template <class... Args>
    void construct(pointer xptr, Args&&... args) {
        new (xptr) value_type(std::forward<Args>(args)...);
    }

    void destruct(pointer xptr) { xptr->~value_type(); }

    void deallocate(pointer ptr) { ::operator delete(ptr); }
};
