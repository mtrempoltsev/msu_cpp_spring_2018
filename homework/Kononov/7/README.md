Написать свой контейнер Vector аналогичный std::vector, аллокатор и итератор произвольного доступа для него. Из поддерживаемых методов достаточно operator[], push_back, pop_back, empty, size, clear, begin, end, rbegin, rend, resize, reserve.

Чтобы тесты проходили, классы должны иметь такие имена:

```c++
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
```

Интерфейс аллокатора и итератора смотрите в документации.

#### Как безопасно увеличить буфер

```c++
template <class T>
class Buffer
{
public:
    Buffer(size_t initialSize = 1024)
        : data_(new T[initialSize])
        , size_(initialSize)
    {
    }

    void resize(size_t newSize)
    {
        if (size_ < newSize)
        {
            auto newData = std::make_unique<T[]>(newSize);
            std::copy(data_.get(), data_.get() + size_, newData.get());
            data_.swap(newData);
            size_ = newSize;
            return;
        }

        assert(!"not implemented yet");
    }

private:
    std::unique_ptr<T[]> data_;
    size_t size_;
};
```
