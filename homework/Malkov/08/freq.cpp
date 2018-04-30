#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct dict {
    std::string word;
    size_t count;
};

namespace params {
    constexpr size_t TOPN = 10;
    std::vector<dict> data;
}

int inbase(std::string word) {
    for (int i = 0; i < params::data.size(); i++) {
        if (params::data[i].word == word) { return i; }
        else { return -1; }
    }
    return -1;
}

bool compare(const dict &a, const dict &b) { return (a.count > b.count); }

int main(int argc, char *argv[]) {
    std::ifstream fin(argv[1]);
    std::string s;
    while (fin >> s) {
        dict temp;
        if (inbase(s) == -1) {
            temp.word = std::move(s);
            temp.count = 1;
            params::data.push_back(temp);
        } else { params::data[inbase(s)].count++; }
    }
    sort(params::data.begin(), params::data.end(), compare);
    std::ofstream fout("output.txt", std::ios_base::app);
    for (int i = 0; i < params::data.size() && i < params::TOPN; ++i) {
        fout << params::data[i].word << ' ' << params::data[i].count << std::endl;
    }
}
