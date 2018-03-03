#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m;
    cin >> m;
    static array<uint32_t, MAX> A;
    static array<vector<uint32_t>, MAX+1> P;
    for(uint32_t i = 0; i < m; i++)
        cin >> A[i], P[A[i]].push_back(i);
    uint32_t t;
    cin >> t;
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t n;
        cin >> n;
        uint32_t j = 0;
        bool ok = true, first = true;
        for(uint32_t i = 0; i < n; i++)
        {
            uint32_t b;
            cin >> b;
            if(not ok)
                continue;
            else if(P[b].empty())
                ok = false;
            else if(first)
            {
                j = P[b][0];
                first = false;
            }
            else
            {
                auto it = upper_bound(P[b].begin(), P[b].end(), j);
                if(it == P[b].end())
                    ok = false;
                else
                    j = *it;
            }
        }
        cout << (ok ? "TAK\n" : "NIE\n");
    }
}
