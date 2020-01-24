#include <bits/stdc++.h>
#include <ktl/util/extio.cpp>

using namespace std;

const int64_t oo = 1000; //INT64_MAX / 3;

int main()
{
    size_t n;
    cin >> n;

    vector<vector<pair<size_t, int64_t>>> graph(n), children = graph;
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v; int64_t s;
        cin >> u >> v >> s; u--; v--;
        graph[u].emplace_back(v, s);
        graph[v].emplace_back(u, s);
    }

    vector<size_t> order;
    function<void(size_t, size_t)> root = [&](size_t u, size_t p) {
        cout << "@ " << u+1 << " (" << p+1 << ")" << endl;
        for(auto [v, s] : graph[u])
            if(v != p)
                children[u].emplace_back(v, s), root(v, u);
        order.push_back(u);
    };

    root(0, 0);

    vector<array<int64_t, 4>> R(n);
    vector<int64_t> A(n); // any proper state (0, 1, 2)
    const size_t None = 0, Butterfly = 1, StickTop = 2, StickMid = 3;

    for(size_t u : order)
    {
        for(auto [v, s] : children[u])
            R[u][None] += A[v];

        R[u][Butterfly] = -oo;
        for(auto [w1, s] : children[u])
          for(auto [w2, z] : children[u])
            if(w1 != w2)
        {
            auto c = s + z + A[w1] + A[w2];
            for(auto [v, _] : children[u])
                if(v != w1 and v != w2)
                    c += A[v];
            R[u][Butterfly] = max(R[u][Butterfly], c);
        }

        R[u][StickTop] = -oo;
        for(auto [w, s] : children[u])
        {
            auto c = s + R[w][StickMid];
            for(auto [v, _] : children[u])
                if(v != w)
                    c += A[v];
            R[u][StickTop] = max(R[u][StickTop], c);
        }

        R[u][StickMid] = -oo;
        for(auto [w, s] : children[u])
        {
            auto c = s + R[w][None];
            for(auto [v, _] : children[u])
                if(v != w)
                    c += A[v];
            R[u][StickMid] = max(R[u][StickMid], c);
        }

        cout << u+1 << " -> " << R[u] << endl;

        A[u] = max({R[u][0], R[u][1], R[u][2]});
    }

    cout << A[0];
}
