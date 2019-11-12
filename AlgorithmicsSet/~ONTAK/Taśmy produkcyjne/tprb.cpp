#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<map<size_t, size_t>> dash(n+1);

    vector<bool> disabled(m+1);
    vector<pair<size_t, size_t>> mach(m+1);
    for(size_t i = 1; i <= m; i++)
    {
        cin >> mach[i].first >> mach[i].second;
        size_t u, v;
        tie(u, v) = mach[i];

        dash[u][i] = v;
        dash[v][i] = u;
    }
    for(size_t k = 1; k <= n; k++)
        dash[k][0] = k, dash[k][m+1] = k;

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
        }
        else if(com == 'Q')
        {
            size_t k;
            cin >> k; k = 1 + (k+last)%n;

            size_t i = 0;
            while(i <= m)
                tie(i, k) = after(k, i);

            cout << (last = k) << '\n';
        }
    }
}