#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 19;

size_t n;
vector<size_t> graph[MAX];


pair<int, size_t> dfs_max(size_t u, size_t glock = SIZE_MAX, size_t lock = MAX)
{
    pair<int, size_t> ret = {0, u};
    for(auto v : graph[u])
      if(v != glock and v != lock)
    {
        auto sub = dfs_max(v, glock, u);
        sub.first++;
        if(sub > ret)
            ret = sub;
    }
    return ret;
}


tuple<int, size_t, size_t> diameter(size_t init, size_t glock = SIZE_MAX)
{
    auto [_, x] = dfs_max(init, glock);
    auto [d, y] = dfs_max(x, glock);
    return {d, x, y};
}


void dfs_list(size_t u, vector<size_t>& lst, size_t glock = SIZE_MAX, size_t lock = SIZE_MAX)
{
    lst.push_back(u);
    for(auto v : graph[u])
        if(v != glock and v != lock)
            dfs_list(v, lst, glock, u);
}


size_t diameter_center(size_t a, size_t glock = SIZE_MAX)
{
    vector<size_t> deg(n+1);
    for(size_t u = 1; u <= n; u++)
        deg[u] = graph[u].size() - (find(graph[u].begin(), graph[u].end(), glock) != graph[u].end());

    vector<bool> pop(n+1);

    queue<size_t> Q;

    vector<size_t> lst;
    dfs_list(a, lst, glock);
    for(auto u : lst)
        if(deg[u] == 1)
            Q.push(u);

    size_t last = a;

    while(not Q.empty())
    {
        auto u = Q.front(); Q.pop();
        if(pop[u]) continue;
        pop[u] = true;
        last = u;
        for(auto v : graph[u])
            if(v != glock and --deg[v] == 1)
                Q.push(v);
    }

    return last;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;

    vector<pair<size_t, size_t>> edges(n-1);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    tuple<int, size_t, size_t, size_t, size_t> best = {INT_MAX, 0, 0, 0, 0}, worst = {0, 0, 0, 0, 0};

    for(auto [x1, y1] : edges)
    {
        auto [d1, a1, b1] = diameter(x1, y1);
        auto [d2, a2, b2] = diameter(y1, x1);

        int d_min = max({(d1+1)/2 + (d2+1)/2 + 1, d1, d2}), d_max = d1+d2+1;

        if(d_min < get<0>(best))
        {
            auto c1 = diameter_center(a1, y1), c2 = diameter_center(a2, x1);
            best = {d_min, x1, y1, c1, c2};
        }

        if(d_max > get<0>(worst))
            worst = {d_max, x1, y1, a1, a2};
    }

    cout << get<0>(best) << ' ' << get<1>(best) << ' ' << get<2>(best) << ' ' << get<3>(best) << ' ' << get<4>(best) << endl;
    cout << get<0>(worst) << ' ' << get<1>(worst) << ' ' << get<2>(worst) << ' ' << get<3>(worst) << ' ' << get<4>(worst) << endl;
}
