#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    static vector<uint64_t> DP(n+1);
    DP[1] = 0;
    for(uint64_t i = 2; i <= n; i++)
    {
        DP[i] = -1LLU;
        for(uint64_t j = 1; j < i; j++)
            DP[i] = min(DP[i], DP[j] + (i+j-1)/j + k);
    }
    uint64_t r = -1LLU;
    for(uint32_t i = 1; i <= n; i++)
        r = min(r, DP[i] + (n+i-1)/i);
    cout << r;
}
