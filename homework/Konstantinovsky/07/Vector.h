#include <memory>
#include <cstring>

template <class T>
class Allocator {
public:
	T * allocate(size_t count);
	void construct(T* ptr, const T &val);
	void construct(T* ptr);
	void destroy(T* ptr);
	void deallocate(T* ptr);
};

template <class T>
T* Allocator<T>::allocate(size_t count) {
	T* ptr;
	ptr = (T*)malloc(count * sizeof(T));
	return ptr;
}

template <class T>
void Allocator<T>::construct(T* ptr, const T &val) {
	ptr = new(ptr) T(val);
}

template <class T>
void Allocator<T>::construct(T* ptr) {
	ptr = new(ptr) T();
}

template <class T>
void Allocator<T>::destroy(T* ptr) {
	ptr->~T();
}

template <class T>
void Allocator<T>::deallocate(T* ptr) {
	free(ptr);
}



template <class T>
class Iterator {
	T* ptr_;
public:
	explicit Iterator(T* ptr) : ptr_(ptr) {}

	bool operator==(const Iterator<T>& other) const;
	bool operator!=(const Iterator<T>& other) const;
	T& operator*() const;
	Iterator& operator++();
	Iterator& operator--();
};

template <class T>
bool Iterator<T>::operator==(const Iterator<T>& other) const {
	return ptr_ == other.ptr_;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const {
	return !(*this == other);
}

template <class T>
T& Iterator<T>::operator*() const {
	return *ptr_;
}

template <class T>
Iterator<T>& Iterator<T>::operator++() {
	++ptr_;
	return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator--() {
	--ptr_;
	return  *this;
}



template<typename T>
class ReverseIterator {
	T* ptr_;
public:
	explicit ReverseIterator(T* ptr) : ptr_(ptr) {}

	bool operator==(const ReverseIterator<T>& other) const;
	bool operator!=(const ReverseIterator<T>& other) const;
	T& operator*() const;
	ReverseIterator& operator++();
	ReverseIterator& operator--();
};

template<typename T>
bool ReverseIterator<T>::operator==(const ReverseIterator<T>& other) const {
	return ptr_ == other.ptr_;
}

template<typename T>
bool ReverseIterator<T>::operator!=(const ReverseIterator<T>& other) const {
	return !(*this == other);
}

template<typename T>
T& ReverseIterator<T>::operator*() const {
	return *ptr_;
}

template<typename T>
ReverseIterator<T>& ReverseIterator<T>::operator++() {
	--ptr_;
	return *this;
}

template<typename T>
ReverseIterator<T>& ReverseIterator<T>::operator--() {
	++ptr_;
	return  *this;
}



template <class T>
class Vector
{
private:
	Allocator<T> alloc_;
	T* data;
	size_t len;
	size_t index;
public:
	Vector(size_t init_cap) { len = 0; index = init_cap; data = alloc_.allocate(init_cap); }
	Vector() { len = 0; index = 10; data = alloc_.allocate(10); }
	T& operator[](size_t ind);
	void push_back(const T &val);

	void pop_back() { resize(len - 1); }
	size_t size() const { return len; }
	size_t capacity() const { return index; }
	bool empty() const { return (len == 0); }
	void clear() { resize(0); }
	Iterator<T> begin() const { return Iterator<T>(data); }
	Iterator<T> end() const { return Iterator<T>(data + len); }
	ReverseIterator<T> rbegin() const { return ReverseIterator<T>(data + len - 1); }
	ReverseIterator<T> rend() const { return ReverseIterator<T>(data - 1); }

	void resize(size_t new_size);
	void reserve(size_t new_cap);
	~Vector();
};

template <class T>
T& Vector<T>::operator[](size_t ind) { return data[ind]; }

template <class T>
void Vector<T>::push_back(const T &val) {
	if (len == index) {
		reserve(index * 2);
	}
	alloc_.construct(data + len, val);
	len++;
}

template <class T>
void Vector<T>::resize(size_t len) {
	if (len > index) {
		reserve(len);
	}

	if (len > this->len) {
		for (size_t i = this->len; i < len; i++) {
			alloc_.construct(data + i);
		}
	}
	else if (len < this->len) {
		for (size_t i = len; i < this->len; i++) {
			alloc_.destroy(data + i);
		}
	}

	this->len = len;
}

template <class T>
void Vector<T>::reserve(size_t index) {
	if (index > this->index) {
		T* tmp_data = alloc_.allocate(index);
		memcpy(tmp_data, data, len * sizeof(T));
		std::swap(data, tmp_data);
		alloc_.deallocate(tmp_data);
		this->index = index;
	}
	else {
		throw std::length_error("");
	}
}

template <class T>
Vector<T>::~Vector() {
	clear();
	alloc_.deallocate(data);
}