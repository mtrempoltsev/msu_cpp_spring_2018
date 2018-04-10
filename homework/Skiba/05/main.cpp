#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

int64_t abs(int64_t x) {
    return (x < 0) ? (-x) : (x);
}
class BigInt{
    int sig = 1;
    int sz, cp = 100;
    int base = 1000;
    int out_len = 3;
    int *ptr;
    void shift() {
        if (cp == sz) {
            resize(cp * 2);
        }
        sz++;
        for (int i = sz - 1; i > 0; i--) {
            ptr[i] = ptr[i - 1];
        }
        ptr[0] = 0;
    }
    int getlen(int64_t x) {
        if (x == 0) {
            return 1;
        }
        int ans = 0;
        while (x) {
            ans++;
            x /= base;
        }
        return ans;
    }
    void resize(int _cp) {
        if (_cp < cp) {
            return;
        }
        cp = _cp + 10;
        int *ptr_new = new int[cp];
        for (int i = 0; i < cp; i++) {
            ptr_new[i] = ptr[i];
        }
        delete[] ptr;
        ptr = ptr_new;
    }
    BigInt(int x, int _sz) {
        sz = _sz;
        cp = sz * 2 + 100;
        ptr = new int[cp];
        for (int i = 0; i < cp; i++) {
            ptr[i] = 0;
        }
    }
public:
    BigInt(int64_t x = 0) {
        if (x < 0) sig = -1;
        x = abs(x);
        sz = getlen(x);
        cp = sz * 2 + 100;
        ptr = new int[cp];
        for (int i = 0; i < cp; i++) {
            if (x > 0) {
                ptr[i] = x % base;
                x /= base;
            } else {
                ptr[i] = 0;
            }
        }
    }
    BigInt(const BigInt& mid) {
        sig = mid.sig;
        sz = mid.sz;
        cp = mid.cp;
        base = mid.base;
        ptr = new int[cp];
        for (int i = 0; i < cp; i++) {
            ptr[i] = mid.ptr[i];
        }
    }
    ~BigInt() {
        if (ptr)
        delete[] ptr;
    }
    bool operator==(const BigInt& mid) const{
        if ((sz == mid.sz) && (sig == mid.sig)) {
            for (int i = 0; i < sz; i++) {
                if (ptr[i] != mid.ptr[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    bool operator!=(const BigInt &mid) const{
        return !operator==(mid);
    }
    bool operator<(const BigInt& mid) const{
        if (sig < mid.sig) {
            return true;
        }
        if (sig > mid.sig) {
            return false;
        }
        if (sz < mid.sz) {
            return true;
        }
        if (sz > mid.sz) {
            return false;
        }
        for (int i = sz - 1; i >= 0; i--) {
            if (ptr[i] == mid.ptr[i])
                continue;
            return sig * ptr[i] < mid.sig * mid.ptr[i];
        }
        return false;
    }
    bool operator>(const BigInt& mid) const{
        if (sig > mid.sig) {
            return true;
        }
        if (sig < mid.sig) {
            return false;
        }
        if (sz > mid.sz) {
            return true;
        }
        if (sz < mid.sz) {
            return false;
        }
        for (int i = sz - 1; i >= 0; i--) {
            if (ptr[i] == mid.ptr[i])
                continue;
            return sig * ptr[i] > mid.sig * mid.ptr[i];
        }
        return false;
    }
    bool operator<=(const BigInt& mid) const{
        if (sig < mid.sig) {
            return true;
        }
        if (sig > mid.sig) {
            return false;
        }
        if (sz < mid.sz) {
            return true;
        }
        if (sz > mid.sz) {
            return false;
        }
        for (int i = sz - 1; i >= 0; i--) {
            if (ptr[i] == mid.ptr[i])
                continue;
            return sig * ptr[i] < mid.sig * mid.ptr[i];
        }
        return true;
    }
    bool operator>=(const BigInt& mid) const{
        if (sig > mid.sig) {
            return true;
        }
        if (sig < mid.sig) {
            return false;
        }
        if (sz > mid.sz) {
            return true;
        }
        if (sz < mid.sz) {
            return false;
        }
        for (int i = sz - 1; i >= 0; i--) {
            if (ptr[i] == mid.ptr[i])
                continue;
            return sig * ptr[i] > mid.sig * mid.ptr[i];
        }
        return true;
    }
    BigInt operator-() {
        BigInt mid(*this);
        if ((sz > 1) || (ptr[0] != 0) ) {
            mid.sig = - mid.sig;
        }
        return mid;
    }
    BigInt& operator=(const BigInt& mid) {
        sig = mid.sig;
        sz = mid.sz;
        cp = mid.cp;
        delete[] ptr;
        ptr = new int[cp];
        for (int i = 0; i < sz; i++) {
            ptr[i] = mid.ptr[i];
        }
        return *this;
    }
    friend BigInt abs(const BigInt& a);
    friend BigInt operator/(const BigInt& a, int64_t b);
    friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt& a, const BigInt& b);
    friend BigInt operator*(const BigInt& a, const BigInt& b);
    friend BigInt operator/(const BigInt& a, const BigInt& b);
    friend BigInt operator%(const BigInt& a, const BigInt& b);
    friend bool operator==(int64_t b, const BigInt& a);
    friend bool operator!=(int64_t b, const BigInt& a);
    friend bool operator<(int64_t b, const BigInt& a);
    friend bool operator>(int64_t b, const BigInt& a);
    friend bool operator<=(int64_t b, const BigInt& a);
    friend bool operator>=(int64_t b, const BigInt& a);
    friend std::ostream& operator<<(std::ostream& out, const BigInt& mid);
};

std::ostream& operator<<(std::ostream& out, const BigInt& mid)
{
    if (mid.sig < 0) {
        out << '-';
    }
    out << mid.ptr[mid.sz - 1];
    for (int i = mid.sz - 2; i >= 0; i--) {
        out << std::setw(mid.out_len) << std::setfill('0') << mid.ptr[i];
    }
    return out;
}
bool operator==(int64_t b, const BigInt& a) {
    return a.operator==(b);
}
bool operator!=(int64_t b, const BigInt& a) {
    return a.operator!=(b);
}
bool operator>(int64_t b, const BigInt& a) {
    return a.operator>(b);
}
bool operator<(int64_t b, const BigInt& a) {
    return a.operator<(b);
}
bool operator<=(int64_t b, const BigInt& a) {
    return a.operator<=(b);
}
bool operator>=(int64_t b, const BigInt& a) {
    return a.operator>=(b);
}
BigInt abs(const BigInt& a) {
    BigInt mid = a;
    mid.sig = 1;
    return mid;
}
BigInt operator+(const BigInt& a, const BigInt& b) {
    int buf = 0;
    int m = std::max(a.sz, b.sz);
    BigInt mid(0, m);
    if (abs(b) > abs(a)) {
        mid.sig = b.sig;
    } else {
        mid.sig = a.sig;
    }
    for (int i = 0; i < m; i++) {
        if (a.sz <= i) {
            mid.ptr[i] = buf + b.ptr[i] * mid.sig;
        } else
        if (b.sz <= i) {
            mid.ptr[i] = buf + a.ptr[i] * mid.sig;
        } else {
            mid.ptr[i] = buf + a.ptr[i] * a.sig + b.ptr[i] * b.sig;
        }
        if (mid.ptr[i] * mid.sig >= 0) {
            mid.ptr[i] = abs(mid.ptr[i]);
            buf = mid.ptr[i] / mid.base;
            buf *= mid.sig;
            mid.ptr[i] %= mid.base;
        } else {
            mid.ptr[i] = mid.base - abs(mid.ptr[i]);
            buf = -1 * mid.sig;
        }
    }
    if (buf) {
        mid.ptr[mid.sz++] = buf * mid.sig;
    }
    while ((mid.sz > 1) && (mid.ptr[mid.sz - 1] == 0)) {
        mid.sz--;
    }
    if ((mid.sz == 1) && (mid.ptr[mid.sz - 1] == 0)) {
        mid.sig = 1;
    }
    return mid;
}
BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt c = b;
    c = -c;
    return operator+(a,c);
}
BigInt operator*(const BigInt& a, const BigInt& b) {
    int buf = 0;
    int m = std::max(a.sz, b.sz);
    BigInt mid(0, m * 2 + 1);
    mid.sig = a.sig * b.sig;
    for (int i = 0; i < a.sz; i++) {
        buf = 0;
        for (int j = 0; j < b.sz; j++) {
            mid.ptr[i + j] += buf + a.ptr[i] * b.ptr[j];
            buf = mid.ptr[i + j] / a.base;
            mid.ptr[i + j] %= a.base;
        }
        if (buf) {
            mid.ptr[i + b.sz] += buf;
        }
    }
    while ((mid.sz > 1) && (!mid.ptr[mid.sz - 1])) {
        mid.sz--;
    }
    if ((mid.sz == 1) && (mid.ptr[mid.sz - 1] == 0)) {
        mid.sig = 1;
    }
    return mid;
}
BigInt operator/(const BigInt& a, const BigInt& b) {
    if (b.sz == 1) {
        int64_t del = b.ptr[0] * b.sig;
        return operator/(a, del);
    }
    BigInt mid_a(abs(a)), mid_b(abs(b));
    BigInt ans(0);
    while (mid_a >= mid_b) {
        BigInt sh1(mid_b), sh2(mid_b), mul(1);
        sh2.shift();
        while ((sh2 < mid_a)) {
            sh1 = sh2;
            sh2.shift();
            mul.shift();
        }
        int i = 0;
        while (mid_a >= sh1) {
            i++;
            mid_a = mid_a - sh1;
        }

        ans = ans + i * mul;
    }
    ans.sig = a.sig * b.sig;
    if ((ans.sz == 1) && (ans.ptr[ans.sz - 1] == 0)) {
        ans.sig = 1;
    }
    return ans;
}
BigInt operator%(const BigInt& a, const BigInt& b) {
    BigInt mid_a(a), zero(0);
    mid_a = mid_a - ((a / b) * b) ;
    return mid_a;
}

BigInt operator/(const BigInt& a, int64_t b) {
    BigInt mid(0);
    int buf = 0;
    int b_sig = (b >= 0) ? 1 : -1;
    b = abs(b);
    //std::cout << a << " " << b << std::endl;
    for (int i = a.sz - 1; i >= 0; i--) {
        buf = buf * a.base + a.ptr[i];
        //std::cout << "Buf " << buf << std::endl;
        if (buf >= b) {
            mid.shift();
            mid = mid + (buf / b);
            buf %=b;
        } else {
            mid.shift();
        }
        //std::cout << "Ans " << mid << std::endl;
    }
    mid.sig = a.sig * b_sig;
    while ((mid.sz > 1) && (!mid.ptr[mid.sz - 1])) {
        mid.sz--;
    }
    if ((mid.sz == 1) && (mid.ptr[mid.sz - 1] == 0)) {
        mid.sig = 1;
    }
        return mid;
}
int main() {
    return 0;
}