#pragma GCC optimize ("O2")
#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, q;
    cin >> n >> m >> q;
    static uint64_t wealth[MAX], value[MAX];
    static vector<uint32_t> sub[MAX], large_owners[MAX];
    uint32_t Q = floor(sqrt(n)) + 1;
    while(q --> 0)
    {
        uint32_t t;
        cin >> t;
        if(t == 1)
        {
            uint32_t f; uint64_t z; cin >> f >> z; f--;
            value[f] += z;
            for(uint32_t o : large_owners[f])
                wealth[o] += z;
        }
        else if(t == 2)
        {
            uint32_t o;
            cin >> o; o--;
            if(sub[o].size() < Q)
            {
                uint64_t r = 0;
                for(uint32_t s : sub[o])
                    r += value[s];
                cout << r << "\n";
            }
            else
                cout << wealth[o] << "\n";
        }
        else if(t == 3)
        {
            uint32_t o, f;
            cin >> o >> f; o--; f--;
            sub[o].push_back(f);
            if(sub[o].size() < Q) {}
            else if(sub[o].size() == Q)
            {
                for(uint32_t s : sub[o])
                {
                    large_owners[s].push_back(o);
                    wealth[o] += value[s];
                }
            }
            else if(sub[o].size() > Q)
            {
                large_owners[f].push_back(o);
                wealth[o] += value[f];
            }
        }
    }
}
