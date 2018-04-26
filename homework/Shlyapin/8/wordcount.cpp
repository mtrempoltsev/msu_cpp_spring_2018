#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Name of the file required\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in.good()) {
        std::cerr << "Bad file\n";
        return 1;
    }
    std::map<std::string, int> tree;
    std::string s;
    while (in >> s) {
        auto t = tree.find(s);
        if (t == tree.end()) {
            t->second = 1;
        } else {
            ++(t->second);
        }
    }
    std::vector<std::pair<std::string, int> > v;
    for (auto &i : tree) {
        v.push_back(i);
    }
    std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) {return a.second > b.second;});
    auto ii = v.begin();
    for (int i = 10; i && ii != v.end(); --i, ++ii) {
        std::cout << ii->second << ' ' << ii->first << std::endl;
    }
    return 0;
}
