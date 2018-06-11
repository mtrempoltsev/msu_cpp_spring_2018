#include <algorithm>

class BigInt
{
    using Character = signed char;

    Character *array = nullptr;
    size_t max_ = 32;
    size_t sec_size = 0;
    bool is_true = true;

    void wide(size_t con = 32);
    void displace();
    void norm_1();
    void norm_2();
public:
    BigInt(int64_t number = 0);
    BigInt(const BigInt &other);
    BigInt(BigInt &&other);
    ~BigInt() { delete[] array; }

    friend bool operator<(const BigInt &first, const BigInt &second);
    friend bool operator>(const BigInt &first, const BigInt &second);
    friend BigInt operator+(const BigInt &first, const BigInt &second);
    friend BigInt operator-(const BigInt &first, const BigInt &second);
    friend BigInt operator*(const BigInt &first, const BigInt &second);
    friend BigInt operator/(const BigInt &first, const BigInt &second);
    BigInt &operator=(const BigInt &other);
    BigInt &operator=(BigInt &&other);
    BigInt operator-() const;
    friend bool operator==(const BigInt &first, const BigInt &second);
    friend bool operator!=(const BigInt &first, const BigInt &second);

    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);

};

std::ostream& operator<<(std::ostream& out, const BigInt& value)
{
    std::string minus = "-";
    if(value.sec_size == 0)
    {
        out << 0;
    }
    else {
        if(!value.is_true)
        {
            out << minus;
        }
        for (size_t i = value.sec_size; i > 0; --i)
        {
            out << int(value.array[i - 1]);
        }
    }
}


BigInt::BigInt(int64_t number)
{
    array = new Character[max_]();
    if(number < 0) {
        is_true = false;
        array[sec_size] = number % 10;
        if (array[sec_size] < 0) {
            array[sec_size] = -array[sec_size];
        }
        ++sec_size;
        number = -(number / 10);
    }

    while(number != 0 && sec_size < max_)
    {
        array[sec_size] = number % 10;
        ++sec_size;
        number /= 10;
    }
}

BigInt::BigInt(const BigInt &other)
{
    sec_size = other.sec_size;
    is_true = other.is_true;
    max_ = other.max_;
    array = new Character[max_]();
    for(size_t j = 0; j < sec_size; ++j){
        array[j] = other.array[j];
    }
}

BigInt::BigInt(BigInt &&moved)
{
    is_true = moved.is_true;
    sec_size = moved.sec_size;
    max_ = moved.max_;
    array = std::move(moved.array);
    moved.array = nullptr;
}

bool operator>(const BigInt &first, const BigInt &second)
{
    return (first != second) && (first - second).is_true;
}

bool operator<(const BigInt &first, const BigInt &second)
{
    return (first != second) && (second - first).is_true;
}

BigInt operator+(const BigInt &first, const BigInt &second)
{
    if(first.sec_size == 0)
    {
        if(second.sec_size == 0)
        {
            return BigInt(0);
        }
    }

    if(first.is_true != second.is_true)
    {
        return first - (-second);
    }

    const BigInt *a = &first;
    const BigInt *b = &second;

    if(second.sec_size > first.sec_size)
    {
        a = &second;
        b = &first;
    }
    BigInt tmp(*a);
    for(size_t i = 0; i < b->sec_size; ++i)
    {
        tmp.array[i] += b->array[i];
    }
    tmp.norm_2();
    return tmp;
}

BigInt BigInt::operator-() const
{
    BigInt tmp(*this);
    tmp.is_true = !is_true;
    return tmp;
}

BigInt operator-(const BigInt &first, const BigInt &second)
{
    if(first.sec_size == 0)
    {
        if(second.sec_size == 0)
        {
            return BigInt(0);
        }
    }
    if(first.is_true != second.is_true)
    {
        return first + (-second);
    }
    if(first.sec_size > second.sec_size)
    {
        BigInt tmp(first);

        for(size_t i = 0; i < second.sec_size; ++i)
        {
            tmp.array[i] -= second.array[i];
        }

        tmp.norm_1();
        return tmp;
    }
    BigInt tmp(second);

    for(size_t i = 0; i < second.sec_size; ++i)
    {
        tmp.array[i] = -tmp.array[i];
    }

    for(size_t i = 0; i < first.sec_size; ++i)
    {
        tmp.array[i] += first.array[i];
    }
    tmp.norm_1();
    return tmp;
}

