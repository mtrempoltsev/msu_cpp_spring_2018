#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.good()) {
        return 1;
    }
    std::map<std::string, unsigned int> data;
    while (file.good()) {
        std::string tmp_str;
        file >> tmp_str;
        data[tmp_str] += 1;
    }

    std::vector< std::pair<unsigned int, std::string> > tmp_vector;
    tmp_vector.reserve(data.size());
    for (auto& i: data) {
        tmp_vector.emplace_back(std::make_pair(i.second, i.first));
    }
    std::sort(tmp_vector.rbegin(), tmp_vector.rend());

    for (size_t i = 0; i < std::min(10, static_cast<int>(tmp_vector.size())); ++i) {
        std::cout << tmp_vector[i].first << ' ' << tmp_vector[i].second << std::endl;
    }
    return 0;
}
