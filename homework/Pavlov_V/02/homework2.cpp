#include <iostream>
#include <vector>

#include "numbers.dat"

void EratosthenesSieve(std::vector<bool>& is_prime){
    is_prime[0] = is_prime[1] = false;
    int max_number = static_cast<int>(is_prime.size());
    for(int i = 2; i < max_number; ++i){
        if(is_prime[i]){
            for(long long j = i * (long long)i; j < max_number; j += i){
                is_prime[j] = false;
            }
        }
    }
}

int GetAllPrimesInRange(int start, int finish, std::vector<bool>& is_prime) {
    int count = 0;
    for (unsigned long long i = start; i <= finish; ++i) {
        if(is_prime[Data[i]])
            count++;
    }
    return count;
}
int binSearch(int key, bool move_to_left) {
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
            if(move_to_left) {
                while(midd > 0 && key == Data[midd - 1])
                    --midd;
            } else {
                while(midd + 1 < Size && key == Data[midd + 1]) {
                    ++midd;
                }
            }
            return midd;
        };
        if (left > right)
            return -1;
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
    if(argc == 1 || argc % 2 == 0)
        return -1;
    
    std::vector<bool> is_prime(100001, true);
    EratosthenesSieve(is_prime);
    
    for(int i = 1; i < argc; i += 2) {
        int first_number = atoi(argv[i]);
        int second_number = atoi(argv[i + 1]);
        
        int start = binSearch(first_number, true);
        int finish = binSearch(second_number, false);
        
        if(start >= 0 && finish >= 0) {
            std::cout << GetAllPrimesInRange(start, finish, is_prime) << "\n";
        }
    }
    return 0;
}


