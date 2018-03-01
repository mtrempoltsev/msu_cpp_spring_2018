#include <iostream>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <set>
#include "numbers.dat"

const int N = 100000;
int bin_search_l(int x, int _l, int _r) {
    int l = _l, r = _r;
    while (l < r) {
        int mid = (l + r) / 2;
        if (Data[mid] < x) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    return r;
}
int bin_search_r(int x, int _l, int _r) {
    int l = _l, r = _r;
    while (l < r) {
        int mid = (l + r) / 2;
        if (Data[mid] <= x) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    return r;
}
int main(int argc, char *argv[]) {
    if (!(argc%2)) {
        return -1;
    }
    if (argc < 2) {
        return -1;
    }
    std::set <int> eazy;
    eazy.insert(2);
    for (int i = 3; i < N; i++) {
        int flag = 0;
        for (auto& el : eazy) {
            if (!(i % el)) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            eazy.insert(i);
        }
    }
    for (int i = 1; i < argc; ++++i) {
        int beg, end;
        beg = std::atoi(argv[i]);
        end = std::atoi(argv[i + 1]);
        if ((beg > N) || (end > N) || (beg < 0) || (end < 0)) {
            return -1;
        }
        if (beg == 0) {
            if ((std::strlen(argv[i]) != 1) || (argv[i][0] != '0')) {
                return -1;
            }
        }
        if (end == 0) {
            if ((std::strlen(argv[i + 1]) != 1) || (argv[i + 1][0] != '0')) {
                return -1;
            }
        }
        beg = bin_search_l(beg, 0, Size - 1);
        end = bin_search_r(end, 0, Size - 1);
        int ans = 0;
        for (int i = beg; i < end; i++) {
            if (eazy.find(Data[i]) != eazy.end()) {
                ans++;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}