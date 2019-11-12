#include <bits/stdc++.h>

using namespace std;

const int RHO = 128;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<map<size_t, size_t>> dash(n+1);

    vector<bool> disabled(m+1);
    vector<pair<size_t, size_t>> mach(m+1), vertices;
    for(size_t i = 1; i <= m; i++)
    {
        cin >> mach[i].first >> mach[i].second;
        size_t u, v;
        tie(u, v) = mach[i];

        dash[u][i] = v;
        dash[v][i] = u;
        for(auto w : {u, v})
            vertices.emplace_back(i, w);
    }
    for(size_t k = 1; k <= n; k++)
        for(auto i : {(size_t)0, m+1})
            dash[k][i] = k, vertices.emplace_back(i, k);

    auto after = [&](size_t k, size_t i) -> pair<size_t, size_t> {
        if(i > m)
            return make_pair(i, k);
        return *dash[k].upper_bound(i);
    };

    auto before = [&](size_t k, size_t i) -> pair<size_t, size_t> {
        if(i == 0)
            return make_pair(i, k);
        return *--dash[k].lower_bound(i);
    };

    auto hop = [&](size_t k, size_t i, int r) {
        if(r < 0) for(int t = 0; t < -r; t++)
            tie(i, k) = before(k, i);
        else for(int t = 0; t < r; t++)
            tie(i, k) = after(k, i);
        return make_pair(k, i);
    };

    vector<map<size_t, pair<size_t, size_t>>> jump(n+1);
    sort(vertices.rbegin(), vertices.rend());

    for(auto p : vertices)
    {
        size_t i, k;
        tie(i, k) = p;
        jump[k][i] = hop(k, i, RHO);
    }


    size_t q, last = 0;
    cin >> q;
    while(q --> 0)
    {
        char com;
        cin >> com;
        if(com == 'C')
        {
            size_t i;
            cin >> i;

            size_t u, v;
            tie(u, v) = mach[i];

            if(not disabled[i])
                dash[u].erase(i), dash[v].erase(i);
            else
                dash[u][i] = v, dash[v][i] = u;
            disabled[i] = not disabled[i];

            for(auto k : {u, v})
            {
                size_t l, j, f, g;
                tie(l, j) = hop(k, i, -RHO);
                l = dash[l][j];
                tie(f, g) = hop(l, j, RHO);

                for(int t = 0; t < RHO+1; t++)
                {
                    jump[l][j] = {f, g};
                    tie(j, l) = after(l, j);
                    tie(g, f) = after(f, g);
                }
            }
        }
        else if(com == 'Q')
        {
            size_t k;
            cin >> k; k = 1 + (k+last)%n;

            size_t i = 0;
            while(i <= m)
                tie(k, i) = jump[k][i];

            cout << (last = k) << '\n';
        }
    }
}
