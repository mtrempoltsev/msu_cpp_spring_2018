#include <iostream>
#include <cmath>

#include "numbers.dat"

using namespace std;

bool is_prime_number(int num) {

    if (num == 1) {
        return false;
    }
    else if (num == 2){
        return true;
    }
    else if(num % 2 == 0){
        return false;
    }

    int sqrt_num = (int)sqrt(num) + 1;

    for (int i = 3; i <= sqrt_num; i=i+2) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

int find_prime_numbers(int start, int end) {

    int n = 0, cache = -1, i = 0;

    if (start > end) {
        return n;
    }

    while(Data[i] < start){
        ++i;
    }

    while (Data[i] <= end) {

        if (cache == Data[i]) {
            ++i;
            ++n;
            continue;
        }
        else if (is_prime_number(Data[i])) {
            ++n;
            cache = Data[i];
        }

        ++i;
    }

    return n;
}

int main(int argc, char* argv[]) {

    int start = 0, end = 0;

    if (argc < 3 || !(argc & 1)) {
        return -1;
    }

    for (int i = 1; i < argc; i = i + 2) {
        start = atoi(argv[i]);
        end = atoi(argv[i+1]);

        if (start >= 0 && end >= 0 && start <= 100000 && end <= 100000) {
            cout << find_prime_numbers(start, end) << endl;
        } else {
            cout << 0 << endl;
        }
    }

    return 0;
}