bool operator>=(const BigInt &first, const BigInt &second)
{
    return (first == second) || (first > second);
}

bool operator<=(const BigInt &first, const BigInt &second)
{
    return (first == second) || (first < second);
}

BigInt &BigInt::operator=(const BigInt &other)
{
    max_ = other.max_;
    is_true = other.is_true;
    sec_size = other.sec_size;
    delete[] array;
    array = new Character[max_]();
    for(size_t i = 0; i < sec_size; ++i)
    {
        array[i] = other.array[i];
    }
    return *this;
}

BigInt &BigInt::operator=(BigInt &&other)
{
    max_ = other.max_;
    is_true = other.is_true;
    sec_size = other.sec_size;
    delete[] array;
    array = other.array;
    other.array = nullptr;
    return *this;
}

bool operator==(const BigInt &first, const BigInt &second)
{
    return !((first - second).sec_size);
}

bool operator!=(const BigInt &first, const BigInt &second)
{
    return !(first == second);
}

void BigInt::displace()
{
    if(sec_size == max_)
    {
        wide();
    }
    ++sec_size;
    for(size_t i = sec_size - 1; i > 0; --i)
    {
        array[i] = array[i - 1];
    }
    array[0] = 0;
}


BigInt operator*(const BigInt &first, const BigInt &second)
{
    if(first.sec_size == 0 || second.sec_size == 0)
    {
        return BigInt(0);
    }

    BigInt tmp = BigInt();
    BigInt displace_tmp(first);
    displace_tmp.is_true = true;

    for(size_t i = 0; i < second.sec_size; ++i)
    {
        BigInt loc_tmp(displace_tmp);
        for(size_t j = i; j < loc_tmp.sec_size; ++j)
        {
            loc_tmp.array[j] *= second.array[i];
        }
        tmp = loc_tmp + tmp;
        displace_tmp.displace();
    }
    tmp.is_true = !(first.is_true ^ second.is_true);
    return tmp;
}

BigInt operator/(const BigInt &first, const BigInt &second)
{
    if(first == 0)
    {
        return BigInt(0);
    }

    BigInt a(first), b(second), c(0);

    a.is_true = true;
    b.is_true = true;
    a >= b;

    while(a >= b)
    {
        BigInt tmp(b);
        BigInt displace_tmp(b);
        BigInt tmp_c(1);
        int i = 0;
        displace_tmp.displace();
        while(a > displace_tmp)
        {
            tmp = displace_tmp;
            tmp_c.displace();
            displace_tmp.displace();
        }
        while(a >= tmp)
        {
            a = a - tmp;
            ++i;
        }
        c = c + tmp_c * i;
    }
    c.is_true = !(first.is_true ^ second.is_true);
    return c;
}

void BigInt::norm_1()
{
    while(sec_size > 1 && array[sec_size - 1] == 0)
    {
        --sec_size;
    }
    if(array[sec_size - 1] < 0)
    {
        for(size_t i = 0; i < sec_size; ++i)
        {
            array[i] = -array[i];
        }
        is_true = !is_true;
    }
    for(size_t i = 0; i < sec_size - 1; ++i)
    {
        if(array[i] < 0)
        {
            array[i] += 10;
            --array[i + 1];
        }
    }
    while(sec_size > 0 && array[sec_size - 1] == 0)
    {
        --sec_size;
    }
}

void BigInt::wide(size_t con)
{
    max_ += con;
    Character *tmp_array = new Character[max_]();
    for(int i = 0; i < sec_size; ++i)
    {
        tmp_array[i] = array[i];
    }
    delete[] array;
    array = tmp_array;
}

void BigInt::norm_2()
{
    int i = 1;
    while(i <= sec_size)
    {
        if(sec_size == max_)
        {
            wide();
        }
        if(array[i - 1] >= 10)
        {
            array[i] += array[i - 1] / 10;
            array[i - 1] = array[i - 1] % 10;
        }
        if(array[sec_size] > 0)
        {
            ++sec_size;
        }
        ++i;
    }
}




