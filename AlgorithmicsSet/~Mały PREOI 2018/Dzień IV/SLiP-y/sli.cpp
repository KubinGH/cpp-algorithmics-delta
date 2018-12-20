#include <bits/stdc++.h>

using namespace std;

vector<bool> vis;
void hierholzer(uint32_t u, vector<set<uint32_t>>& graph, vector<uint32_t>& out)
{
    vis[u] = true;
    while(not graph[u].empty())
    {
        uint32_t v = *graph[u].begin();
        graph[u].erase(v); graph[v].erase(u);
        hierholzer(v, graph, out);
    }
    out.push_back(u);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    unordered_map<string, uint32_t> TI;
    vector<string> TS(n);
    for(uint32_t i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        TI[s] = i; TS[i] = s;
    }
    vector<vector<uint32_t>> M(n, vector<uint32_t>(n, 1));
    for(uint32_t i = 0; i < n; i++)
        M[i][i] = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        string a; uint32_t _; string b;
        cin >> a >> _ >> _ >> b;
        M[TI[a]][TI[b]] = 0;
        M[TI[b]][TI[a]] = 0;
    }

    vector<vector<uint32_t>> G(n);
    for(uint32_t u = 0; u < n; u++)
        for(uint32_t v = 0; v < n; v++)
            if(M[u][v]) G[u].push_back(v);
    uint32_t r = 0;
    for(uint32_t u = 0; u < n; u++)
        r += G[u].size() % 2;
    cout << r << "\n";

    vector<set<uint32_t>> Gf(n);
    vector<uint32_t> V1;
    for(uint32_t u = 0; u < n; u++)
    {
        for(uint32_t v : G[u])
            Gf[u].insert(v);
        if(G[u].size() % 2)
            V1.push_back(u);
    }
    for(uint32_t i = 0; i < V1.size(); i += 2)
    {
        Gf[V1[i]].insert(V1[i+1]);
        Gf[V1[i+1]].insert(V1[i]);
    }

    vis.resize(n);
    vector<uint32_t> circuit; circuit.reserve(n*n);
    for(uint32_t u = 0; u < n; u++)
        if(not vis[u])
            hierholzer(u, Gf, circuit);
    auto it0 = circuit.begin(), it1 = circuit.begin(); it1++;
    for(; it1 != circuit.end(); it0++, it1++)
    {
        if(M[*it0][*it1])
            cout << TS[*it0] << " " << TS[*it1] << "\n", M[*it0][*it1]--;
    }
}
