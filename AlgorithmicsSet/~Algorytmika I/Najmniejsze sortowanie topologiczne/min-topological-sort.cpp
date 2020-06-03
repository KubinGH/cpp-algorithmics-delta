#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n);
    vector<size_t> in(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v); in[v]++;
    }

    priority_queue<size_t, vector<size_t>, greater<size_t>> Q;
    for(size_t u = 0; u < n; u++)
        if(not in[u])
            Q.push(u);

    vector<size_t> topo;
    while(not Q.empty())
    {
        auto u = Q.top(); Q.pop();
        topo.push_back(u);
        for(auto v : graph[u])
            if(not --in[v])
                Q.push(v);
    }

    if(not *max_element(in.begin(), in.end()))
    {
        cout << "TAK" << endl;
        for(auto u : topo)
            cout << u+1 << ' ';
        cout << endl;
    }
    else
        cout << "NIE" << endl;
}
