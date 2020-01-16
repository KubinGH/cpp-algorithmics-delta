#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX / 2 - 0xD;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<pair<size_t, int>>> G(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int d;
        cin >> u >> v >> d; u--; v--;
        G[u].emplace_back(v, d);
    }

    vector<int> D(n);
    vector<size_t> B(n);
    vector<bool> I(n);
    queue<size_t> Q;

    while(q --> 0)
    {
        size_t s, t;
        cin >> s >> t; s--; t--;

        fill(D.begin(), D.end(), +oo); D[s] = 0;
        fill(B.begin(), B.end(), SIZE_MAX);
        fill(I.begin(), I.end(), false);

        Q.push(s); I[s] = true;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop(); I[u] = false;
            for(auto [v, d] : G[u])
            {
                if(D[u] + d < D[v])
                {
                    D[v] = D[u] + d;
                    B[v] = u;
                    if(not I[v]) Q.push(v), I[v] = true;
                }
            }
        }

        if(D[t] != +oo)
        {
            cout << D[t] << ' ';
            vector<size_t> path;
            for(auto u = t; u < n; u = B[u])
                path.push_back(u);
            reverse(path.begin(), path.end());
            cout << path.size() << ' ';
            for(auto v : path)
                cout << v+1 << ' ';
            cout << '\n';
        }
        else
            cout << "NIE\n";

    }
}
