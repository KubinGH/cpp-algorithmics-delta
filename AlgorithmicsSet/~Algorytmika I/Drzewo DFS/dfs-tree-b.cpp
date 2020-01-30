#include <bits/stdc++.h>

using namespace std;

vector<vector<size_t>> graph;
vector<vector<size_t>> ext_i;
vector<uint> one, both;
vector<size_t> result;

void dfs_init(size_t u, size_t p, set<size_t>& curr)
{
    for(auto i : ext_i[u])
        curr.insert(i);
    for(auto v : graph[u]) if(v != p)
    {
        set<size_t> sub;
        dfs_init(v, u, sub);
        if(curr.size() < sub.size())
            swap(curr, sub);
        while(not sub.empty())
        {
            auto x = *sub.begin(); sub.erase(sub.begin());
            if(curr.count(x))
                both[u]++;
            else
                curr.insert(x);
        }
        both[u] += both[v];
    }
    one[u] = curr.size();
}

void dfs(size_t u, size_t p)
{
    bool zero = true;
    for(auto v : graph[u])
        if(one[v])
            zero = false;
    if(zero)
        result.push_back(u);

    for(auto v : graph[u]) if(v != p)
    {

        dfs(v, u);

    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph.resize(n); ext_i.resize(n);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        if(i < n-1)
            graph[u].push_back(v), graph[v].push_back(u);
        else
            ext_i[u].push_back(i), ext_i[v].push_back(i);
    }

    one.resize(n); both.resize(n);
    { set<size_t> c; dfs_init(0, 0, c); }

    result.reserve(n);
    dfs(0, 0);

    sort(result.begin(), result.end());
    cout << result.size() << '\n';
    for(auto u : result)
        cout << u+1 << ' ';
}
