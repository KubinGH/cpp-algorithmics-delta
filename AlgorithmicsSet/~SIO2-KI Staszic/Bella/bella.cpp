#include <bits/stdc++.h>

using namespace std;

template<typename T>
string to_string(const T& o)
{
    stringstream s;
    s << o;
    return s.str();
}

uint32_t count_prefix_7(const string& str)
{
    uint32_t r = 0;
    for(uint32_t k = 0; k < str.size(); k++)
        if(str[k] == '7') r++;
        else break;
    return r;
}
uint32_t count_suffix_7(const string& str)
{
    uint32_t r = 0;
    for(uint32_t k = str.size(); k --> 0; )
    {
        if(str[k] == '7') r++;
        else break;
    }
    return r;
}
uint32_t count_interfix_7(const string& str)
{
    uint32_t r = 0, c = 0;
    for(uint32_t k = 0; k < str.size(); k++)
    {
        if(str[k] == '7') c++;
        else r = max(r, c), c = 0;
    }
    return max(r, c);
}

int main()
{
    uint64_t a, b;
    cin >> a >> b;
    vector<string> c_prefixes[32], c_suffixes[32];
    string M;
    string current = to_string(a-1);
    uint32_t r = 0;
    for(uint64_t i = a; i <= b; i++)
    {
        current.back()++;
        for(uint32_t j = current.size(); j --> 1; )
            if(current[j] > '9')
                current[j] = '0', current[j-1]++;
        if(current[0] > '9')
            current[0] = '0', current.insert(0, "1");
        uint32_t suffix_count = count_suffix_7(current), prefix_count = count_prefix_7(current);
        if(prefix_count == current.size() and suffix_count == current.size())
            M += current;
        else
        {
            if(c_prefixes[prefix_count].size() < 16)
                c_prefixes[prefix_count].push_back(current);
            if(c_suffixes[suffix_count].size() < 16)
                c_suffixes[suffix_count].push_back(current);
        }
        r = max(r, count_interfix_7(current));
    }
    vector<string> prefixes = {""}, suffixes = {""};
    for(uint32_t i = 0; i < 32; i++)
        for(string c : c_prefixes[i])
            prefixes.push_back(c);
    for(uint32_t i = 0; i < 32; i++)
        for(string c : c_suffixes[i])
            suffixes.push_back(c);
    for(string A : suffixes)
      for(string B : prefixes)
    {
        bool Ae = A.empty(), Be = B.empty();
        if(!Ae and !Be and A == B)
            continue;
        r = max(r, count_suffix_7(A) + M.size() + count_prefix_7(B));
    }
    cout << r;
}
