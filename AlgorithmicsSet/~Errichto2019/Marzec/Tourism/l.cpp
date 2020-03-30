#include <bits/stdc++.h>

using namespace std;

const size_t NAX = 1 << 18, MAX = 1 << 18;

struct low_stuff
{
    bool vis[NAX], stk[NAX];
    struct edge
    {
        size_t u, v;
        size_t nd(size_t w) const { return u == w ? v : u; }
    } edges[MAX];
    vector<size_t> graph[NAX];
    size_t low[NAX], preorder[NAX], watch = 0;
    bool bridge[MAX];

    void add_edge(size_t u, size_t v)
    {
        static size_t i = 0;
        edges[i] = {u, v};
        graph[u].push_back(i);
        graph[v].push_back(i);
        i++;
    }

    void dfs(size_t u, size_t p = 0)
    {
        low[u] = preorder[u] = watch++;
        vis[u] = stk[u] = true;

        for(auto i : graph[u])
        {
            auto v = edges[i].nd(u);

            if(not vis[v])
                dfs(v, u), low[u] = min(low[u], low[v]);
            else if(stk[v] and v != p)
                low[u] = min(low[u], preorder[v]);
        }

        for(auto i : graph[u])
        {
            auto v = edges[i].nd(u);
            if(preorder[u] < low[v])
                bridge[i] = true;
        }

        stk[u] = false;
    }

    bool vic[NAX];
    size_t parent[NAX], color[NAX], k = 1;
    void dfs_color(size_t u, size_t c = 0)
    {
        vic[u] = true;
        color[u] = c;
        for(auto i : graph[u])
        {
            auto v = edges[i].nd(u);
            if(not vic[v])
            {
                size_t cc;
                if(bridge[i]) parent[cc = k++] = c;
                else cc = c;
                dfs_color(v, cc);
            }
        }
    }
} low;


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<int> A(n+1);
    for(size_t u = 1; u <= n; u++)
        cin >> A[u];

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        low.add_edge(u, v);
    }

    size_t s;
    cin >> s;

    low.dfs(s);
    low.dfs_color(s);

    const size_t k = low.k;
    vector<int64_t> W(k);
    vector<int> C(k);
    for(size_t u = 1; u <= n; u++)
    {
        auto c = low.color[u];
        C[c]++; W[c] += A[u];
    }

    vector<vector<size_t>> children(k);
    vector<bool> S(k);
    auto Q = W;

    for(size_t u = k; u --> 0; )
    {
        if(u) children[low.parent[u]].push_back(u);
        if(C[u] > 1)
            S[u] = true;
        int64_t w = 0;
        for(auto v : children[u])
        {
            if(S[v])
                Q[u] += Q[v], S[u] = true;
            else
                w = max(w, W[v]);
        }
        Q[u] += w;
    }

    cout << Q[0] << endl;
}
