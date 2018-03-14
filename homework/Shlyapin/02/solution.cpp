#include <iostream>
#include <cmath>
#include <cstdlib>
#include "numbers.dat"

void initialize_array(int *arr)
{
    int MAX = sqrt(Data[Size - 1]) + 1;
    for (std::size_t i = 0; i < Size; ++i) {
        arr[i] = 1;
    }
    for (int i = 2; i < MAX; ++i) {
        for (size_t j = 0; j < Size; ++j) {
            if (arr[j] && ((Data[j] != i && Data[j] % i == 0) || Data[j] == 1)) {
                arr[j] = 0;
            }
        }
    }
}

int get_num(char *arg)
{
    constexpr int BASE = 10;
    char *isvalid = nullptr;
    int res = strtol(arg, &isvalid, BASE);
    return *isvalid ? -1 : res;
}

int main(int argc, char *argv[])
{
    using std::cout;
    using std::size_t;
    using std::endl;

    if (argc == 1 || (argc & 1) == 0) {
        return -1;
    }
    int *flag= new int[Size] {1, 2, 3, 4, 5, 6, 7, 8};            //mark whether Data[i] is prime or not
    initialize_array(flag);
    
    for (int i = 1; i < argc; i += 2) {
        int left = get_num(argv[i]), right = get_num(argv[i + 1]);
        if (left < 0 || right < 0) {
            return -1;
        }
        if (left > right) {
            cout << 0 << endl;
            continue;
        }
        unsigned sum = 0;
        size_t L = 0, R = Size - 1;
        for (; Data[L] < left; L++) {};
        
        if (Data[L] != left) {
            cout << 0 << endl;
            continue;
        }
        for (; Data[R] > right; R--) {};
        
        if (Data[R] != right) {
            cout << 0 << endl;
            continue;
        }
        for (size_t i = L; i <= R; ++i) {
            sum += flag[i];
        }
        cout << sum << endl;
    }
    delete[] flag;
    return 0;
}
