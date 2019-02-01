#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 11;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;

    const uint64_t oo = 1LLU << 60;
    vector<vector<array<uint64_t, 2>>> W(n, vector<array<uint64_t, 2>>(n, {oo, oo}));
    vector<vector<uint32_t>> G(n);

    vector<uint32_t> indegree(n);

    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        cin >> W[u][v][0] >> W[u][v][1];
        G[u].push_back(v);
        indegree[v]++;
    }

    vector<uint32_t> T; T.reserve(n);
    for(uint32_t u = 0; u < n; u++)
        if(indegree[u] == 0)
            T.push_back(u);
    vector<bitset<N>> P(n);
    for(uint32_t t = 0; t < T.size(); t++)
    {
        uint32_t u = T[t];
        P[u].set(u);
        for(uint32_t v : G[u])
        {
            P[v] |= P[u];
            if(--indegree[v] == 0)
                T.push_back(v);
        }
    }

    vector<vector<uint64_t>> Q(n, vector<uint64_t>(n, oo));
    min_priority_queue<pair<uint64_t, pair<uint32_t, uint32_t>>> V;
    auto update = [&](uint32_t u, uint32_t v, uint64_t q) {
        if(q < Q[u][v])
            V.emplace(Q[u][v] = q, make_pair(u, v));
    };
    update(0, 0, 0);
    while(not V.empty())
    {
        uint32_t u, v;
        tie(u, v) = V.top().second;
        uint64_t q = V.top().first;
        V.pop();
        if(q > Q[u][v]) continue;

        if(u == v)
          for(uint32_t u1 : G[u])
            for(uint32_t v1 : G[u])
              if(u1 != v1)
                update(u1, v1, Q[u][u] + W[u][u1][0] + W[u][v1][0]);
              else
                update(u1, u1, Q[u][u] + W[u][u1][0] + W[u][v1][1]);
        else if(P[u][v])
            for(uint32_t v1 : G[v])
                update(u, v1, Q[u][v] + W[v][v1][0]);
        else
            for(uint32_t u1 : G[u])
                update(u1, v, Q[u][v] + W[u][u1][0]);
    }

    cout << Q[n-1][n-1];
}
