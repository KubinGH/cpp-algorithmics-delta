#include <bits/stdc++.h>

using namespace std;

const uint MOD = 1e9 + 7;

struct edge { size_t u, v, i; };

constexpr auto nothin = [](size_t, edge) {};

struct dfs
{
    const vector<vector<edge>>& graph;
    vector<bool> vis;

    dfs(const vector<vector<edge>>& _graph) : graph(_graph), vis(graph.size()) {}

    template<typename PreCallback, typename PostCallback>
    void operator() (size_t u, const PreCallback& F1, const PostCallback& F2, edge used = {SIZE_MAX, SIZE_MAX, SIZE_MAX})
    {
        if(vis[u])
            return;
        vis[u] = true;
        F1(u, used);
        for(auto e : graph[u])
            operator() (e.v, F1, F2, e);
        F2(u, used);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n;
    cin >> n;

    vector<tuple<size_t, size_t, size_t>> pred(n);
    for(size_t i = 0; i < n; i++)
    {
        size_t u, v;
        char c; cin >> c;
        if(c == 'T')
            cin >> u, v = u;
        else if(c == 'N')
            cin >> u >> v;
        u--; v--;
        pred[i] = tuple<size_t, size_t, size_t>{u, v, i};
    }

    auto fail = [&]() { cout << "NIE\n0" << endl; exit(0); };

    vector<vector<edge>> graph(n);
    vector<size_t> ini_assigned, assign(n);
    vector<bool> claimed(n);
    for(auto& p : pred)
    {
        size_t u, v, i; tie(u, v, i) = p;
        if(u == v)
        {
            if(claimed[u])
                fail();
            ini_assigned.push_back(u);
            assign[i] = u+1;
            claimed[u] = true;
        }
        else
        {
            graph[u].push_back({u, v, i});
            graph[v].push_back({v, u, i});
        }
    }

    dfs ini_assign_dfs{graph};
    for(auto u : ini_assigned)
    {
        ini_assign_dfs(u,
            [&](size_t v, edge used) {
                if(used.i == SIZE_MAX) return;
                if(claimed[v])
                    fail();
                assign[used.i] = v + 1;
                claimed[v] = true;
            },
            nothin
        );
    }

    uint exponent = 0;
    dfs counter_dfs{graph};
    for(size_t u = 0; u < n; u++)
    {
        if(claimed[u] or counter_dfs.vis[u])
            continue;

        size_t vV = 0, vE = 0;
        counter_dfs(u,
            [&](size_t v, edge) {
                vV++;
                vE += graph[v].size();
            },
            nothin
        ); vE /= 2;
        if(vV != vE)
            fail();
        exponent++;
    }

    if((size_t)count(claimed.begin(), claimed.end(), true) == n)
    {
        cout << "TAK\n";
        for(auto i : assign)
            cout << i << "\n";
        cout << endl;
        return 0;
    }
    else
    {
        uint result = 1;
        while(exponent --> 0)
        {
            result *= 2;
            if(result >= MOD)
                result -= MOD;
        }
        cout << "NIE\n" << result;
    }
}
