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
    void delta(T v, size_t p)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }
};

template<typename T>
struct fenwick_tree_2d
{
    size_t h, w;
    vector<fenwick_tree<T>> F;
    fenwick_tree_2d(size_t _h, size_t _w) : h(_h), w(_w), F(h+1, fenwick_tree<T>(w+1)) {}

    T get_prefix(size_t y, size_t x) const
    {
        T r = 0;
        while(y)
            r += F[y].get_prefix(x), y -= fenwick_tree<T>::lsb(y);
        return r;
    }

    void delta(T v, size_t y, size_t x)
    {
        y++;
        while(y <= h)
            F[y].delta(v, x), y += fenwick_tree<T>::lsb(y);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<uint64_t>> D(n, vector<uint64_t>(m));

    fenwick_tree_2d<uint64_t> T(n + 1, m + 1);

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
