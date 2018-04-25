#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    std::fstream file(argv[1]);
    if (!file) {
        std::cout << "can't open file";
        return 1;
    }
    std::string mid;
    std::map<std::string, int> map;
    while (file >> mid) {
        map[mid]++;
    }
    std::multimap<int, std::string> ans;
    for (auto i = map.begin(); i != map.end(); ++i) {
        ans.insert(std::pair<int, std::string> (i->second, i->first));
        if (ans.size() > 10) {
            ans.erase(ans.begin());
        }
    }
    for (auto i = ans.rbegin(); i != ans.rend(); ++i) {
        std::cout << i->first << ' ' << i->second << std::endl;
    }
    return 0;
}