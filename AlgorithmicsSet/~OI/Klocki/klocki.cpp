#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17, MAX_H = 1 << 20;

template<typename T>
constexpr inline T lsb(T x) { return x & (-x); }

template<typename T>
struct fenwick_tree
{
    size_t n;
    T* F;
    fenwick_tree(size_t _n) { n = _n+1; F = new T[n+1]; fill(F, F + (n+1), 0); }
    ~fenwick_tree() { delete[] F; }
    T get_prefix(size_t p) const // Sum in [0, p)
        { T r = 0; for(p++; p; p -= lsb(p)) r += F[p]; return r; }
    void delta(size_t p, T v)
        { for(p += 2; p <= n; p += lsb(p)) F[p] += v; }

    T get(size_t a, size_t b) const // Get on interval [a, b]
        { return get_prefix(b+1) - get_prefix(a); }
    T get(size_t p) const // Get on point [p]
        { return get(p, p); }
    void set(size_t p, T v)
        { return delta(p, v - get(p)); }

    size_t lower_bound(T v)
    {
        T s = 0; size_t p = 0;
        for(size_t i = (32 - __builtin_clz(n)); i --> 0; )
        {
            if(p + (1u << i) < n and s + F[p + (1u << i)] < v)
                s += F[p + (1u << i)], p += 1u << i;
        }
        return p;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    vector<int64_t> H(n);
    int64_t max_h = 0;
    for(uint32_t i = 0; i < n; i++)
        cin >> H[i], max_h = max(max_h, H[i]);
    fenwick_tree<int64_t> F(max_h+1), S(max_h+1);
    for(uint32_t i = 0; i < k-1; i++)
    {
        F.delta(H[i], 1);
        S.delta(H[i], H[i]);
    }
    uint32_t ri = -1u; int64_t rv = INT64_MAX, rm = INT64_MAX;
    for(uint32_t i = k-1; i < n; i++)
    {
        F.delta(H[i], 1);
        S.delta(H[i], H[i]);
        int64_t m = F.lower_bound(k/2+1)-1, v = 0;
        if(m > 0)
            v += F.get(0, m-1) * m - S.get(0, m-1);
        if(m < max_h)
            v += S.get(m+1, max_h) - F.get(m+1, max_h) * m;
        if(v < rv)
        {
            ri = i;
            rv = v;
            rm = m;
        }
        F.delta(H[i+1-k], -1);
        S.delta(H[i+1-k], -H[i+1-k]);
    }
    cout << rv << "\n";
    for(uint32_t i = 0; i < n; i++)
    {
        if(ri+1-k <= i and i <= ri)
            cout << rm << "\n";
        else
            cout << H[i] << "\n";
    }
}
