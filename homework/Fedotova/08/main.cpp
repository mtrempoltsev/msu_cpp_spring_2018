#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <utility>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "error" << std::endl;
        return 1;
    }
    
    std::fstream f;
    f.open(argv[1], std::fstream::in);
    if (!f) {
        std::cerr << "file error" << std::endl;
        return 1;
    }
    std::string s;
    std::map<std::string, int> m;
    
    while(f >> s) 
        m[s]++;
    f.close();
    
    std::vector<std::pair<std::string, int>> v(m.begin(), m.end());
    std::sort(v.begin(), v.end(), [](auto i, auto j) {return (i.second > j.second);});
    
    for (auto it = v.begin(); it != v.end() && it - v.begin() < 10; it++)
        std::cout << it->second << ' ' << it->first << std::endl;
    
    return 0;
}
