#include <bits/stdc++.h>

using namespace std;

#ifndef KTL_DEBUG_MACROS
#if defined(XHOVA) && !defined(XHOVA_O)
#define KTL_DEBUG_MACROS
#endif
#endif

#define KTL_CDBG_COLOR_INIT    "\033[1;33m"
#define KTL_CDBG_COLOR_DEINIT  "\033[0m"

#define note(x) #x << " = " << (x)
#define short_pos "[" << __LINE__ << "]"
#define long_pos "[<" << __PRETTY_FUNCTION__ << ">::" << __LINE__ << "]"
#ifdef KTL_DEBUG_MACROS
#define debug(...)  cerr << KTL_CDBG_COLOR_INIT << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT
#define debugx(...) cerr << KTL_CDBG_COLOR_INIT << short_pos << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << endl
#define debugX(...) cerr << KTL_CDBG_COLOR_INIT <<  long_pos << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << endl
#else
#define debug(...) (void)0
#define debugx(...) (void)0
#define debugX(...) (void)0
#endif

struct cdbg_t
{
    template<typename T>
    cdbg_t& operator<< (const T& o)
    {
        (void)o;
#ifdef KTL_DEBUG_MACROS
        debug(o);
#endif
        return *this;
    }
    cdbg_t& operator<< (ostream& (*pf)(ostream&))
    {
        (void)pf;
#ifdef KTL_DEBUG_MACROS
        debug(pf);
#endif
        return *this;
    }
} cdbg;

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
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(2*n);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; bool s;
        cin >> u >> v >> s; u--; v--;
        if(s)
        {
            graph[u << 1].push_back(v << 1 | 1);
            graph[v << 1 | 1].push_back(u << 1);
        }
        else
        {
            graph[u << 1].push_back(v << 1);
            graph[v << 1 | 1].push_back(u << 1 | 1);
        }
    }

    auto rscc = kosaraju{graph};
    vector<vector<size_t>> scc; vector<size_t> scc_idx;
    tie(scc, scc_idx) = kosaraju{graph}();
    vector<size_t> scc_size(scc.size());

    for(size_t i = 0; i < scc.size(); i++)
    {
        vector<size_t> vertices;
        for(auto u : scc[i])
            vertices.push_back(u / 2);
        sort(vertices.begin(), vertices.end());
        vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());
        scc_size[i] = vertices.size();
    }

    for(const auto& c : scc)
    {
        cdbg << "[ ";
        for(auto u : c)
            cdbg << u/2+1 << "." << u%2 << "; ";
        cdbg << "]\n";
    }

    for(size_t u = 0; u < n; u++)
        cout << scc_size[scc_idx[u << 1 | 1]] - 1 << "\n";
}
