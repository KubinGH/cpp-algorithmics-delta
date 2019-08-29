#include <bits/stdc++.h>

using namespace std;

struct edge
{
    size_t v; int64_t w;
};

void recover_matching(
    const vector<vector<edge>>& graph, const vector<size_t>& parent,
    const vector<size_t>& chosen, size_t u, bool b, vector<size_t>& out)
{
    for(auto e : graph[u]) if(parent[e.v] == u)
    {
        if(b and chosen[u] == e.v)
        {
            out.push_back(e.v);
            recover_matching(graph, parent, chosen, e.v, 0, out);
        }
        else
        {
            recover_matching(graph, parent, chosen, e.v, 1, out);
        }
    }
}

pair<int64_t, vector<size_t>> solve_max_matching(
    const vector<vector<edge>>& graph, const vector<size_t>& parent,
    const vector<size_t>& order, int64_t C)
{
    const size_t n = graph.size();

    vector<array<int64_t, 2>> M(n);
    vector<size_t> chosen(n, SIZE_MAX);

    for(auto u : order)
    {
        pair<int64_t, size_t> choice = {INT64_MIN, SIZE_MAX};
        int64_t sum1 = 0;
        for(auto e : graph[u]) if(parent[e.v] == u)
        {
            choice = max(choice, make_pair((C + e.w + M[e.v][0]) - M[e.v][1], e.v));
            sum1 += M[e.v][1];
        }
        M[u][0] = M[u][1] = sum1;
        if(choice.first > 0)
        {
            M[u][1] += choice.first;
            chosen[u] = choice.second;
        }
    }

    vector<size_t> matching;
    matching.reserve(n);
    recover_matching(graph, parent, chosen, 0, 1, matching);

    return {M[0][1], matching};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<vector<edge>> graph(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v; int64_t w;
        cin >> u >> v >> w; u--; v--;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<size_t> parent(n, SIZE_MAX), order;
    vector<int64_t> cost(n);
    order.reserve(n);

    parent[0] = 0;
    function<void(size_t)> dfs_root = [&](size_t u) {
        for(auto e : graph[u])
            if(parent[e.v] == SIZE_MAX)
                parent[e.v] = u, cost[e.v] = e.w, dfs_root(e.v);
        order.push_back(u);
    };
    dfs_root(0);

    const int64_t RANGE = 1e12;
    int64_t lo = 0, hi = 2*RANGE;
    while(lo < hi)
    {
        int64_t mid = (lo + hi) / 2;
        auto p = solve_max_matching(graph, parent, order, mid - RANGE);
        cerr << mid-RANGE << ": " << p.first << ", " << p.second.size() << endl;
        if(p.second.size() >= k)
            hi = mid;
        else
            lo = mid+1;
    }

    int64_t C = lo - RANGE;
    cerr << "C = " << C << endl;

    auto sol = solve_max_matching(graph, parent, order, C);

    if(sol.second.size() < k)
    {
        cout << "NIE";
        return 0;
    }

    cerr << "-> " << sol.first << endl;

    auto bsol = solve_max_matching(graph, parent, order, C-1);

    int64_t real = sol.first - C*(int64_t)sol.second.size(), breal = bsol.first - (C-1)*(int64_t)bsol.second.size();
    int64_t b = (breal-real)/int64_t(sol.second.size()-bsol.second.size());

    cerr << real << " " << breal << " " << b << endl;

    cout << "TAK\n" << (real + int64_t(sol.second.size() - k)*b);
}
