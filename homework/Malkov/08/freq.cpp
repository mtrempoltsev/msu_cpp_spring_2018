#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

namespace params {
    constexpr size_t TOPN = 10;
    std::unordered_map<std::string, size_t> result;
}

bool compare(const std::string &a, const std::string &b) {
    return (params::result[a] > params::result[b]); 
}

int main(int argc, char *argv[]) {
    if (argc != 2) { return 1; }
    std::ifstream fin(argv[1]);
    if (!fin) { return 1; }
    std::vector<std::string> words;
    std::string s;
    while (fin >> s) {
        if (!params::result[s]++) { words.push_back(std::move(s));}
    }
    sort(words.begin(), words.end(), compare);
    for (int i = 0; i < words.size() && i < params::TOPN; ++i) {
        std::cout << params::result[words[i]] << ' ' << words[i] << std::endl;
    }
    return 0;
}
