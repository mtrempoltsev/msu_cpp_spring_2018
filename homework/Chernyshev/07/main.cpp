//#include <iostream>

// operator[], push_back, pop_back, empty, size, clear, begin, end, rbegin, rend, resize, reserve

template <class T>
class Allocator
{

};

template <class T>
class Iterator
{
    
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;

private:
    Alloc alloc_;
};

int main(){}