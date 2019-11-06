#include <bits/stdc++.h>
#include <ktl/structures/fenwick.cpp>

using namespace std;

const size_t NAX = 1 << 18;

struct query { size_t l, r; int v; };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;

    vector<int> drop(n);
    for(int& a : drop) cin >> a;

    vector<query> Q(m);
    vector<vector<size_t>> begins(n), ends(n+1);
    for(size_t i = 0; i < m; i++)
    {
        cin >> Q[i].l >> Q[i].r >> Q[i].v;
        Q[i].l--;
        begins[Q[i].l].push_back(i);
        ends[Q[i].r].push_back(i);
    }

    fenwick_tree<int64_t> active(m + 1);

    for(size_t i = 0; i < n; i++)
    {
        for(size_t t : begins[i])
            active.delta(t, Q[t].v);
        for(size_t t : ends[i])
            active.delta(t, -Q[t].v);

        auto k = active.lower_bound(drop[i]) + 1;
        if(k <= m)
            cout << k;
        else
            cout << "NIE";
        cout << '\n';
    }
}
