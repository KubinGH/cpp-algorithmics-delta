#include <bits/stdc++.h>

using namespace std;

template<typename T>
    using minq = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<pair<uint32_t, uint64_t>>> G;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; uint64_t w;
        cin >> u >> v >> w; u--; v--;
        G[u].emplace_back(v, w);
    }
    minq<pair<uint64_t, uint32_t>> Q;
    uint32_t X, Y;
    cin >> X >> Y; X--; Y--;
    vector<uint64_t> D(n, -1LLU);
    Q.emplace(D[X] = 0, X);
    while(not Q.empty())
    {
        auto p = Q.top(); Q.pop();
        uint32_t u = p.first; uint64_t d = p.second;
        if(d > D[u]) continue;
        for(auto e : G[p.first])
        {
            uint32_t v = e.first; uint64_t w = e.second;
            if(D[u] + w < D[v])
                Q.emplace(D[v] = D[u] + w, v);
        }
    }
    cout << D[Y];
}
