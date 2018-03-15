#include <iostream>
#include "numbers.dat"

int idx_binary_search_first(const int *a, int key, int l, int r);
int idx_binary_search_last(const int *a, int key, int l, int r);
bool *get_sieve(int N);
int count_primes(const int *a, const bool*, int l, int r);


int main(int argc, char **argv) {
    if (argc < 3 || (argc % 2 == 0)) {
        return -1;
    }

    bool *S = get_sieve(Data[Size-1]);

    int n_of_primes = 0;
    for (int i = 1; i < argc; i += 2) {
        int start, end;
        start = std::atoi(argv[i]);
        end = std::atoi(argv[i + 1]);
        if (start < 0 || end < 0) {
            std::cout << 0 << std::endl;
            return -1;
        }

        int idx_left, idx_right;
        idx_left = idx_binary_search_first(Data, start, 0, Size);
        if (idx_left == -1) {
            std::cout << 0 << std::endl;
            continue;
        }
        idx_right = idx_binary_search_last(Data, end, idx_left, Size);
        if (idx_right == -1) {
            std::cout << 0 << std::endl;
            continue;
        }

        n_of_primes = count_primes(Data, S, idx_left, idx_right);
        std::cout << n_of_primes << std::endl;
    }
    
    delete[] S;
    return 0;
}

int idx_binary_search_first(const int *a, int key, int l, int r) {
    int mid = l + (r - l) / 2;
    if (l >= r) {
        return -1;
    }

    if (a[l] == key) {
        return l;
    } else if (a[mid] == key) {
        if (mid == l + 1) {
            return mid;
        } else {
            return idx_binary_search_first(a, key, l, mid+1);
        }
    } else if (a[mid] > key) {
        return idx_binary_search_first(a, key, l, mid);
    } else {
        return idx_binary_search_first(a, key, mid, r);
    }
}

int idx_binary_search_last(const int *a, int key, int l, int r) {
    int mid = l + (r - l) / 2;
    if (l >= r) {
        return -1;
    }

    if (a[r - 1] == key) {
        return r - 1;
    } else if (a[mid] == key) {
        if (mid == r - 2) {
            return mid;
        } else {
            return idx_binary_search_last(a, key, mid-1, r);
        }
    } else if (a[mid] > key) {
        return idx_binary_search_last(a, key, l, mid);
    } else {
        return idx_binary_search_last(a, key, mid, r);
    }
}

bool *get_sieve(int N) {
    bool *S = new bool[N + 1];
    std::fill_n(S, N + 1, true);
    S[0] = S[1] = false;
    for (int k = 2; k*k <= N; k++) {
        if (S[k]) {
            for(int j = k*k; j <= N; j += k){
                S[j] = 0;
            }
        }
    }
    return S;
}

int count_primes(const int *a, const bool *sieve, int l, int r) {
    int sum = 0;
    for (int i = l; i <= r; i++) {
        sum += sieve[a[i]];
    }
    return sum;
}