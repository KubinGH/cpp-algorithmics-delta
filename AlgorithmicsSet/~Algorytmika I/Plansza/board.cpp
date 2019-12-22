#include <bits/stdc++.h>

using namespace std;

struct edge_t { size_t u, v; bool used; };

size_t nd(const edge_t& e, size_t u) { return e.u == u ? e.v : e.u; }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(2*n+1);
    vector<edge_t> edges;

    map<pair<size_t, size_t>, size_t> remap;

    auto add_edge = [&](size_t u, size_t v) {
        auto s = edges.size();
        graph[u].push_back(s);
        graph[v].push_back(s);
        remap[{u, v}] = remap[{v, u}] = s;
        edges.push_back({u, v, false});
    };

    for(size_t i = 0; i < m; i++)
    {
        size_t x, y;
        cin >> x >> y; x--; y--;
        add_edge(x, y+n);
    }

    for(size_t u = 0; u < 2*n; u++)
        if(graph[u].size() % 2)
            add_edge(u, 2*n);

    vector<int> no(edges.size());
    for(size_t start = 0; start <= 2*n; start++)
    {
        if(graph[start].empty())
            continue;

        stack<size_t> S;
        vector<size_t> C;
        S.push(start);
        while(not S.empty())
        {
            size_t u = S.top(), i;
            while(not graph[u].empty() and edges[i = graph[u].back()].used)
                graph[u].pop_back();

            if(graph[u].empty())
            {
                S.pop();
                C.push_back(u);
            }
            else
            {
                edges[i].used = true;
                S.push(nd(edges[i], u));
            }
        }
        C.pop_back();
        // intuicyjne ale bez dowodu (bez: kontrprzyklad P_4)
        if(auto it = find(C.begin(), C.end(), 2*n); it != C.end())
            rotate(C.begin(), it, C.end());
        C.push_back(C.front());

        for(size_t i = 0; i+1 < C.size(); i++)
            no[remap[{C[i], C[i+1]}]] = (i % 2 ? -1 : 1);
    }


    cout << "TAK\n";
    for(size_t i = 0; i < m; i++)
        cout << no[i] << '\n';
}
