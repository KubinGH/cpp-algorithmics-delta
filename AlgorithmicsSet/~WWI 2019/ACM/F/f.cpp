#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<unordered_set<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    set<pair<size_t, size_t>> order;

    for(size_t u = 0; u < n; u++)
        order.emplace(graph[u].size(), u);

    while(true)
    {
        auto it = order.lower_bound({2, 0});
        if(it == order.end() or it->first != 2)
            break;

        size_t u = it->second;
        order.erase(it);

        size_t a = *graph[u].begin(), b = *++graph[u].begin();

        order.erase({graph[a].size(), a});
        order.erase({graph[b].size(), b});

        graph[a].erase(u);
        graph[u].erase(a);
        graph[b].erase(u);
        graph[u].erase(b);

        graph[a].insert(b);
        graph[b].insert(a);

        order.emplace(graph[a].size(), a);
        order.emplace(graph[b].size(), b);
    }

    size_t deg1 = 0;
    bool fail = false;
    for(size_t i = 0; i < n; i++)
    {
        if(graph[i].size() == 1)
            deg1++;
        if(graph[i].size() > 1)
            fail = true;
    }
    if(deg1 > 2)
        fail = true;

    if(fail)
        cout << "NIE";
    else
        cout << "TAK";
}
