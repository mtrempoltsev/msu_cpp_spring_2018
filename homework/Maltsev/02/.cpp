#include <iostream>
#include "numbers.dat"
#include <vector>
int binary_search(const int* data, int left_index, int right_index, int key) {
    int mid_index;
    while (right_index > left_index) {
        mid_index = left_index + (right_index - left_index) / 2;
        if (data[mid_index] >=  key) {
            right_index = mid_index;
        } else {
            left_index = mid_index + 1;
        }
    }
    if (data[left_index] == key) {
        return left_index;
    } else {
        return -1;
    }
}
int prims_quantity(int left, int right) {

    const int N = right;
    std::vector<bool> prime(N + 1, true);
    prime[0] = prime[1] = false;
    int counter = N - 1;
    for (int i = 2; i * i <= N; ++i) {
        if (prime[i]) {
            for (int j = i + i; j <= N; j += i) {
                if (prime[j]) {
                    prime[j] = false;
                    if (j >= left) {
                        --counter;
                    }
                }
            }
        }
    }
    return counter;
}
int main(int argc, char** argv)
{
    if (!(argc % 2) || argc == 1) {
        return -1;
    }
    int start_index,
            start_number, end_number;
    int i = 1;
    int cur_index, cur_number;
    while (i < argc) {
        start_number = std::atoi(argv[i]);
        if (start_number < 0 || start_number > 100000) {
            return -1;
        }
        end_number = std::atoi(argv[i+1]);
        if (start_number > end_number) {
            std::cout << 0 << std::endl;
            return 0;
        }
        start_index = binary_search(Data, 0, Size, start_number);
        if ( start_index >= 0) {
            std::cout << prims_quantity(start_number, end_number) << std::endl;
        } else {
            std::cout << 0 << std::endl;
            return -1;
        }
        i += 2;
    }
    return 0;
}