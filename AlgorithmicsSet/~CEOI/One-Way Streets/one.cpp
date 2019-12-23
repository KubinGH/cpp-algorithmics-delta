#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

struct edge_t
{
    size_t u, v;
    bool bridge = false;
    edge_t(size_t _u, size_t _v) : u(_u), v(_v) {}
    edge_t() : edge_t(0, 0) {}
    size_t nd(size_t w) { return u == w ? v : u; }
};

size_t n, m, p;
vector<size_t> G[MAX];
edge_t E[MAX];
int ori[MAX];
pair<size_t, size_t> R[MAX];

bool vis[MAX], stk[MAX];

void reset_vis()
{
    fill(vis, vis + (n+1), false);
}

static size_t low[MAX], preorder[MAX];
size_t watch = 0;
void dfs_lo(size_t u, size_t last_edge)
{
    low[u] = preorder[u] = ++watch;
    vis[u] = stk[u] = true;
    for(auto i : G[u])
    {
        if(i == last_edge)
            continue;

        auto v = E[i].nd(u);

        if(not vis[v])
        {
            dfs_lo(v, i);
            low[u] = min(low[u], low[v]);
        }
        else if(stk[v])
        {
            low[u] = min(low[u], preorder[v]);
        }

        if(preorder[u] < low[v])
            E[i].bridge = true;
    }

    stk[u] = false;
}

size_t biconn_id[MAX], biconn_cnt = 0;
void dfs_bic(size_t u, size_t color)
{
    if(vis[u]) return;
    vis[u] = true;
    biconn_id[u] = color;
    for(auto i : G[u])
        if(not E[i].bridge)
            dfs_bic(E[i].nd(u), color);
}

edge_t F[MAX];
vector<size_t> H[MAX];

size_t parent_edge[MAX];
int depth[MAX];
vector<size_t> roots;

void dfs_bic_root(size_t u)
{
    if(vis[u]) return;
    vis[u] = true;
    for(auto i : H[u])
    {
        auto v = F[i].nd(u);
        if(not vis[v])
        {
            parent_edge[v] = i;
            dfs_bic_root(v);
        }
    }
}

int tag[MAX];

int dfs_bic_orient(size_t u)
{
    int tag_here = tag[u];
    auto j = parent_edge[u];
    for(auto i : H[u])
    {
        auto v = F[i].nd(u);
        if(v == F[j].nd(u))
            continue;
        tag_here += dfs_bic_orient(v);
    }
    if(tag_here)
    {
        ori[j] = (u == F[j].u ? 1 : -1);
        if(tag_here < 0)
            ori[j] *= -1;
    }
    return tag_here;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> m;

    for(size_t i = 0; i < m; i++)
    {
        cin >> E[i].u >> E[i].v;
        G[E[i].u].push_back(i);
        G[E[i].v].push_back(i);
    }

    reset_vis();
    for(size_t u = 1; u <= n; u++)
        if(not vis[u])
            dfs_lo(u, SIZE_MAX);

    reset_vis();
    for(size_t u = 1; u <= n; u++)
        if(not vis[u])
            dfs_bic(u, biconn_cnt++);

    for(size_t i = 0; i < m; i++)
    {
        F[i] = edge_t(biconn_id[E[i].u], biconn_id[E[i].v]);
        if(F[i].u != F[i].v)
        {
            H[F[i].u].push_back(i);
            H[F[i].v].push_back(i);
        }
    }

    reset_vis();
    for(size_t u = 0; u < biconn_cnt; u++)
        if(not vis[u])
            parent_edge[u] = SIZE_MAX, roots.push_back(u), dfs_bic_root(u);

    cin >> p;
    for(size_t i = 0; i < p; i++)
    {
        cin >> R[i].first >> R[i].second;
        size_t u = biconn_id[R[i].first], v = biconn_id[R[i].second];
        tag[u]++;
        tag[v]--;
    }

    for(auto u : roots)
        dfs_bic_orient(u);

    for(size_t i = 0; i < m; i++)
        cout << "LBR"[ori[i]+1];
    cout << endl;
}
