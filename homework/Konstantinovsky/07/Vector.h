#include <memory>
#include <cstring>

template <class T>
class Allocator {
public:
	T * allocate(size_t size);
	void construct(T* ans, const T &val);
	void construct(T* ans);
	void destroy(T* ans);
	void deallocate(T* ans);
};

template <class T>
class Iterator {
	T* it;
public:
	explicit Iterator(T* it) { this->it = it; }

	bool operator==(const Iterator<T>& a) const;
	bool operator!=(const Iterator<T>& a) const;
	T& operator*() const;
	Iterator& operator++();
	Iterator& operator--();
};


template<typename T>
class RIterator {
	T* it;
public:
	explicit RIterator(T* it) { this->it = it; }

	bool operator==(const RIterator<T>& a) const;
	bool operator!=(const RIterator<T>& a) const;
	T& operator*() const;
	RIterator& operator++();
	RIterator& operator--();
};

template <class T>
class Vector
{
private:
	Allocator<T> alloc;
	T* data;
	size_t len;
	size_t index;
public:
	Vector(size_t init_cap) { len = 0; index = init_cap; data = alloc.allocate(init_cap); }
	Vector() { len = 0; index = 10; data = alloc.allocate(10); }
	T& operator[](size_t i);
	void push_back(const T &val);

	void pop_back() { resize(len - 1); }
	size_t size() const { return len; }
	size_t capacity() const { return index; }
	bool empty() const { return (len == 0); }
	void clear() { resize(0); }
	Iterator<T> begin() const { return Iterator<T>(data); }
	Iterator<T> end() const { return Iterator<T>(data+len); }
	RIterator<T> rbegin() const { return RIterator<T>(data+len-1); }
	RIterator<T> rend() const { return RIterator<T>(data-1); }

	void resize(size_t len);
	void reserve(size_t index);
	~Vector();
};


template <class T>
T* Allocator<T>::allocate(size_t size) {
	T* ans = (T*)malloc(size * sizeof(T));
	return ans;
}
template <class T> void Allocator<T>::construct(T* ans, const T &val) { ans = new(ans) T(val); }
template <class T> void Allocator<T>::construct(T* ans) { ans = new(ans) T(); }
template <class T> void Allocator<T>::destroy(T* ans) { ans->~T(); }
template <class T> void Allocator<T>::deallocate(T* ans) { free(ans); }


template <class T> bool Iterator<T>::operator==(const Iterator<T>& a) const { return it == a.it; }
template <class T> bool Iterator<T>::operator!=(const Iterator<T>& a) const { return !(*this == a); }
template <class T> T& Iterator<T>::operator*() const { return *it; }
template <class T> Iterator<T>& Iterator<T>::operator++() { ++it; return *this; }
template <class T> Iterator<T>& Iterator<T>::operator--() { --it; return  *this; }


template<typename T> bool RIterator<T>::operator==(const RIterator<T>& a) const { return it == a.it; }
template<typename T> bool RIterator<T>::operator!=(const RIterator<T>& a) const { return !(*this == a); }
template<typename T> T& RIterator<T>::operator*() const { return *it; }
template<typename T> RIterator<T>& RIterator<T>::operator++() { --it; return *this; }
template<typename T> RIterator<T>& RIterator<T>::operator--() { ++it; return *this; }


template <class T> T& Vector<T>::operator[](size_t i) { return data[i]; }
template <class T>
void Vector<T>::push_back(const T &val) {
	if (len == index) {
		reserve(index * 2);
	}
	alloc.construct(data + len, val);
	len++;
}
template <class T>
void Vector<T>::resize(size_t len) {
	if (len > index) {
		reserve(len);
	}

	if (len > this->len) {
		for (size_t i = this->len; i < len; i++) {
			alloc.construct(data + i);
		}
	}
	else if (len < this->len) {
		for (size_t i = len; i < this->len; i++) {
			alloc.destroy(data + i);
		}
	}

	this->len = len;
}
template <class T>
void Vector<T>::reserve(size_t index) {
	if (index > this->index) {
		T* tmp_data = alloc.allocate(index);
		memcpy(tmp_data, data, len * sizeof(T));
		std::swap(data, tmp_data);
		alloc.deallocate(tmp_data);
		this->index = index;
	}
	else {
		throw std::length_error("");
	}
}
template <class T>
Vector<T>::~Vector() {
	clear();
	alloc.deallocate(data);
}