#include <bits/stdc++.h>


#include <cstddef>
#include <vector>
#include <algorithm>

using std::size_t;
using std::vector;
using std::__lg;

using namespace std;

namespace fenwicks
{
    template<typename Tp>
    static constexpr inline Tp lsb(Tp x) { return x & (-x); }
}

template<typename T, size_t DIM>
struct dfenwick_tree;

template<typename T>
struct dfenwick_tree<T, 1>
{
    size_t n;
    vector<T> F;
    dfenwick_tree(size_t _n) : n(_n), F(n+1, 0) {}

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
            r += F[p].get_prefix(args...), p -= fenwicks::lsb(p);
        return r;
    }

    template<typename... Args>
    void delta(T v, size_t p, Args... args)
    {
        p++;
        while(p <= n)
            F[p].delta(v, args...), p += fenwicks::lsb(p);
    }
};

int main()
{
    dfenwick_tree<int, 3> T(32u, 32u, 32u);
    T.delta(5, 1, 1, 1);
    T.delta(3, 0, 1, 1);
    T.delta(8, 2, 2, 1);
    cout << T.get_prefix(2, 2, 2);
}
