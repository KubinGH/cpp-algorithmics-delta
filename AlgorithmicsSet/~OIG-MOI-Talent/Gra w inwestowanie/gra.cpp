#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t n, k;
    cin >> n >> k;
    static vector<uint64_t> DP(n+1);
    map<uint64_t, uint64_t, greater<uint64_t>> consider;
    DP[1] = k+1;
    for(uint64_t i = 2; i <= n; i++)
    {
        DP[i] = i + k;
        for(auto p : consider)
        {
            uint64_t j = p.second;
            DP[i] = min(DP[i], DP[j] + (i+j-1)/j + k);
        }
        while(not consider.empty() and consider.begin()->first >= DP[i])
            consider.erase(consider.begin());
        consider[DP[i]] = i;
    }
    cout << DP[n]-k;
}
