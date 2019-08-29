#include <bits/stdc++.h>

using namespace std;

const double RANGE = 1e8;

struct edge
{
    size_t v; int w;
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

vector<size_t> solve_max_matching(
    const vector<vector<edge>>& graph, const vector<size_t>& parent,
    const vector<size_t>& order, double C)
{
    const size_t n = graph.size();

    vector<array<double, 2>> M(n);
    vector<size_t> chosen(n, SIZE_MAX);

    for(auto u : order)
    {
        pair<double, size_t> choice = {INT64_MIN, SIZE_MAX};
        double sum1 = 0;
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

    return matching;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<vector<edge>> graph(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v; int w;
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

    double lo = -RANGE, hi = RANGE;
    while(hi - lo > 1e-9)
    {
        double mid = (lo + hi) / 2;
        auto p = solve_max_matching(graph, parent, order, mid);
        if(p.size() >= k)
            hi = mid;
        else
            lo = mid+1e-9;
    }

    double C = lo + 5e-9;

    auto sol = solve_max_matching(graph, parent, order, C);

    if(sol.size() < k)
    {
        cout << "NIE";
        return 0;
    }

    vector<int64_t> weighties;
    for(auto i : sol)
        weighties.push_back(cost[i]);
    sort(weighties.rbegin(), weighties.rend());

    int64_t result = 0;
    for(size_t i = 0; i < k; i++)
        result += weighties[i];

    cout << "TAK\n" << result;
}
