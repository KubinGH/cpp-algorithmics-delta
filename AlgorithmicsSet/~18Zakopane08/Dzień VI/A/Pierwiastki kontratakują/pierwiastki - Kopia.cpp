#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

typedef pair<uint32_t, uint32_t> pair_u32;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    set<pair_u32> S;
    vector<uint32_t> X[MAX];
    queue<pair_u32> Q;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t x, y;
        cin >> x >> y;
        S.emplace(x, y);
        X[x].push_back(y);
        Q.emplace(x, y);
    }
    while(not Q.empty())
    {
        auto p = Q.front(); Q.pop();
        uint32_t x = p.first, y = p.second;
        cout << x << ", " << y << endl;
        for(uint32_t z : X[y])
        {
            if(S.find(pair_u32{z, x}) == S.end())
            {
                S.emplace(z, x);
                X[z].push_back(x);
                Q.emplace(z, x);
            }
        }
    }
    cout << S.size();
}
