#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<uint32_t>> G(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<uint32_t> D(n, -1u);
    vector<vector<uint32_t>> L(n);
    queue<uint32_t> Q;
    Q.push(0); D[0] = 0;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        L[D[u]].push_back(u);
        for(uint32_t v : G[u])
            if(D[v] != -1u)
                Q.push(v), D[v] = D[u] + 1;
    }

}
