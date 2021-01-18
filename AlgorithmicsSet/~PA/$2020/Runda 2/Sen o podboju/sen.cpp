#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t cases;
    cin >> cases;

    while(cases --> 0)
    {
        size_t n;

        cin >> n;

        vector<int> A(n);
        for(auto& a : A)
            cin >> a;

        vector<vector<pair<size_t, size_t>>> graph(n);
        for(size_t i = 0; i < n - 1; i++)
        {
            size_t u, v;
            cin >> u >> v; u--; v--;
            graph[u].emplace_back(v, i);
            graph[v].emplace_back(u, i);
        }
        vector<int64_t> R(n+1, INT64_MAX);
        for(size_t mask = 0; mask < (1u << (n - 1)); mask++)
        {
            size_t vis = 0;
            function<int(size_t)> fun = [&](size_t u) {
                if(vis >> u & 1)
                    return 0;
                vis |= 1 << u;
                int f = A[u];
                for(auto [v, i] : graph[u])
                    if(not (mask >> i & 1))
                        f += fun(v);
                return f;
            };

            int64_t val = 0;
            for(size_t u = 0; u < n; u++)
            {
                int64_t f = fun(u);
                val += f * f;
            }
            size_t p = __builtin_popcount(mask);
            R[p] = min(R[p], val);
        }

        for(size_t i = 0; i < n; i++)
            cout << R[i] << ' ';
        cout << endl;
    }
}
