#include <algorithm>
#include <iostream>

// very simple vector implementation
class IntVector {
   public:
     using myint = int;
    // default
    IntVector() : data{new int[10]()}, capacity(10), _size(0) {}

    IntVector(const int* _data, const size_t __size) {
        _size = __size;
        capacity = mult * _size;
        data = new int[capacity];
        for (size_t i = 0; i < _size; i++) {
            data[i] = _data[i];
        }
    }

    IntVector(const size_t __size)
        : data{new int[__size]()}, _size(__size), capacity(2 * __size) {}

    // copy
    IntVector(const IntVector& v) {
        capacity = v.capacity;
        _size = v._size;
        data = new int[v._size];
        std::copy(v.begin(), v.end(), data);
    }

    // move const
    IntVector(IntVector&& moved) {
        capacity = moved.capacity;
        _size = moved._size;
        data = nullptr;
        std::swap(data, moved.data);
        moved.clear();
    }

    // move assigment
    IntVector& operator=(IntVector&& moved) {
        if (this == &moved) return *this;
        delete[] data;
        capacity = moved.capacity;
        _size = moved._size;
        std::swap(data, moved.data);
        moved.clear();
        return *this;
    }

    void clear()
    {
      for (size_t i = 0; i < _size; i++) {
        data[i].~myint();
      }
      capacity = 0;
      _size = 0;
    }

    IntVector& operator=(const IntVector& v) {
        delete[] data;
        capacity = v.capacity;
        _size = v._size;
        data = new int[capacity];
        std::copy(v.begin(), v.end(), data);
        return *this;
    }

    void resize() {
        int* tmp = new int[1 + mult * _size];
        std::copy(data, data + _size, tmp);
        delete[] data;
        data = tmp;
    }

    size_t size() const { return _size; }

    void push_back(const int elem) {
        if (_size == capacity) resize();
        data[_size++] = elem;
    }

    int pop_back() { return data[_size--]; }

    void push_front(const int elem)
    {
      for (size_t i = _size; i > 0; i--) {
        data[i] = data[i-1];
      }
      _size++;
      if (_size == capacity)
        resize();
      data[0] = elem;
    }

    int& operator[](size_t i) {
        if (i < _size) {
            return data[i];
        }
        throw std::out_of_range("indx is not correct");
    }

    int operator[](size_t i) const {
        if (i < _size) {
            return data[i];
        }
        throw std::out_of_range("indx is not correct");
    }

    int* begin() const { return data; }
    int* begin() { return data; }

    int* end() const { return data + _size; }
    int* end() { return data + _size; }

    friend std::ostream& operator<<(std::ostream& os, const IntVector& vector) {
        for (int i = vector.size() - 1; i >= 0; i--) {
            os << vector[i];
        }
        return os;
    }
    ~IntVector() { delete[] data; }

   private:
    int* data;
    size_t capacity;
    size_t _size;
    const static int mult = 2;
};
