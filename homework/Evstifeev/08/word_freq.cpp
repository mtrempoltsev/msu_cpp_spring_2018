#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

constexpr size_t TOP_N = 10;
using pair = std::pair<std::string, size_t>;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr
            << "Wrong number of arguments. Format: word_freq [input_file.txt]";
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file) {
        std::cout << "Can't open file " << argv[1];
        return 1;
    }

    std::unordered_map<std::string, size_t> word_freq;

    std::string s;
    while (file >> s) word_freq[s]++;
    std::vector<pair> vec(word_freq.begin(), word_freq.end());
    std::sort(vec.begin(), vec.end(), [](const pair &p1, const pair &p2) {
        return p1.second > p2.second;
    });
    for (size_t i = 0; i < vec.size() && i < TOP_N; i++)
        std::cout << vec[i].second << ' ' << vec[i].first << std::endl;
    return 0;
}
