#include <bits/stdc++.h>

// -*- ktl/structures/fenwick.cpp -*-

#include <cstddef>
#include <vector>
#include <algorithm>

using std::size_t;
using std::vector;
using std::__lg;

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1, 0) {}

    static constexpr inline size_t lsb(size_t x) { return x & -x; }
    T get_prefix(size_t p) const
    {
        T r = 0;
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }
    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }

    T get(size_t a, size_t b) const
        { return get_prefix(b+1) - get_prefix(a); }
    T get(size_t p) const
        { return get(p, p); }
    void set(size_t p, T v)
        { return delta(p, v - get(p)); }

    size_t lower_bound(T v)
    {
        T s = 0; size_t p = 0;
        for(size_t i = __lg(n)+1, q = (1u << __lg(n)); i --> 0; q /= 2)
            if(p + q <= n and s + F[p + q] < v)
                s += F[p + q], p += q;
        return p;
    }
};

// -$- ktl/structures/fenwick.cpp -$-


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
