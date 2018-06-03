#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<set<uint32_t>, MAX> GS;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        GS[u].insert(v); GS[v].insert(u);
    }
    uint32_t result = 0;
    for(uint32_t u = 0; u < n; u++)
    {
        for(auto ita = GS[u].upper_bound(u); ita != GS[u].end(); ita++)
        {
            uint32_t a = *ita;
            if(GS[a].size() < 2) continue;
            for(auto itb = GS[u].upper_bound(a); itb != GS[u].end(); itb++)
            {
                uint32_t b = *itb;
                if(GS[a].find(b) != GS[a].end())
                    result++;
            }
        }
    }
    cout << result;
}
