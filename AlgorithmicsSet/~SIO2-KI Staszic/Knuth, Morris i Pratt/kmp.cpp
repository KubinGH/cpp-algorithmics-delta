#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;
const char* ANSWER_YES = "Jest.";
const char* ANSWER_NO = "Nie ma go.";

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    string pattern, match;
    pattern.reserve(MAX+1);
    match.reserve(MAX+1);
    // TOFIX:
    // faff fafaff
    for(uint32_t ti = 0; ti < t; ti++)
    {
        cin >> pattern >> match;
        static array<uint32_t, MAX> T;
        uint32_t i = 0, j = 0, group_start = -1,
                 pattern_size = pattern.size();
        while(pattern[pattern_size - 1] == '*') pattern_size--;
        for(; j < match.size() and i < pattern_size; j++)
        {
            if(pattern[i] == '*')
                group_start = -1u;
            if(group_start == -1u)
            {
                while(i < pattern_size and pattern[i] == '*') i++;
                if(i == pattern_size)
                    break;
                group_start = i;
                T[0] = 0;
                for(uint32_t mi = 1; group_start + mi < pattern_size and pattern[group_start + mi] != '*'; mi++)
                {
                    uint32_t mj = T[mi - 1];
                    while(mj > 0 and pattern[group_start+mi] != pattern[group_start+mj])
                        mj = T[mj - 1];
                    if(pattern[group_start+mi] == pattern[group_start+mj])
                        mj++;
                    T[mi] = mj;
                }
            }
            while(i > group_start and pattern[i] != match[j])
                i = group_start + T[i - group_start - 1];
            if(pattern[i] == match[j])
                i++;
        }
        if(i >= pattern_size)
            cout << ANSWER_YES << '\n';
        else
            cout << ANSWER_NO << '\n';
    }
}
