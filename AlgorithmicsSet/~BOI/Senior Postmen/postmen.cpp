#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<size_t, size_t>>> graph(n+1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }

    vector<bool> use(m);
    auto fix = [&](size_t u) {
        while(not graph[u].empty() and use[graph[u].back().second])
            graph[u].pop_back();
    };

    vector<bool> on(n + 1);

    for(size_t s = 0; s < n; s++)
    {
        fix(s);
        if(graph[s].empty())
            continue;

        vector<size_t> tour, stk;
        stk.push_back(s);
        while(not stk.empty())
        {
            auto u = stk.back();
            fix(u);
            if(not graph[u].empty())
            {
                auto [v, i] = graph[u].back();
                stk.push_back(v); use[i] = true;
                graph[u].pop_back();
            }
            else
                tour.push_back(u), stk.pop_back();
        }

        vector<size_t> run;
        for(auto u : tour)
        {
            if(on[u])
            {
                while(on[u])
                {
                    auto v = run.back();
                    cout << v << ' ';
                    on[v] = false;
                    run.pop_back();
                }
                cout << '\n';
            }
            on[u] = true;
            run.push_back(u);
        }
        assert(run.size() <= 1);
    }
}
