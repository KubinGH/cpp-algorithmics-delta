#include <bits/stdc++.h>

using namespace std;

vector<vector<size_t>> graph, tree;
vector<int> area_delta;
vector<uint> preorder, postorder;
uint watch = 0;
void dfs_root(size_t u, size_t p = SIZE_MAX)
{
    preorder[u] = watch++;
    for(auto v : graph[u])
        if(v != p)
            dfs_root(v, u), tree[u].push_back(v);
    postorder[u] = watch;
}
vector<int> value;
void dfs(size_t u, int s = 0)
{
    value[u] = (s += area_delta[u]);
    for(auto v : tree[u])
        dfs(v, s);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph.resize(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    preorder.resize(n); postorder.resize(n);
    tree.resize(n);

    dfs_root(0);

    area_delta.resize(n);

    for(size_t i = n-1; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        if(preorder[u] < preorder[v])
            swap(u, v);
        area_delta[u]++;
        if(preorder[v] <= preorder[u] and preorder[u] < postorder[v])
        {
            area_delta[0]++;
            auto it = lower_bound(tree[v].begin(), tree[v].end(), u, [&](size_t lhs, size_t rhs) {
                return postorder[lhs] < postorder[rhs];
            });
            area_delta[*it]--;
        }
        else
            area_delta[v]++;
    }

    value.resize(n);

    dfs(0);

    bool a = false;
    for(size_t u = 0; u < n; u++)
      if(value[u] == int(m-n+1))
    {
        if(not a) cout << "TAK\n", a = true;
        cout << u+1 << ' ';
    }
    if(not a) cout << "NIE";

}
