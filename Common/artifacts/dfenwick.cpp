#include <bits/stdc++.h>

#pragma KTL include "structures/fenwick.cpp"

using namespace std;

template<typename T>
struct fenwick_tree;

namespace fenwicks
{
    template<typename Tp>
    static constexpr inline Tp lsb(Tp x) { return x & (-x); }
}

template<typename T, size_t DIM>
struct dfenwick_tree;

template<typename T>
struct dfenwick_tree<T, 1> : public fenwick_tree<T> {};

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
