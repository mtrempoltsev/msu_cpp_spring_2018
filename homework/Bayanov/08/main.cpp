#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

const size_t TOP = 10;

void FindTopMostFrequencyWords(std::ifstream& in){
    std::string word;
    std::map<std::string, int> dictionary;

    while(in.good()){
        in >> word;
        ++dictionary[word];
    }

    std::priority_queue<std::pair<int, std::string>> frequency;

    for(auto var: dictionary){
        std::pair<int, std::string> tmp = {-var.second, var.first};
        if(frequency.size() < TOP){
            frequency.push(tmp);
        }else{
            if(frequency.top().first > tmp.first){
                frequency.pop();
                frequency.push(tmp);
            }
        }
    }

    std::vector<std::pair<int, std::string>> answer;
    while(frequency.size()){
        answer.push_back(frequency.top());
        frequency.pop();
    }
    for(auto it = answer.rbegin(); it != answer.rend(); ++it){
        std::cout << -(it -> first) << " " << it -> second << "\n";
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2){
        return 1;
    }

    std::ifstream in (argv[1]);
    if(!in.is_open()){
        return 1;
    }

    FindTopMostFrequencyWords(in);

    return 0;
}