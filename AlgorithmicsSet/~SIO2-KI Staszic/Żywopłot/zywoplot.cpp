#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct fenwick_tree
{
    size_t n; vector<T> F;
    static inline size_t lsb(size_t x) { return x&-x; }
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}
    T get_prefix(size_t p) const
        { T r = 0; while(p) r += F[p], p -= lsb(p); return r; }
    void delta(size_t p, T v)
        { p++; while(p <= n) F[p] += v, p += lsb(p); }

    T get(size_t i, size_t j) const
        { return get_prefix(j+1) - get_prefix(i); }
    T get(size_t p) const { return get(p, p); }
    void set(size_t p, T v) { delta(p, v - get(p)); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<uint32_t> A(n);
    fenwick_tree<uint32_t> F(1<<20);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], F.delta(A[i], 1);
    while(q --> 0)
    {
        string com;
        cin >> com;
        if(com == "pyt")
        {
            uint32_t h; cin >> h;
            cout << F.get(h, F.n-1) << "\n";
        }
        else if(com == "mod")
        {
            uint32_t i, h; cin >> i >> h; i--;
            F.delta(A[i], -1); F.delta(A[i] = h, 1);
        }
    }
}
