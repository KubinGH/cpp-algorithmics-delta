#include <bits/stdc++.h>

using namespace std;

struct edge { size_t v; uint64_t w; };

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;

    vector<vector<edge>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; uint64_t w;
        cin >> u >> v >> w; u--; v--;
        graph[u].push_back({v, w});
    }

    min_priority_queue<tuple<uint64_t, size_t, size_t>> Q;
    map<pair<size_t, size_t>, uint64_t> D;

    auto put_me_maybe = [&](uint64_t c, size_t u, size_t v) {
        if(not D.count({u, v}) or c < D[{u, v}])
            Q.emplace(D[{u, v}] = c, u, v);
    };

    put_me_maybe(0, n, 0);

    uint64_t result = -1llu;

    while(not Q.empty())
    {
        auto tpl = Q.top(); Q.pop();
        uint64_t c; size_t u, v;
        tie(c, u, v) = tpl;

        if(c > D[{u, v}])
            continue;

        for(auto e : graph[v])
        {
            if(e.v == v + 1)
                put_me_maybe(c + e.w, u, v + 1);
        }
        for(auto e : graph[u < n ? u : 0])
        {
            if(v == n - 1 and e.v == n - 1)
                result = min(result, c + e.w);
            else if(e.v == v + 1)
                put_me_maybe(c + e.w, v, v + 1);
        }
    }

    if(result == -1llu)
        cout << "NIE";
    else
        cout << result;
}
