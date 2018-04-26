#include<bits/stdc++.h>
#include<string>

const long long prost = 536870913; //большое прострое число для хэширования
const int MAX_STRINGS = 10;

int main(int argc,char** argv)
{
    if(argc != 2){
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file){
        return 1;
    }
    std::map<int, int> NumOfOccurrenc;      //Количество вхождений слова в строку по её хэшу
    std::map<int, std::string> HashAndStr;  //Слово по её хэшу
    std::set<int> SetOfHash;                //Все слова встретившиеся в файле
    while(file.good())
    {
        std::string str;
        file >> str;

            // Считаю хэш слова
        long long hash = 0;
        int i = 0;
        while(i < str.size()){
            hash = ((hash + str[i]) * prost) % 1000000000;
            i++;
        }

        SetOfHash.insert(hash);
        NumOfOccurrenc[hash]++;
        if(HashAndStr[hash].empty())
            HashAndStr[hash] = str;
    }


    for(int i = 0; i < MAX_STRINGS; ++i){
        int MaxStr = -1;
        for(auto j : SetOfHash){
            if(NumOfOccurrenc[j] != -1 && (MaxStr == -1 || NumOfOccurrenc[MaxStr] < NumOfOccurrenc[j]))
                MaxStr = j;
        }
        if(MaxStr == -1)
            return 0;
        std::cout << NumOfOccurrenc[MaxStr] << " " << HashAndStr[MaxStr] << std::endl;
        NumOfOccurrenc[MaxStr] = -1;
    }
    return 0;
}
