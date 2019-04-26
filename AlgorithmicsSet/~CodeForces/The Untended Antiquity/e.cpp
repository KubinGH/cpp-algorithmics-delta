#include <bits/stdc++.h>

using namespace std;

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
            if(p + q < n and s + F[p + q] < v)
                s += F[p + q], p += q;
        return p;
    }
};

template<typename T, size_t DIM>
struct dfenwick_tree;

template<typename T>
struct dfenwick_tree<T, 1>
{
    fenwick_tree<T> F;
    dfenwick_tree(size_t n) : F(n) {}
    T get_prefix(size_t p) const { return F.get_prefix(p); }
    void delta(T v, size_t p) { return F.delta(p, v); }
};

template<typename T, size_t DIM>
struct dfenwick_tree
{
    size_t n;
    vector<dfenwick_tree<T, DIM - 1>> F;
    template<typename... Args>
    dfenwick_tree(size_t _n, Args... args) : n(_n), F(n+1, dfenwick_tree<T, DIM - 1>{args...}) {}

    template<typename... Args>
    T get_prefix(size_t p, Args... args) const
    {
        T r = 0;
        while(p)
            r += F[p].get_prefix(args...), p -= fenwick_tree<T>::lsb(p);
        return r;
    }

    template<typename... Args>
    void delta(T v, size_t p, Args... args)
    {
        p++;
        while(p <= n)
            F[p].delta(v, args...), p += fenwick_tree<T>::lsb(p);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<uint64_t>> D(n, vector<uint64_t>(m));

    dfenwick_tree<uint64_t, 2> T(n + 1, m + 1);

    auto get = [&](size_t r, size_t c) {
        return T.get_prefix(r + 1, c + 1);
    };

    mt19937_64 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

    while(q --> 0)
    {
        size_t t, r1, c1, r2, c2;
        cin >> t >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;

        if(t == 1)
        {
            uint64_t d = gen();
            D[r1][c1] = d;
            T.delta(d, r1, c1);
            T.delta(-d, r2 + 1, c1);
            T.delta(-d, r1, c2 + 1);
            T.delta(d, r2 + 1, c2 + 1);
        }
        else if(t == 2)
        {
            uint64_t d = D[r1][c1];
            D[r1][c1] = 0;
            T.delta(-d, r1, c1);
            T.delta(d, r2 + 1, c1);
            T.delta(d, r1, c2 + 1);
            T.delta(-d, r2 + 1, c2 + 1);
        }
        else if(t == 3)
        {
            auto u = get(r1, c1);
            auto v = get(r2, c2);
            cout << (u == v ? "Yes" : "No") << "\n";
        }
    }
}