#include <iostream>
#include <list>
#include "numbers.dat"

using std::cout;
using std::endl;

enum direction {
    TOP,
    BOT
};

ssize_t bin_search(int val, const int * array, int size, direction dir) {
    int lo = 0, hi = size, mid;
    while(hi > lo) {
        mid = (hi + lo) / 2;
        if(array[mid] < val) {
            lo = mid + 1;
        } else if(array[mid] > val) {
            hi = mid - 1;
        } else {
            if(dir == TOP) {
                while(mid < size) {
                    if(array[mid + 1] == val)
                        mid++;
                    else break;
                }
            } else {
                while(mid > 0) {
                    if(array[mid - 1] == val)
                        mid--;
                    else break;
                }
            }
            return mid;
        }
    }
    return -1;
}

std::list<int> prime_list;

bool is_dumb_prime(int x) {
    if((x % 2 == 0 && x != 2) || x == 1) return false;
    for(int i = 3; i * i <= x; i++) {
        if(x % i == 0) return false;
    }
    return true;
}

bool is_prime(int x) {
    if(x == 1) return false;
    for(int pr : prime_list)  {
        if(pr * pr > x) break;
        if(x % pr == 0) {
            return false;
        }
    }
    return true;
}

void fill_primes() {
    for(int i = 0; i < 317; i++) {//317 ~ sqrt(100000)
        if(is_dumb_prime(i)) {
            prime_list.push_back(i);
        }
    }
}
size_t count_primes(int low_ind, int high_ind, const int array[]) {
    if(low_ind < high_ind) {
        size_t sum = 0;
        for(size_t i = low_ind; i < high_ind;  i++) {
            if(is_prime(array[i])) sum++;
        }
        return sum;
    } else {
        return 0;
    }

}


int main(int argc, char* argv[]) {
    if (argc == 1 || argc % 2 == 0) {
        return -1;
    }
    fill_primes();
    for (int i = 1; i + 1 < argc; i += 2) {
        int low_bound = std::atoi(argv[i]);
        int high_bound = std::atoi(argv[i + 1]);
        int low_index = bin_search(low_bound, Data, Size, BOT);
        int high_index = bin_search(high_bound, Data, Size, TOP);
        if (low_index >= 0 && high_index >= 0) {
            cout << count_primes(low_index, high_index, Data) << endl;
        } else {
            cout << 0 << endl;
        }
    }
    return 0;
}