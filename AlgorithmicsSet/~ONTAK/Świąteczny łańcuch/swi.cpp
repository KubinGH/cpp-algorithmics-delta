#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const unsigned K = 31, P = (1u << 31) - 1, B = 5e5 + 9;

unsigned mersenne_mod(unsigned n)
{
    return n >= P ? n - P : n;
}
unsigned mersenne_mod(uint64_t n)
{
    n = (n >> K) + (n & P);
    n = (n >> K) + (n & P);
    return __builtin_expect(n != P, true) ? n : 0;
}
struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b)
    {
        return mersenne_mod(a * b);
    }
};

struct fenwick_tree
{
    size_t n;
    vector<unsigned> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}
    static constexpr size_t lsb(size_t x) { return x & -x; }
    void delta(size_t p, unsigned v)
    {
        p++;
        while(p <= n)
            F[p] += v, F[p] = mersenne_mod(F[p]), p += lsb(p);
    }
    unsigned get_prefix(size_t p)
    {
        unsigned r = 0;
        while(p)
            r = mersenne_mod(r + F[p]), p -= lsb(p);
        return r;
    }
    unsigned get(size_t i, size_t j)
    {
        auto r = (int)get_prefix(j) - (int)get_prefix(i);
        return r < 0 ? r + P : r;
    }
    unsigned get(size_t i)
    {
        return get(i, i + 1);
    }
};


struct disjoint_set
{
    size_t n;
    vector<size_t> parent, nrank;
    disjoint_set(size_t _n) : n(_n)
    {
        parent.resize(n); nrank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    void unite(size_t u, size_t v)
    {
        if(nrank[v = find(v)] > nrank[u = find(u)])
            swap(u, v);
        if(u == v)
            return;
        parent[v] = u;
        if(nrank[u] == nrank[v])
            nrank[u]++;
    }
    size_t find(size_t u)
    {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;

    vector<unsigned> B_pow(n + 1), B_pow_i(n + 1);
    B_pow[0] = 1;
    for(size_t i = 1; i <= n; i++)
        B_pow[i] = mersenne_mod((uint64_t) B_pow[i-1] * B);
    for(size_t i = 0; i <= n; i++)
        B_pow_i[i] = power((uint64_t)B_pow[i], P - 2, mod_multiplies{});

    fenwick_tree F(n);
    vector<unsigned> A(n);

    auto set_value = [&](size_t p, unsigned v) {
        A[p] = v;
        F.delta(p, P - F.get(p));
        F.delta(p, mersenne_mod((uint64_t) v * B_pow[n-p-1]));
    };
    auto get_prefix = [&](size_t p) {
        return mersenne_mod((uint64_t)F.get_prefix(p) * B_pow_i[n-p]);
    };
    auto get = [&](size_t i, size_t j) {
        return mersenne_mod(
            (uint64_t)P*P + get_prefix(j) -
            (uint64_t)get_prefix(i)*B_pow[j - i]);
    };

    vector<vector<size_t>> occ(n + 1);
    for(size_t i = 0; i < n; i++)
    {
        set_value(i, i + 1);
        occ[i + 1].push_back(i);
    }

    disjoint_set dset(n+1);
    int p = n;
    auto color_merge = [&](unsigned i, unsigned j) {
        dset.unite(i, j);
        if(dset.parent[j] == i)
            swap(i, j);
        p--;
        for(auto k : occ[i])
            set_value(k, j);
        copy(occ[i].begin(), occ[i].end(), back_inserter(occ[j]));
        occ[i].clear();
    };

    for(size_t i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        size_t x = (a+p)%n, y = (b+(int64_t)p*i)%n, l = (c % (n-max(x, y))) + 1;

        while(true)
        {
            size_t lo = 0, hi = l + 1;
            while(lo < hi)
            {
                auto k = (lo + hi) / 2;

                if(get(x, x + k) != get(y, y + k))
                    hi = k;
                else
                    lo = k+1;
            }
            if(lo == l+1)
                break;
            else
                color_merge(A[x+lo-1], A[y+lo-1]);
        }


        cout << p << '\n';
    }
}
