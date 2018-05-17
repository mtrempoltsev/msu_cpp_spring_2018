#include <iostream>
#include <fstream>
#include <map>

struct Word
{
    char* data_;

    Word()
    {
    }

    Word(char* data)
    {
        data_ = data;
    }

    ~Word()
    {
        delete data_;
        data_ = 0;
    }

    bool operator<(Word y)
    {
        return data_ < y.data_;
    }
};

std::map<Word, int> freqMap;

int main(int argc, char* argv[])
{
    auto fileName = argv[1];

    std::fstream file(fileName);

    char c;

    do
    {
        do { c = file.get(); } while (c == ' ');

        file.put(c);

        char* buf = new char[64];

        for (int i = 0; i < 64; ++i)
        {
            buf[i] = file.get();
            if (buf[i] == ' ')
                break;
        }

        do { c = file.get(); } while (c == ' ');

        Word w(buf);

        if (freqMap.count(w) != 0)
            freqMap[w] = freqMap[w] + 1;
        else
            freqMap[w] = 0;
    } while (file.good());

    for (auto p : freqMap)
        std::cout << p.first.data_ << " = " << p.second;

    return 0;
}
