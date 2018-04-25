
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

typedef std::pair<std::string, int> word;

int main(int argc, const char * argv[]) {
    std::map<std::string, int> list_words;
    if (argc != 2)
        return 1;
    std::string file_name = argv[1];
    std::ifstream file(file_name);
    if (!file) {
        std::cout << "can't open file" ;
        return 1;
    }
    
    while (file.good()) {
        std::string s;
        file >> s;
        list_words[s]++;
    }
    std::vector<word> vec(list_words.begin(), list_words.end());
    std::sort(vec.begin(), vec.end(), [] (const word& a, const word& b) -> bool {
         return a.second > b.second;
    });
    
    for (int i = 0; i < std::min((size_t) 10, vec.size()); ++i) {
        std::cout << vec[i].second << " " << vec[i].first << std::endl;
    }
    
    return 0;
}
