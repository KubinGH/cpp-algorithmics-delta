#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;

    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    void delta(size_t p, T v)
    {
        for(p++; p <= n; p += p & -p)
            F[p] += v;
    }

    T get_prefix(size_t p) const
    {
        T r = 0;
        for(; p; p &= p - 1)
            r += F[p];
        return r;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    fenwick_tree<int64_t> coef[3] = {{n}, {n}, {n}};
    for(size_t i = 0; i < n; i++)
        { int a; cin >> a; coef[0].delta(i, 2*a); }

    auto get = [&](size_t i) {
        auto a = coef[2].get_prefix(i), b = coef[1].get_prefix(i), c = coef[0].get_prefix(i);
        int64_t x = i;
        return (a*x*x + b*x + c) / 2;
    };

    while(q --> 0)
    {
        char t;
        size_t l, r;
        cin >> t >> l >> r; l--;

        if(t == '1')
        {
            int64_t p = l, a = 1, b = 1 - 2*p, c = p * (p - 1), s = int64_t(r-l)*int64_t(r-l+1);
            coef[2].delta(l, +a); coef[2].delta(r, -a);
            coef[1].delta(l, +b); coef[1].delta(r, -b);
            coef[0].delta(l, +c); coef[0].delta(r, s-c);
        }
        else if(t == '2')
            cout << get(r) - get(l) << '\n';
    }
}
