#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000, MAX_KSUM = 2000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    set<uint32_t> U, R;
    for(uint32_t i = 2; i < n + 1; i++)
        U.insert(i);
    R.insert(1);
    static array<uint32_t, MAX_KSUM> W;
    for(uint32_t mi = 0; mi < m; mi++)
    {
        uint32_t k;
        cin >> k;
        bool f = false;
        for(uint32_t i = 0; i < k; i++)
        {
            cin >> W[i];
            if(f or (i > 0 and *R.rbegin() < W[i] and *R.rbegin() < W[i-1]))
                continue;
            auto it = R.lower_bound(W[i]);
            if(*it < W[i] and (i == 0 or *it > W[i-1]))
                f = true;
            if(it != R.begin())
                it--;
            if(*it < W[i] and (i == 0 or *it > W[i-1]))
                f = true;
        }
        if(*R.rbegin() > W[k-1])
            f = true;
        uint32_t i = 0;
        if(f) for(auto it = U.begin(); it != U.end();)
        {
            uint32_t u = *it;
            while(u > W[i] and i + 1 < k)
                i++;
            if(u < W[i] or (u > W[i] and i == k - 1))
            {
                it = U.erase(it);
                R.insert(u);
            }
            else
                it++;
        }
        if(R.find(n) != R.end())
        {
            cout << mi;
            return 0;
        }
    }
    cout << m;
}
