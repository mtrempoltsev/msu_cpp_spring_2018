#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <set>
#include <map>

constexpr size_t ARGNUM = 2;
constexpr size_t TOP_N = 10;

class wrong_argument_number: public std::exception {};
class couldnt_open_file: public std::exception {};

void word_counter(const std::string &fname);

int main(int argc, char **argv)
{
    try {
        if(argc != ARGNUM) {
            throw wrong_argument_number();
        }
        word_counter(argv[1]);
    } catch(...) {
        std::cerr << "error" << std::endl;
        return 1;
    }
    return 0;
}

void word_counter(const std::string &fname)
{
    std::ifstream fin(fname);
    if (!fin) {
        throw couldnt_open_file();
    }
    std::map<std::string, int> counter;
    while (fin.good()) {
        std::string word;
        fin >> word;
        counter[word]++;
    }

    std::set<std::pair<int, std::string>> res;
    for(auto &elem : counter) {
        res.emplace(elem.second, elem.first);
    }
    auto it = res.rbegin();
    for(int i = 0; i < TOP_N && it != res.rend(); ++i, ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
}
