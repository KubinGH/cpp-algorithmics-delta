#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 12;

typedef pair<uint32_t, uint32_t> pair_u32;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<uint32_t> X[MAX];
    static bitset<MAX> E[MAX];
    queue<pair_u32> Q;
    uint64_t r = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t x, y;
        cin >> x >> y;
        X[x].push_back(y);
        Q.emplace(x, y);
        E[x][y] = true;
        r++;
    }
    while(not Q.empty())
    {
        auto p = Q.front(); Q.pop();
        uint32_t x = p.first, y = p.second;
        //cout << x << ", " << y << endl;
        for(uint32_t z : X[y])
        {
            if(not E[z][x])
            {
                E[z][x] = true;
                X[z].push_back(x);
                Q.emplace(z, x);
                r++;
            }
        }
    }
    cout << r;
}
