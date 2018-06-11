#include <string>
#include <stdint.h>
#include <string.h>
class MyException
{
	private:
	const std::string cause_;
	public:
	MyException();
	MyException(const char *cause);
	~MyException();
	void Handle();
};
MyException::MyException(): cause_("nothing")
{
}
MyException::MyException(const char *cause): cause_(cause)
{
}
MyException::~MyException()
{
}
void MyException::Handle()
{
	std::cout << cause_ << std::endl;
}
/*my own exception class above*/
/*Allocator below*/
template <class T>
class Allocator
{
public:
    template<class U, class... Args> static void construct(U *p, Args&&... args) 
	{
        new(reinterpret_cast<void *>(p)) U(std::forward<Args>(args)...);
    }

    template<class U> static void destroy(U * p) { p->~U(); }

    template<class... Args> static T* allocate(const size_t count, Args&&... args) 
	{
        if (count==0) 
		{
            return nullptr;
        }

        return  static_cast<T*>(operator new[] (count * sizeof(T)));
    }

    static void deallocate(T* ptr, size_t count) 
	{
        for (size_t i=0; i<count; i++) 
		{
            destroy(ptr+i);
        }
        operator delete[] (ptr);
    }
    static void deallocate(T* ptr) 
	{
        operator delete[] (ptr);
    }
    static size_t max_size() noexcept { return std::numeric_limits<size_t>::max(); }
};
/*Allocator above*/
/*Iterator below*/
template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
	private:
	T *p_;
	public:
	/*default-constructible, copy-constructible, copy-assignable and destructible*/
	Iterator();
	Iterator(T *x);
	Iterator(const Iterator &it);
	Iterator& operator=(const Iterator &it);
	~Iterator();
	/*incrementable*/
	Iterator& operator++();
	Iterator operator++(int);
	Iterator& operator--();
	Iterator operator--(int);
	/*comparable*/
	bool operator==(const Iterator& rhs) const;
	bool operator!=(const Iterator& rhs) const;
	/*dereferenceable*/
	T& operator*();
	/*arithmetics*/
	Iterator& operator+(size_t n);
	Iterator& operator-(size_t n);
	int operator-(const Iterator& it);
	/*relative comparable*/
	bool operator>(const Iterator& rhs) const;
	bool operator>=(const Iterator& rhs) const;
	bool operator<=(const Iterator& rhs) const;
	bool operator<(const Iterator& rhs) const;
	/*offset dereference*/
	T& operator[](size_t n);
};
template <class T>
Iterator<T>::Iterator(): p_(nullptr)
{
}
template <class T>
Iterator<T>::Iterator(T *x): p_(x)
{
}
template <class T>
Iterator<T>::Iterator(const Iterator &it): p_(it.p_)
{
}
template <class T>
Iterator<T>::~Iterator()
{
}
template <class T>
Iterator<T>& Iterator<T>::operator=(const Iterator &it)
{
	p_=it.p_;
}
/*boolean operators*/
template <class T>
bool Iterator<T>::operator==(const Iterator& rhs) const
{
	return p_==rhs.p_;
}
template <class T>
bool Iterator<T>::operator!=(const Iterator& rhs) const
{
	return p_!=rhs.p_;
}
template <class T>
bool Iterator<T>::operator>(const Iterator& rhs) const
{
	return p_>rhs.p_;
}
template <class T>
bool Iterator<T>::operator>=(const Iterator& rhs) const
{
	return p_>=rhs.p_;
}
template <class T>
bool Iterator<T>::operator<=(const Iterator& rhs) const
{
	return p_<=rhs.p_;
}
template <class T>
bool Iterator<T>::operator<(const Iterator& rhs) const
{
	return p_<rhs.p_;
}
/*dereference*/
template <class T>
T& Iterator<T>::operator*()
{
	return *p_;
}
template <class T>
T& Iterator<T>::operator[](size_t n)
{
	return *(p_+n);
}
/*arithm*/
template <class T>
Iterator<T>& Iterator<T>::operator+(size_t n)
{
	p_+=n;
	return *this;
}
template <class T>
Iterator<T>& Iterator<T>::operator-(size_t n)
{
	p_-=n;
	return *this;
}
template <class T>
int Iterator<T>::operator-(const Iterator<T> &it)
{
	return p_-it.p_;
}
template <class T>
Iterator<T>& Iterator<T>::operator++()
{
	p_++;
	return *this;
}
template <class T>
Iterator<T> Iterator<T>::operator++(int)
{
	Iterator tmp(*this);
	p_++;
	return tmp;
}
template <class T>
Iterator<T>& Iterator<T>::operator--()
{
	p_--;
	return *this;
}
template <class T>
Iterator<T> Iterator<T>::operator--(int)
{
	Iterator tmp(*this);
	p_--;
	return tmp;
}
/*Iterator above*/
/*Vector below*/
template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator=Iterator<T>;
    using reverse_iterator=std::reverse_iterator<iterator>;

    Vector(const size_t capacity=0) : capacity_(capacity), data_(alloc_.allocate(capacity)), size_(0) {}

    ~Vector() {clear(); alloc_.deallocate(data_, size_);}

    iterator begin() noexcept { return iterator(data_); }
    iterator end() noexcept { return iterator(data_ + size_); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    bool empty() const noexcept { return size_==0; }
    size_t capacity() const noexcept { return capacity_; }
    size_t size() const noexcept { return size_; }

    T& operator[] (const size_t n) 
	{
        if (n>=size_) 
		{
            throw std::out_of_range("vector index out of range");
        }
        return data_[n];
    }

    const T& operator[] (const size_t n) const 
	{
        if (n>=size_) 
		{
            throw std::out_of_range("vector index out of range");
        }
        return data_[n];
    }

    void pop_back() 
	{
        if (size_>0) 
		{
            resize(size_-1);
        }
    }

    void push_back (const T& val)
    {
        if (size_+1>capacity_) 
		{
            failsafe_allocation(size_*2+1);
            capacity_=size_*2+1;
        }
        alloc_.construct(data_+ size_, val);
        ++size_;
    }

    void reserve(const size_t size)
    {
        if (size > capacity_)
        {
            failsafe_allocation(size);
            capacity_ = size;
        }
    }
    void resize(const size_t newSize)
    {
        if (size_ < newSize)
        {
            if (capacity_ < newSize) 
			{
                failsafe_allocation(newSize);
                capacity_= newSize;
            }
            for (size_t i = size_; i<newSize; i++) 
			{
                alloc_.construct(data_+i);
            }
            size_=newSize;
        } 
		else 
		{
            for (size_t i=newSize; i<size_; i++) 
			{
                alloc_.destroy(data_+i);
            }
            size_=newSize;
        }
    }
    void clear() { resize(0); }

private:
    void failsafe_allocation(const size_t size)
    {
        auto newData=alloc_.allocate(size);
        memcpy(newData, data_, size_*sizeof(T));
        std::swap(newData, data_);
        alloc_.deallocate(newData);
    }
    T* data_;
    size_t size_;
    size_t capacity_;
    Alloc alloc_;
};
