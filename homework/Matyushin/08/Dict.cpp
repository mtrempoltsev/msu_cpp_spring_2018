#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char** argv){
    if (argc != 2){
        std::cerr << "error" << std::endl;
        return 1;
    }
        
    std::unordered_map<std::string, size_t> dict;
    std::fstream file;
    file.open(argv[1], std::fstream::in);
    if (!file){
        std::cerr << "error" << std::endl;
        return 1;
    }
    
    std::string word;
    while (file >> word)
            dict[word]++;
    file.close();
    
    std::vector<std::pair<std::string, size_t>> vect;
    auto iterator = dict.begin();
    while (iterator != dict.end()){
        vect.emplace_back(iterator->first, iterator->second);
        iterator++;
    }
    
    std::sort(vect.begin(), vect.end(), [](std::pair<std::string, size_t> &left, std::pair<std::string, size_t> &right) { return left.second > right.second;});
    
    auto viterator = vect.begin();
    while ((viterator != vect.end()) && (viterator - vect.begin() < 10)){
        std::cout << viterator->second << " " << viterator->first << std::endl;
        viterator++;
    }
    
    return 0;
}
