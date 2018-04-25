#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

bool my_cmp(const std::pair<uint32_t, std::string>& a, const std::pair<uint32_t, std::string>& b) {
    return (a.first > b.first);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    std::ifstream f(argv[1]);
    if (!f) {
        return 1;
    }

    std::map<std::string, uint32_t> m;
    while (f.good()) {
        std::string s;
        f >> s;
        if (s.length() > 0) {
            if (m.find(s) == m.end()) {
                m[s] = 0;
            }
            ++m[s];
        }
    }

    std::vector<std::pair<uint32_t, std::string> > v;
    for (auto it = m.begin(); it != m.end(); ++it) {
        v.push_back(make_pair(it->second, it->first));
    }

    uint32_t n = std::min(static_cast<size_t>(10), v.size());
    std::partial_sort(v.begin(), v.begin() + n, v.end(), my_cmp);

    for (uint32_t i = 0; i < n; ++i) {
        std::cout << v[i].first << " " << v[i].second << std::endl;
    }

    return 0;
}
