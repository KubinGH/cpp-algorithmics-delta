#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using os_set = tree<
    T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update
>;

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    fenwick_tree(size_t _n) : n(1 << __lg(2*_n-1)), F(n+1) {}

    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += p & -p;
    }
    T get_prefix(size_t p)
    {
        T r = 0;
        while(p)
            r += F[p], p &= p - 1;
        return r;
    }
};

struct ari
{
    fenwick_tree<int> A;
    fenwick_tree<int64_t> B;
    ari(size_t n) : A(n), B(n) {}
    void delta_a(size_t p, int v) { A.delta(p, v); }
    void delta_b(size_t p, int v) { B.delta(p, v); }
    int64_t get_prefix(size_t p) { return A.get_prefix(p)*(int64_t)p + B.get_prefix(p); }
    int64_t get(size_t l, size_t r) { return get_prefix(r) - get_prefix(l); }
    int64_t get(size_t i) { return get(i, i + 1); }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<size_t> P(n), I(n);
    for(size_t i = 0; i < n; i++)
        cin >> P[i], P[i]--, I[P[i]] = i;

    ari R(n), L(n+1);
    os_set<size_t> E;

    int64_t inv = 0;
    for(size_t k = 1; k <= n; k++)
    {
        auto p = I[k-1];
        inv += (k - 1) - E.order_of_key(p);
        E.insert(p);

        R.delta_a(p, 1); R.delta_b(p, -(int)p);
        L.delta_a(0, 1); L.delta_a(p+1, -1);
        L.delta_b(p+1, p+1);

        int64_t k1 = k/2, k2 = k-k1;
        auto m = *E.find_by_order(k1);

        cout << inv + R.get(0, m) + L.get(m, n) - k1*(k1+1)/2 - k2*(k2+1)/2 << ' ';
    }

    cout << endl;
}
