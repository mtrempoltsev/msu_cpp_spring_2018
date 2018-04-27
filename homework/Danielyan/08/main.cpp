#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>

auto CountWordOccurrences(std::ifstream &in) {
    std::unordered_map<std::string, uint64_t> dict;
    std::string cur_word;
    while (in >> cur_word)
        ++dict[cur_word];
    return dict;
};

auto SortKeysByValues(const std::unordered_map<std::string, uint64_t> &map) {
    std::vector<std::pair<uint64_t, std::string>> result;
    result.reserve(map.size());
    for (auto &x : map)
        result.emplace_back(x.second, x.first);
    std::sort(result.begin(), result.end(), [] (const auto& x, const auto& y) {
        return x.first > y.first;
    });
    return result;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Could not open the file" << std::endl;
        return 1;
    }

    auto result = SortKeysByValues(CountWordOccurrences(input));
    for (int i = 0; i < std::min<size_t>(result.size(), 10); ++i) {
        std::cout << result[i].first << " " << result[i].second << "\n";
    }

    return 0;
}

