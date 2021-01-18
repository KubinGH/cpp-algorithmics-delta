#include <bits/stdc++.h>

using namespace std;

constexpr uint mod = 1e9 + 7;

uint64_t getms() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(); }

vector<size_t> segments(size_t w, size_t l, size_t r)
{
    vector<size_t> nodes;
    for(l += w, r += w; l < r; l /= 2, r /= 2)
    {
        if(l % 2) nodes.emplace_back(l++);
        if(r % 2) nodes.emplace_back(--r);
    }
    return nodes;
}

struct kosaraju
{
    using graph_t = vector<vector<size_t>>;

    const graph_t& graph;
    size_t n;
    vector<bool> vis;

    kosaraju(const graph_t& _graph) : graph(_graph), n(graph.size()), vis(n) {}

    void marker_dfs(size_t u, const graph_t& G, vector<size_t>& out)
    {
        vis[u] = true;
        for(size_t v : G[u])
            if(not vis[v])
                marker_dfs(v, G, out);
        out.push_back(u);
    }

    pair<vector<vector<size_t>>, vector<size_t>>
    operator() ()
    {
        vector<size_t> order; order.reserve(n);
        fill(vis.begin(), vis.end(), false);
        for(size_t u = 0; u < n; u++)
            if(not vis[u])
                marker_dfs(u, graph, order);

        graph_t graph_T(n);
        for(size_t u = 0; u < n; u++)
            for(size_t v : graph[u])
                graph_T[v].push_back(u);

        fill(vis.begin(), vis.end(), false);
        reverse(order.begin(), order.end());
        vector<vector<size_t>> scc;
        vector<size_t> scc_idx(n);
        for(size_t u : order)
        {
            if(vis[u]) continue;
            scc.emplace_back();
            marker_dfs(u, graph_T, scc.back());
            for(auto i : scc.back())
                scc_idx[i] = scc.size() - 1;
        }
        return {scc, scc_idx};
    }

    graph_t make_scc_graph(const vector<vector<size_t>>& scc, const vector<size_t>& scc_idx)
    {
        fill(vis.begin(), vis.end(), false);
        graph_t scc_graph(scc.size());
        for(size_t i = 0; i < scc.size(); i++)
        {
            vis[i] = true;
            for(auto u : scc[i])
              for(auto v : graph[u])
                if(not vis[scc_idx[v]])
            {
                vis[scc_idx[v]] = true;
                scc_graph[i].push_back(scc_idx[v]);
            }
            vis[i] = false;
            for(auto e : scc_graph[i])
                vis[e] = false;
        }
        return scc_graph;
    }

    graph_t make_scc_graph()
    {
        vector<vector<size_t>> scc;
        vector<size_t> scc_idx;
        tie(scc, scc_idx) = operator() ();
        return make_scc_graph(scc, scc_idx);
    }
};


struct fenwick_tree
{
    size_t n;
    vector<size_t> F;

    fenwick_tree(size_t m) : n(m), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    uint get_prefix(size_t p) const
    {
        uint r = 0;
        while(p)
            r = (r + F[p]) % mod, p -= lsb(p);
        return r;
    }

    void delta(size_t p, uint v)
    {
        p++;
        while(p <= n)
            F[p] = (F[p] + v) % mod, p += lsb(p);
    }
};


vector<vector<size_t>> construct_explosion_graph(
    const vector<int64_t>& A, const vector<int64_t>& R)
{
    const size_t n = A.size();

    const size_t w = 1 << __lg(2*n - 1);

    vector<vector<size_t>> graph(2*w);
    for(size_t i = 0; i < n; i++)
    {
        size_t l = lower_bound(A.begin(), A.end(), A[i] - R[i]) - A.begin(),
               r = upper_bound(A.begin(), A.end(), A[i] + R[i]) - A.begin();
        for(auto v : segments(w, l, r))
            graph[i + w].push_back(v);
    }
    for(size_t i = 1; i < w; i++)
        graph[i].push_back(2*i), graph[i].push_back(2*i+1);

    return graph;
}


vector<pair<size_t, size_t>> get_explosion_intervals(
    size_t n, const vector<vector<size_t>>& graph)
{
    const size_t w = graph.size() / 2;

    kosaraju kosa(graph);
    auto [scc, scc_idx] = kosa();
    auto scc_graph = kosa.make_scc_graph(scc, scc_idx);

    const size_t s = scc.size();
    vector<bool> exists(s);
    vector<size_t> left(s, n), right(s, 0);
    vector<pair<size_t, size_t>> intervals;
    for(size_t i = s; i --> 0; )
    {
        for(auto u : scc[i])
          if(w <= u and u < w+n)
        {
            exists[i] = true;
            left [i] = min(left [i], u-w);
            right[i] = max(right[i], u-w);
        }

        for(auto j : scc_graph[i])
        {
             left[i] = min( left[i],  left[j]);
            right[i] = max(right[i], right[j]);
        }

        if(exists[i])
            intervals.emplace_back(left[i], right[i]);
    }

    return intervals;
}


uint count_nondominated_subsets(size_t m, vector<pair<size_t, size_t>> I)
{
    const size_t n = I.size();

    sort(I.begin(), I.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first or (lhs.first == rhs.first and lhs.second > rhs.second);
    });
    fenwick_tree F(m+1);
    F.delta(0, +1);
    for(size_t i = n; i --> 0; )
    {
        auto v = F.get_prefix(I[i].second+1 + 1);
        F.delta(0, v); F.delta(I[i].second+1, mod-v);
    }

    return F.get_prefix(0 + 1);
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n0;
    cin >> n0;
    vector<int64_t> A(n0), R(n0);
    for(size_t i = 0; i < n0; i++)
        //cin >> A[i] >> R[i];
        A[i] = i, R[i] = n0/3;

    cout << count_nondominated_subsets(n0, get_explosion_intervals(n0, construct_explosion_graph(A, R))) << endl;
}
