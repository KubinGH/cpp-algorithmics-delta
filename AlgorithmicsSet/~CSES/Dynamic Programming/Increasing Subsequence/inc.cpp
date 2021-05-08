#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

template<typename T>
struct max_fenwick_tree
{
    size_t n;
    vector<T> F;

    max_fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    T get_prefix(size_t p) const
    {
        T r = 0;
        while(p)
            r = max(r, F[p]), p &= p - 1;
        return r;
    }
    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] = max(F[p], v), p += p & -p;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    map<int, size_t> remap;
    vector<int> A(n);
    for(auto& a : A)
        cin >> a, remap[a];

    size_t m = 0;
    for(auto& [k, v] : remap)
        v = m++;

    max_fenwick_tree<int> F(m);
    for(auto& a : A)
        a = remap[a], F.delta(a, F.get_prefix(a) + 1);

    cout << F.get_prefix(m) << endl;
}
