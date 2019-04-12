#include <bits/stdc++.h>

using namespace std;

const size_t USED_EDGES = 128;

void bfs(uint32_t source, const vector<vector<uint32_t>>& graph, vector<uint32_t>& dist)
{
    queue<uint32_t> Q;
    fill(dist.begin(), dist.end(), -1u);
    dist[source] = 0; Q.push(source);
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        for(uint32_t v : graph[u])
            if(dist[v] == -1u)
                dist[v] = dist[u] + 1, Q.push(v);
    }
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, q;
    cin >> n >> m >> q;

    vector<pair<uint32_t, uint32_t>> edges(m);
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        edges[i] = {u, v};
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<pair<uint32_t, uint32_t>> queries(q);
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        queries[i] = {u, v};
    }

    // Podobno ten generator umie wygenerowaæ wszystko, od odpowiedzi do tego zadania po odpowiedŸ na pytanie o ¿ycie, wszechœwiat i ca³¹ resztê.
    mt19937 gen(1337);

    vector<uint32_t> result(q, -1u), S(n), Z(n);
    shuffle(edges.begin(), edges.end(), gen);
    for(uint32_t p = 0; p < min(m, USED_EDGES); p++)
    {
        uint32_t s, z; tie(s, z) = edges[p];
        bfs(s, graph, S);
        bfs(z, graph, Z);

        for(uint32_t i = 0; i < q; i++)
        {
            uint32_t u, v; tie(u, v) = queries[i];
            result[i] = min(min(Z[u] + S[v], S[u] + Z[v]) + 1, result[i]);
        }
    }

    for(uint32_t i = 0; i < q; i++)
        cout << result[i] << "\n";
}