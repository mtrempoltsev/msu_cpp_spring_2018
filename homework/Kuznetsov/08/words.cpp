#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout<<"wrong argument count. Must 2, get " + argc << std::endl;
        return 1;
    }

    std::fstream file(argv[1], std::fstream::in);
    if(!file) {
        std::cout<<"open file error"<<std::endl;
        return 1;
    }

    std::unordered_map<std::string, int> wordsCount;
    {
        std::string word;
        while (file >> word)
            ++wordsCount[word];
        file.close();
    }

    std::vector<std::pair<std::string, int> > words(wordsCount.begin(), wordsCount.end());

    std::partial_sort(words.begin(), words.begin()+10, words.end(),
              [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)  { return a.second > b.second; });

    for(auto iter = words.begin(); iter != words.end() && iter - words.begin() < 10; ++iter)
        std::cout<<iter->second<<' '<<iter->first<<std::endl;

    return 0;
}