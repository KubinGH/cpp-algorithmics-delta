#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000, MAX_E = 10000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static unordered_map<uint32_t, int64_t> W[MAX];
    static unordered_map<uint32_t, uint32_t> trans[MAX];
    vector<tuple<uint32_t, uint32_t, int64_t>> edges;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; int64_t c;
        cin >> u >> v >> c; u--; v--;
        if(W[u].find(v) == W[u].end())
        {
            W[u][v] = c;
            edges.emplace_back(u, v, c);
            trans[u][v] = i;
        }
        else if(c < W[u][v])
        {
            W[u][v] = c;
            get<2>(edges[trans[u][v]]) = c;
        }
    }
    uint32_t x = -1u;
    static int64_t D[MAX];
    static uint32_t P[MAX];
    fill(P, P + n, -1u);
    for(uint32_t i = 0; i < n; i++)
    {
        x = -1u;
        for(auto e : edges)
        {
            uint32_t u, v; int64_t w;
            tie(u, v, w) = e;
            if(D[u] + w < D[v])
            {
                D[v] = D[u] + w;
                P[v] = u;
                x = v;
            }
        }
    }
    if(x == -1u)
        cout << "NIE";
    else
    {
        for(uint32_t i = 0; i < n; i++)
            x = P[x];
        vector<uint32_t> cycle;
        for(uint32_t u = x;; u = P[u])
        {
            cycle.push_back(u);
            if(u == x and cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());
        cout << "TAK\n" << cycle.size()-1 << " ";
        for(uint32_t i = 0; i < cycle.size() - 1; i++)
            cout << trans[cycle[i]][cycle[i+1]]+1 << " ";
    }
}
