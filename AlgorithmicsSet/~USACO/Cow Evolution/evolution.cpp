#include <bits/stdc++.h>

using namespace std;

int main()
{
#ifndef XHOVA
    ifstream cin("evolution.in");
    ofstream cout("evolution.out");
#endif
    uint32_t n;
    cin >> n;
    vector<vector<uint32_t>> F(n);
    unordered_map<string, uint32_t> T;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t k;
        cin >> k;
        for(uint32_t j = 0; j < k; j++)
        {
            string s;
            cin >> s;
            if(not T.count(s))
                T[s] = T.size();
            F[i].push_back(T[s]);
        }
        sort(F[i].begin(), F[i].end());
    }

}
