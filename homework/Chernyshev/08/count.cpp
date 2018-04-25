#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

namespace Limits
{
    constexpr size_t TOP_N = 10;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Not appropriate number of arguments (expected 2, got " << argc << ")\n";
        return 1;
    }

    std::ifstream fin(argv[1]);
    if (!fin) {
        std::cerr << "File can't be opened\n";
        return 1;
    }

    std::map<std::string, size_t> freq;
    std::vector<std::string> words;

    std::string s;
    while (fin >> s) {
        if (!freq[s]++) {
            words.push_back(std::move(s));
        }
    }

    sort(words.begin(), words.end(), [&freq](const std::string &s1, const std::string &s2) {
        return freq[s1] > freq[s2];
    });

    for (int i = 0; i < words.size() && i < Limits::TOP_N; ++i) {
        std::cout << freq[words[i]] << ' ' << words[i] << std::endl;
    }
}
