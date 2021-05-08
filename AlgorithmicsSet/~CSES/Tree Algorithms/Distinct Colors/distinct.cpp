#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> value(n + 1);
    for(size_t u = 1; u <= n; u++)
        cin >> value[u];

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> result(n + 1);

    function<void(size_t, size_t, set<int>&)> dfs = [&](size_t u, size_t parent, set<int>& curr) {
        for(auto v : graph[u]) if(v != parent)
        {
            set<int> sub;
            dfs(v, u, sub);
            if(sub.size() > curr.size())
                swap(sub, curr);
            for(auto x : sub)
                curr.insert(x);
        }
        curr.insert(value[u]);
        result[u] = curr.size();
    };

    set<int> tmp;
    dfs(1, 0, tmp);

    for(size_t u = 1; u <= n; u++)
        cout << result[u] << ' ';
    cout << endl;
}
