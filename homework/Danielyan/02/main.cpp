#include <iostream>
#include <vector>

#include "numbers.dat"

size_t BinSearch(const std::vector<int> &array, int value) {
    size_t begin = 0, end = array.size();

    while (begin < end) {
        size_t mid = (end - begin) / 2 + begin;
        if (array[mid] > value) {
            end = mid;
        } else if (array[mid] < value) {
            begin = mid + 1;
        } else {
            return mid;
        }
    }
    return array.size();
}

class Preprocessor {
public:
    explicit Preprocessor(const std::vector<int> &numbers) : numbers_(numbers) {
        if (numbers_.back() > 1) {
            is_prime_.resize(numbers_.back() + 1, 1);
            is_prime_[0] = is_prime_[1] = 0;
            for (int i = 2; i < is_prime_.size(); ++i) {
                if (is_prime_[i] == 1) {
                    for (size_t j = 2; i * j < is_prime_.size(); ++j) {
                        is_prime_[i * j] = 0;
                    }
                }
            }
        }
    }

    int CountPrimesInRangeNumber(int left, int right) {
        int result = 0;
        for (int i = 0; i < numbers_.size(); ++i) {
            if (left <= numbers_[i] && numbers_[i] <= right) {
                result += is_prime_[numbers_[i]];
            }
        }
        return result;
    }

private:
    std::vector<int> numbers_;
    std::vector<int> is_prime_;
};

int main(int argc, char* argv[]) {

    if (!(argc & 1) || argc == 1) {
        std::cerr << "Invalid number of argumets" << std::endl;
        return -1;
    }
    
    Preprocessor preprocessor(std::vector<int>(Data, Data + Size));

    for (int i = 1; i < argc; i += 2) {
        std::cout << preprocessor.CountPrimesInRangeNumber(atoi(argv[i]), atoi(argv[i + 1])) << "\n";
    }
    return 0;
}
