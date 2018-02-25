#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 8000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m; cin >> n >> m;
    string pattern, text; pattern.reserve(n); text.reserve(m);
    cin >> pattern >> text;
    static array<uint32_t, MAX> T;
    T[0] = 0;
    for(uint32_t i = 1; i < pattern.size(); i++)
    {
        uint32_t j = T[i - 1];
        while(j > 0 and pattern[i] != pattern[j])
            j = T[j - 1];
        if(pattern[i] == pattern[j])
            j++;
        T[i] = j;
    }
    uint32_t j = 0;
    for(uint32_t i = 0; i < text.size(); i++)
    {
        while(j > 0 and text[i] != pattern[j])
            j = T[j - 1];
        if(text[i] == pattern[j])
        {
            j++;
            if(j == pattern.size())
            {
                cout << i + 2 - pattern.size() << '\n';
                j = T[j - 1];
            }
        }
    }
}
