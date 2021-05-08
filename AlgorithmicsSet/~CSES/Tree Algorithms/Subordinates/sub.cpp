#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<size_t>> children(n + 1);
    vector<size_t> parent(n + 1);
    vector<int> sub(n + 1, 1); sub[0] = 0;
    for(size_t i = 2; i <= n; i++)
        cin >> parent[i], children[parent[i]].push_back(i);
    vector<size_t> order;
    function<void(size_t)> dfs = [&](size_t u) {
        for(auto v : children[u])
            dfs(v);
        order.push_back(u);
    }; dfs(1);
    for(auto i : order)
        sub[parent[i]] += sub[i];
    for(size_t i = 1; i <= n; i++)
        cout << sub[i]-1 << ' ';
    cout << endl;
}
