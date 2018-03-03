#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string in;
    cin >> in;
    static array<array<uint32_t, 26>, MAX+1> S;
    for(uint32_t i = 0; i < in.size(); i++)
    {
        S[i+1] = S[i];
        S[i+1][in[i] - 'a']++;
    }
    uint32_t q;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        uint32_t m = 0, c = 0;
        for(uint32_t i = 0; i < 26; i++)
        {
            if(m < S[b+1][i] - S[a][i])
                m = S[b+1][i] - S[a][i], c = i;
        }
        cout << (char)(c + 'a');
    }
}
