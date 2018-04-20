#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    std::ifstream f(argv[1]);
    
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

    std::vector<std::pair<int, std::string> > v;
    for (auto it = m.begin(); it != m.end(); ++it) {
        v.push_back(make_pair(it->second, it->first));
    }

    uint32_t n = std::min(static_cast<uint32_t>(10), static_cast<uint32_t>(v.size()));
    std::partial_sort(v.rbegin(), v.rbegin() + n, v.rend());

    for (uint32_t i = 0; i < n; ++i) {
        std::cout << v[i].first << " " << v[i].second << std::endl;
    }

    return 0;
}
