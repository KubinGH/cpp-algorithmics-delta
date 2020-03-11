#include <bits/stdc++.h>

using namespace std;

using uint =  unsigned;

vector<vector<size_t>> graph;
vector<bool> vis;
vector<size_t> stk, hist;
vector<vector<size_t>> cycles;

void dfs(size_t u, size_t p = SIZE_MAX)
{
    vis[u] = true;
    stk[u] = hist.size();
    hist.push_back(u);

    for(auto v : graph[u]) if(v != p)
    {
        if(vis[v] and stk[v])
        {
            cycles.emplace_back();
            cycles.back().reserve(stk[u] - stk[v] + 1);
            for(size_t j = stk[v]; j <= stk[u]; j++)
                cycles.back().push_back(hist[j]);
        }
        else if(not vis[v])
            dfs(v, u);
    }

    hist.pop_back();
    stk[u] = 0;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph.resize(n); vis.resize(n); stk.resize(n);
    hist.reserve(n);

    vector<pair<size_t, size_t>> edges(m);
    vector<unordered_map<size_t, uint>> weight(n);
    for(size_t i = 0; i < m; i++)
    {
        auto& [u, v] = edges[i];
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        weight[u][v] = weight[v][u] = i;
        edges.emplace_back(u, v);
    }

    hist.push_back(stk[0] = SIZE_MAX);

    dfs(0);

    const size_t k = cycles.size();
    vector<vector<size_t>> cycles_here(m);
    for(size_t c = 0; c < k; c++)
        for(size_t i = 0; i < cycles[c].size(); i++)
            cycles_here[weight[cycles[c][i]][cycles[c][i+1 == cycles[c].size() ? 0 : i+1]]].push_back(c);

    vector<uint> result(n, 1), pre(m);
    vector<size_t> count_on_cycle(k);
    for(size_t i = m; i --> 0; )
    {
        auto [u, v] = edges[i];

        size_t filled = SIZE_MAX;
        for(auto c : cycles_here[i])
            if(++count_on_cycle[c] == cycles[c].size())
                assert(filled == SIZE_MAX), filled = c;

        auto r = result[u] + result[v];
        if(filled != SIZE_MAX)
        {
            auto cycle = cycles[filled];
            auto itu = find(cycle.begin(), cycle.end(), u),
                 itv = find(cycle.begin(), cycle.end(), v);
            if(itu > itv)
                swap(u, v), swap(itu, itv);
            rotate(cycle.begin(), itu, cycle.end());
            cycle.push_back(u);

            vector<size_t> w(cycle.size() - 1);
            for(size_t j = 0; j+1 < cycle.size(); j++)
                w[j] = weight[cycle[j]][cycle[j+1]];

            size_t x = max_element(w.begin() + 1, w.end()) - w.begin();

            bool inc = true, dec = true;
            for(size_t j = 1; j < x; j++)
                inc = inc and (w[j] < w[j+1]);
            for(size_t j = x; j+2 < cycle.size(); j++)
                dec = dec and (w[j] > w[j+1]);

            if(inc and dec)
                r -= pre[weight[cycle[x]][cycle[x+1]]];
        }
        pre[i] = result[u] = result[v] = r;
    }

    for(size_t u = 0; u < n; u++)
        cout << result[u] - 1 << ' ';
    cout << endl;
}
