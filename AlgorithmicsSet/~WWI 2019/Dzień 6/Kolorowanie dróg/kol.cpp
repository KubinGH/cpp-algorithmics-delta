#include <bits/stdc++.h>

using namespace std;

struct interval
{
    size_t L, R;
};

struct disjoint_intervals
{
    vector<size_t> &occ, &of_occ;
    stack<pair<interval, int>> iv;
    disjoint_intervals(vector<size_t>& _occ, vector<size_t>& _of_occ) : occ(_occ), of_occ(_of_occ) {}

    size_t& top_L() { return iv.top().first.L; }
    size_t& top_R() { return iv.top().first.R; }
    int& top_x() { return iv.top().second; }

    void occ_delta(int x, int v)
    {
        of_occ[occ[x]]--;
        occ[x] += v;
        of_occ[occ[x]]++;
    }

    void put_prefix(size_t R, int x)
    {
        while(not iv.empty() and top_R() <= R)
        {
            occ_delta(top_x(), -(top_R() - top_L()));
            iv.pop();
        }
        if(not iv.empty() and top_L() < R)
        {
            occ_delta(top_x(), -(R - top_L()));
            top_L() = R;
        }
        iv.emplace(interval{0, R}, x);
        occ_delta(x, R);
    }
};

struct heavy_light_decomposition
{
    const vector<vector<size_t>>& graph;
    size_t n, c;
    vector<vector<size_t>> children;
    // path_parent - root of path where u is located
    // parent - tree parent
    // path_root - root of path of given index
    // path_no - index of path the vertex is in
    // vertices are colored, the color of u is the color of the edge leading to parent
    // ROOT is always colored in the nonexistent color 0 and subtracted from the result
    vector<size_t> path_parent, parent, path_root, path_no, depth, subtree;
    vector<size_t> occ, of_occ;
    vector<disjoint_intervals> diva;

    heavy_light_decomposition(const vector<vector<size_t>>& _graph, size_t _n, size_t _c)
        : graph(_graph), n(_n), c(_c)
    {
        children.resize(n); parent.resize(n, SIZE_MAX);
        depth.resize(n); subtree.resize(n);
        occ.resize(c + 1); of_occ.resize(n + 1);
        path_parent.resize(n, SIZE_MAX); path_no.resize(n, SIZE_MAX);

        of_occ[0] = c + 1;
        parent[0] = 0;
        dfs_prepare(0, 0);
        dfs_hld(0, 0);
        diva[path_no[0]].put_prefix(1, 0);
    }

    void dfs_prepare(size_t u, size_t lock)
    {
        subtree[u] = 1;
        for(auto v : graph[u]) if(v != lock)
        {
            parent[v] = u;
            children[u].push_back(v);
            depth[v] = depth[u] + 1;
            dfs_prepare(v, u);
            subtree[u] += subtree[v];
        }
    }

    void dfs_hld(size_t u, size_t p_root)
    {
        if(u == p_root)
        {
            path_no[u] = path_root.size();
            diva.emplace_back(occ, of_occ);
            path_root.emplace_back(u);
        }
        path_no[u] = path_no[p_root];
        path_parent[u] = p_root;

        sort(children[u].begin(), children[u].end(), [&](size_t a, size_t b) {
            return subtree[a] > subtree[b];
        });

        if(not children[u].empty())
        {
            dfs_hld(children[u].front(), p_root);
            for(size_t i = 1; i < children[u].size(); i++)
            {
                auto v = children[u][i];
                dfs_hld(v, v);
            }
        }
    }

    void put_path(size_t u, int x)
    {
        do {
            diva[path_no[u]].put_prefix(depth[u] - depth[path_parent[u]] + 1, x);
            u = parent[path_parent[u]];
        } while(u);
        diva[path_no[0]].put_prefix(1, 0);
    }

    size_t get_of_occ(size_t x)
    {
        return of_occ[x] - (occ[0] == x);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, c, q;
    cin >> n >> c >> q;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    heavy_light_decomposition hld(graph, n, c);

    while(q --> 0)
    {
        size_t u, k, m;
        cin >> u >> k >> m; u--;

        hld.put_path(u, k);

        cout << hld.get_of_occ(m) << '\n';
    }
}
