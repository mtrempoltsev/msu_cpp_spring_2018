#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "numbers.dat"

std::vector<int> indexes;

bool is_prime(long long n){
    if(n == 1){
        return false;
    }
    for(long long i = 2; i * i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}

int GetAllPrimesInRange() {
    int count = 0;
    for (unsigned long long i = indexes[0]; i <= indexes[1]; ++i) {
        if(is_prime(Data[i]))
            count++;
    }
    return count;
}
bool binSearch(int key, std::pair<int, int> &p) {
    int midd = 0;
    int left = 0;
    int right = Size - 1;
    while(true) {
        midd = (left + right) / 2;
        if (key < Data[midd])
            right = midd - 1;
        else if (key > Data[midd])
            left = midd + 1;
        else {
            if(key == p.first) {
                while(midd > 0 && key == Data[midd - 1])
                    --midd;
            } else {
                while(midd + 1 < Size && key == Data[midd + 1]) {
                    ++midd;
                }
            }
            indexes.push_back(midd);
            return true;
        };
        if (left > right)
            return false;
    }
}
bool isCorrectPair(std::pair<int, int> &p) {
    if(p.first > p.second){
        std::cout << 0 << std::endl;
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    std::vector<std::pair<int, int>> p;
    if(argc == 1) return -1;
    if(argc % 2== 1) {
        for(int i = 1; i < argc; i += 2) {
            std::pair<int, int> cur;
            cur.first = std::atoi(argv[i]);
            cur.second = std::atoi(argv[i + 1]);
            p.push_back(cur);
        }
    } else return -1;
    for(int i = 0; i < p.size(); ++i) {
        if(isCorrectPair(p[i])) {
            if(binSearch(p[i].first, p[i]) && binSearch(p[i].second, p[i])) {
                std::cout << GetAllPrimesInRange() << std::endl;
                indexes.clear();
            }
        }
    }
    return 0;
}
