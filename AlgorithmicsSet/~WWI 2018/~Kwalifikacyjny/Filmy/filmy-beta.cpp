#include <bits/stdc++.h>

using namespace std;

const size_t MAX_M = 20, MAX_C = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m, finish;
    cin >> m >> finish;
    static vector<uint32_t> S[MAX_M];
    static uint32_t D[MAX_M];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t c; cin >> D[i] >> c;
        for(uint32_t j = 0; j < c; j++)
        {
            uint32_t b; cin >> b;
            S[i].push_back(b);
        }
    }
    static uint32_t R[1u << MAX_M];
    uint32_t result = -1u;
    for(uint32_t p = 1; p < (1u << m); p++)
    {
        for(uint32_t i = 0; i < m; i++)
        {
            if(p & (1u << i))
            {
                uint32_t q = p ^ (1u << i);
                auto it = upper_bound(S[i].begin(), S[i].end(), R[q]);
                if(it == S[i].begin()) continue;
                it--;
                R[p] = max(R[p], *it + D[i]);
            }
        }
        if(R[p] > finish)
            result = min(result, (uint32_t)__builtin_popcount(p));
    }
    cout << int(result);
}
