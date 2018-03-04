#include <iostream>
#include "numbers.dat"

namespace opt {
    constexpr size_t rbord = 100000;
}

void eratos(bool *primass) {
    primass[0] = primass[1] = true;
    for (size_t i = 2; i < opt::rbord; i++) {
        if (!primass[i]) {
            for (size_t j = 2 * i; j < opt::rbord; j += i) {
                primass[j] = true;
            }
        }
    }

}

int bins(int num) {
    int l = 0, r = Size, m;
    while (r - 1 > 0) {
        m = (l + r) / 2;
        if (Data[m] == num) {
            return m;
        }
        if (Data[m] > num) {
            r = m;
        }
        if (Data[m] < num) {
            l = m;
        }
    }
    if (Data[l] == num) {
        return l;
    }
    if (Data[r] == num) {
        return r;
    }
    return -1;
}

int main(int argc, char *argv[]) {

    if (!(argc & 1) || argc == 1) {
        return -1;
    }

    auto *primass = new bool[opt::rbord];
    std::fill_n(primass, opt::rbord, false);
    eratos(primass);

    int l, lpos, r, rpos, result;
    for (size_t i = 1; i < argc; i += 2) {

        l = std::atoi(argv[i]);
        lpos = bins(l);
        r = std::atoi(argv[i+1]);
        rpos = bins(r);

        if (lpos == -1 || rpos == -1) {
            continue;
        }

        result = 0;
        for (int j = lpos; j <= rpos; ++j) {
            result += !primass[Data[j]];
        }

        std::cout << result << std::endl;
    }

    delete[] primass;

    return 0;
}

