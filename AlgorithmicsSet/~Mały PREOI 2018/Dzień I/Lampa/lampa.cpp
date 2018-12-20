#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, h;
    cin >> h >> w;
    uint32_t n = (w+1)*(h+1);
    vector<vector<pair<uint32_t, bool>>> G((w+1)*(h+1));
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
    {
        char c; cin >> c;
        bool b = (c == '/');
        uint32_t v00 = y*(w+1)+x, v01 = v00+1, v10 = v00+(w+1), v11 = v10+1;
        G[v00].emplace_back(v11, b); G[v11].emplace_back(v00, b);
        G[v01].emplace_back(v10, !b); G[v10].emplace_back(v01, !b);
    }
    vector<bool> V(n);
    vector<uint32_t> D(n, -1u);
    deque<pair<uint32_t, uint32_t>> Q;
    Q.emplace_back(0, 0); D[0] = 0;
    while(not Q.empty())
    {
        uint32_t u, c; tie(u, c) = Q.front(); Q.pop_front();
        if(D[u] < c) continue;
        for(auto e : G[u])
        {
            uint32_t v = e.first; bool b = e.second;
            if(D[u]+b < D[v])
            {
                D[v] = D[u]+b;
                if(b == 0)
                    Q.emplace_front(v, D[v]);
                else
                    Q.emplace_back(v, D[v]);
            }
        }
    }
    if(D[n-1] == -1u)
        cout << "NIE";
    else
        cout << D[n-1];
}
