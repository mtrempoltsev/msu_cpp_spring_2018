template<class T>
class allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count);
    void deallocate(pointer ptr, size_type count);

    size_t max_size() const noexcept;
};


template<class T, class Allocator = allocator<T>>
class Vector
{
public:
	Vector();
	Vector(int l, const T& initial);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& moved);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& moved);
	~Vector();

  iterator begin();
  iterator end();
  iterator rbegin();
  iterator rend();

	T& operator[](size_t i);
	const T& operator[](size_t i) const;
	void push_back(const T& x);
	void pop_back();
	void push_front(const T& x);
  void resize(size_t newSize);
  void resize(size_t newsize, const T& defaultValue);
  void reserve(size_type count);
	size_t size() const;
	size_t capacity();


private:
  Allocator alloc;
	std::unique_ptr<T[]> _array;
	size_t _size;
	size_t _capacity;
	void resize();
};

template<class T>
Vector<T>::Vector()
  : _capacity(4)
  , _array(alloc.allocate(4))
  , _size(0)
{
}

template<class T>
Vector<T>::Vector(int l)
  : _capacity(l)
  , _array(alloc.allocate(l))
  , _size(l)
{
	for (int i = 0; i < l; i++)
		_array[i] = T();
}

template<class T>
Vector<T>::Vector(const Vector<T> & other)
:	_capacity(other._capacity)
, _size(other._size)
, _array(other._array)
{
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector<T> & other)
{
	if (this != &other) {
		_array = std::unique_ptr<T[]>(other._array);
		_capacity = other._capacity;
		_size = other._size;
	}
	return *this;
}

template<class T>
Vector<T>::Vector(Vector && moved) :
	_capacity(moved._capacity), _size(moved._size)
{
	_array = moved._array;
	moved._array = nullptr;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& moved)
{
	if (this != &moved) {
		delete[] _array;
		_array = moved._array;
		_capacity = moved._capacity;
		_size = moved._size;
		moved._array = nullptr;
	}
	return *this;
}

template<class T>
Vector<T>::~Vector()
{

	delete[] _array;
}

template<class T>
T& Vector<T>::operator[](size_t i)
{
	return _array[i];
}

template<class T>
const T& Vector<T>::operator[](size_t i) const
{
	return _array[i];
}

template<class T>
void Vector<T>::push_back(const T& x)
{
	if (_size == _capacity) {
		resize();
	}
	_array[_size++] = x;
}

template<class T>
inline void Vector<T>::pop()
{
	if (_size > 0) {
		_size--;
	}
	return;
}

template<class T>
inline void Vector<T>::push_front(const T& x)
{
	if (_size == _capacity) {
		resize();
	}
	if (_size > 0) {
		for (size_t i = _size; i > 0; i--) {
			_array[i] = _array[i - 1];
		}
	}
	_size++;
	_array[0] = x;
}

template<class T>
size_t Vector<T>::size() const
{
	return _size;
}

template<class T>
size_t Vector<T>::capacity()
{
	return _capacity;
}

template<class T>
void Vector<T>::resize()
{
	_capacity *= 2;
	T* newMem = new T[_capacity];
	std::copy(_array, _array + _size, newMem);
	delete[] _array;
	_array = newMem;
}
