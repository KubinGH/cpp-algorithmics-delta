#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<size_t>>;

struct pathmap
{
    uint inc = 0;
    unordered_map<uint, uint64_t> c;
    uint64_t& operator[] (uint a) { return c[a - inc]; }
    vector<pair<uint, uint64_t>> items() const
    {
        vector<pair<uint, uint64_t>> out;
        out.reserve(c.size());
        for(auto p : c)
            out.emplace_back(p.first + inc, p.second);
        return out;
    }
};

pathmap* count_paths(const graph_t& graph, size_t u, uint k, uint64_t& of_length_k, size_t lock = SIZE_MAX)
{
    pathmap* total;
    vector<pathmap*> subs;
    for(auto v : graph[u]) if(v != lock)
    {
        auto sub = count_paths(graph, v, k, of_length_k, u);
        sub->inc++;
        subs.push_back(sub);
    }
    if(not subs.empty())
    {
        sort(subs.begin(), subs.end(), [&](pathmap* lhs, pathmap* rhs) {
            return lhs->c.size() < rhs->c.size();
        });
        total = subs.back();
        subs.pop_back();
        auto& rtotal = *total;

        rtotal[0]++;
        of_length_k += rtotal[k];
        reverse(subs.begin(), subs.end());
        for(auto sub : subs)
        {
            auto it = sub->items();
            for(auto p : it)
                of_length_k += rtotal[k - p.first] * p.second;
            for(auto p : it)
                rtotal[p.first] += p.second;
            delete sub;
        }
    }
    else
        total = new pathmap, (*total)[0]++;

    return total;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; uint k;
    cin >> n >> k;

    graph_t graph(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    uint64_t of_length_k = 0;
    auto ptr = count_paths(graph, 0, k, of_length_k);
    delete ptr;

    cout << of_length_k;
}
