#include <bits/stdc++.h>

using namespace std;

inline bool is_vowel(char c)
    { return c=='a' or c=='e' or c=='i' or c=='o' or c=='u' or c=='y'; }


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    const uint32_t n = S.size();
    if(n < 3)
    {
        cout << 0;
        return 0;
    }
    bool b[3] = {is_vowel(S[0]), is_vowel(S[1]), 0};
    uint64_t r = 0;
    uint32_t q = -1u;
    for(uint32_t i = 2; i < n; i++)
    {
        b[2] = is_vowel(S[i]);
        if(b[0] == b[1] and b[1] == b[2])
            q = i-2;
        r += q+1;
        b[0] = b[1]; b[1] = b[2];
    }
    cout << r;
}
