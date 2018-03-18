#include <bits/stdc++.h>

using namespace std;

bool is_vowel(char c)
{
    return c == 'a' or c == 'e' or c == 'i' or
           c == 'o' or c == 'u' or c == 'y';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    vector<uint32_t> P(S.size() + 1);
    for(uint32_t i = 0; i < S.size(); i++)
        P[i+1] = P[i] + is_vowel(S[i]);
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        cout << P[b+1] - P[a] << '\n';
    }
}
