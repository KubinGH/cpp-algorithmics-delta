#include <bits/stdc++.h>

using namespace std;

vector<vector<size_t>> graph;
vector<int> point_delta, area_delta;
vector<uint> preorder, postorder;
uint watch = 0;
void dfs_root(size_t u, size_t p = SIZE_MAX)
{
    preorder[u] = watch++;
    for(auto v : graph[u])
        if(v != p)
            dfs_root(v, u);
    postorder[u] = watch;
}
vector<int> value;
void dfs(size_t u, size_t p = SIZE_MAX, int s = 0)
{
    s += area_delta[u];
    value[u] = s + point_delta[u];
    for(auto v : graph[u])
        if(v != p)
            dfs(v, u, s);
}

int main()
{
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

    dfs_root(0);

    point_delta.resize(n); area_delta.resize(n);

    for(size_t i = n-1; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        if(preorder[u] < preorder[v])
            swap(u, v);
        area_delta[u]++;
        if(preorder[v] <= preorder[u] and preorder[u] < postorder[v])
            area_delta[0]++, area_delta[v]--, point_delta[v]++, area_delta[u]++;
        else
            area_delta[v]++;
    }

    value.resize(n);

    dfs(0);

            for(size_t i = 0; i < n; i++)
                cout << preorder[i] << ".." << postorder[i] << "/" << area_delta[i] << "." << point_delta[i] << "/" << value[i] << ' ';
            cout << endl;

    bool a = false;
    for(size_t u = 0; u < n; u++)
      if(value[u] == int(m-n+1))
    {
        if(not a) cout << "TAK\n", a = true;
        cout << u+1 << ' ';
    }
    if(not a) cout << "NIE";
}
