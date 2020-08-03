#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n), weak_graph(n);
    vector<int> in(n), out(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        out[u]++; in[v]++;
        graph[u].push_back(v);
        weak_graph[u].push_back(v);
        weak_graph[v].push_back(u);
    }

    vector<int> ins, outs;
    size_t c = 0;
    vector<bool> vis(n);
    function<void(size_t)> dfs = [&](size_t u) {
        if(vis[u]) return;
        vis[u] = true;
         ins.back() += max(0, out[u] - in[u]);
        outs.back() += max(0, in[u] - out[u]);
        for(auto v : graph[u])
            dfs(v);
    };

    for(size_t s = 0; s < n; s++)
        if(not vis[s])
            ins.push_back(0), outs.push_back(0), c++, dfs(s);

    int r = 0;
    for(size_t i = 0; i < c; i++)
        r += ins[i] + outs[i];
    r /= 2;
    if(r)
      for(size_t i = 0; i < c; i++)
        r += max(ins[i], outs[i]) == 0;
    else if(c > 1)
      r += c;


    cout << r << endl;
}
