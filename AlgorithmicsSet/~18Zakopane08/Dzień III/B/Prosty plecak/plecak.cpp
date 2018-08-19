#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 128;

int main()
{
    uint32_t n, w;
    cin >> n >> w;
    static vector<uint64_t> W[4];
    uint64_t b, v;
    cin >> b >> v;
    W[0].push_back(v);
    for(uint32_t i = 1; i < n; i++)
    {
        uint32_t q, p;
        cin >> q >> p;
        W[q-b].push_back(p);
    }
    static vector<uint64_t> S[4];
    for(uint32_t i = 0; i < 4; i++)
    {
        sort(W[i].begin(), W[i].end(), greater<uint64_t>());
        S[i].resize(W[i].size()+1);
        S[i][0] = 0;
        partial_sum(W[i].begin(), W[i].end(), S[i].begin()+1);
    }
    uint32_t t[4] = {0, 0, 0, 0};
    uint64_t r = 0;
    while(true)
    {
        t[0]++;
        for(uint32_t i = 0; i < 3; i++)
            if(t[i] == W[i].size()+1)
                t[i+1]++, t[i] = 0;
        if(t[3] == W[3].size()+1)
            break;
        uint64_t s = 0;
        for(uint32_t i = 0; i < 4; i++)
            s += (b+i) * t[i];
        if(s <= w)
            r = max(r, S[0][t[0]] + S[1][t[1]] + S[2][t[2]] + S[3][t[3]]);
    }
    cout << r;
}
