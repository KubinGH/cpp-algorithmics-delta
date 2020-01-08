#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    string S;
    cin >> S;

    array<vector<uint>, 26> C;
    for(size_t c = 0; c < 26; c++)
    {
        C[c].resize(n+1);
        for(size_t i = 0; i < n; i++)
        {
            uint x = c == size_t(S[i]-'a');
            C[c][i+1] = C[c][i] + x;
        }
    }


    while(m --> 0)
    {
        size_t a, b;
        cin >> a >> b; a--;

        uint64_t q = 0;
        for(size_t c = 0; c < 26; c++)
        {
            uint64_t t = C[c][b] - C[c][a];
            q += t*t;
        }

        cout << (uint64_t(b-a)*(b-a) - q) / 2 + 1 << '\n';
    }
}
