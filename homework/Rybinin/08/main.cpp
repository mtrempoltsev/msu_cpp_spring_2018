#include<bits/stdc++.h>
#include<string>

const long long prost = 536870913;
int main(int argc,char** argv)
{
    if(argc != 2)
        return 1;
    std::ifstream file(argv[1]);
    if (!file)
        return 1;
    std::string s;
    getline(file, s);
    int i = 0;
    std::map<int, int> m;
    std::map<int, std::string> g;
    std::set<int> st;
    while(i < s.size())
    {
        while(i < s.size() && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
            i++;
        std::string str;
        long long hashh = 0;
        while(i < s.size() && s[i] != ' ' && s[i] != '\t' && s[i] != '\n'){
            str += s[i];
            hashh = ((hashh+s[i])*prost) % 1000000000;
            i++;
        }
        st.insert(hashh);
        m[hashh]++;
        if(g[hashh].empty())
            g[hashh] = str;
    }
    for(int i = 0; i < 10; ++i){
        int mx = -1;
        for(auto j : st){
            if(m[j] != -1 && (mx == -1 || m[mx] < m[j]))
                mx = j;
        }
        if(mx == -1)
            return 0;
        std::cout << m[mx] << " " << g[mx] << std::endl;
        m[mx] = -1;
    }
    return 0;
}
