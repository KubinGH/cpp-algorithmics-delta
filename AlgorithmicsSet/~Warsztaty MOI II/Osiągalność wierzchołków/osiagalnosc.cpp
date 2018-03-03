#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<vector<uint32_t>, MAX> G;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    static array<bool, MAX> V;
    queue<uint32_t> Q;
    V[0] = true;
    Q.push(0);
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        for(uint32_t v : G[u])
        {
            if(not V[v])
            {
                V[v] = true;
                Q.push(v);
            }
        }
    }
    for(uint32_t i = 0; i < n; i++)
        cout << (V[i] ? "TAK" : "NIE") << '\n';
}
