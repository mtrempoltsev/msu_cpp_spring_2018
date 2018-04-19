#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

auto CountWordOccurrences(std::ifstream &in) {
    std::map<std::string, uint64_t> dict;
    std::string cur_word;
    while (in >> cur_word)
        ++dict[cur_word];
    return dict;
};

auto SortKeysByValues(const std::map<std::string, uint64_t> &map) {
    std::vector<std::pair<uint64_t, std::string>> result;
    result.reserve(map.size());
    for (const auto &&x : map)
        result.emplace_back(x.second, x.first);
    std::sort(result.begin(), result.end());
    return result;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
        throw std::runtime_error("Could not open the file");

    auto result = SortKeysByValues(CountWordOccurrences(input));
    for (int i = 0; i < result.size() && i < 10; ++i) {
        std::cout << result[i].first << result[i].second << "\n";
    }

    return 0;
}

