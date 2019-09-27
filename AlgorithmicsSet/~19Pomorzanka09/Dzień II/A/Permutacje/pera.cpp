#include <bits/stdc++.h>
#include <ktl/util/extio.cpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using namespace __gnu_pbds;

template<typename T>
using order_statistics_set = tree<
    T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update
>;

using namespace std;

struct fenwick_tree
{
    size_t n;
    vector<int> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    void delta(size_t p, int v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }
    int get_prefix(size_t p)
    {
        int r = 0;
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }
};

int64_t common2(const vector<size_t>& P, const vector<size_t>& Q)
{
    assert(P.size() == Q.size());

    const size_t n = P.size();
    vector<size_t> I(n);

    for(size_t i = 0; i < n; i++)
        I[P[i]] = i;

    fenwick_tree fen(n);
    int64_t result = 0;
    for(size_t i = 0; i < n; i++)
    {
        auto x = I[Q[i]];
        result += fen.get_prefix(x);
        fen.delta(x, 1);
    }

    return result;
}

namespace inner
{
    vector<size_t> pinverse(const vector<size_t>& P)
    {
        vector<size_t> Q(P.size());
        for(size_t i = 0; i < P.size(); i++)
            Q[P[i]] = i;
        return Q;
    }


    struct fenwick_tree_2d
    {
        size_t n;
        vector<order_statistics_set<size_t>> F;

        fenwick_tree_2d(size_t _n) : n(_n), F(n+1) {}

        static constexpr size_t lsb(size_t x) { return x & -x; }

        void push(size_t x, size_t y)
        {
            y++;
            while(y <= n)
                F[y].insert(x), y += lsb(y);
        }

        int get_prefix(size_t x, size_t y)
        {
            int r = 0;
            while(y)
                r += F[y].order_of_key(x), y -= lsb(y);
            return r;
        }
    };

    uint64_t solve(vector<size_t> A, vector<size_t> B, vector<size_t> C)
    {
        const size_t n = A.size();

        auto B1 = pinverse(B), C1 = pinverse(C);

        uint64_t result = 0;

        fenwick_tree_2d T(n);

        for(size_t k = 0; k < n; k++)
        {
            size_t x = A[k], i = B1[x], j = C1[x];
            result += T.get_prefix(i+1, j+1);

            T.push(i+1, j+1);
        }

        return result;
    }
}
int main()
{
    size_t n;
    cin >> n;

    mt19937 gen(time(0));
    map<int, vector<int>> gather;
    for(size_t t = 0; t < 2048; t++)
    {
        array<vector<size_t>, 3> P;
        for(size_t k = 0; k < 3; k++)
        {
            P[k].resize(n);
            iota(P[k].begin(), P[k].end(), 0);
            shuffle(P[k].begin(), P[k].end(), gen);
            //for(size_t i = 0; i < n; i++)
            //    cin >> P[k][i], P[k][i]--;
        }

        auto ab = common2(P[0], P[1]), ac = common2(P[0], P[2]), bc = common2(P[1], P[2]), abc = (int64_t)inner::solve(P[0], P[1], P[2]);
        gather[abc].push_back(ab+ac+bc);
        cout << ab << " " << ac << " " << bc << " -> " << abc << " @" << ab+ac+bc << endl;
    }

    for(auto p : gather)
    {
        auto v = p.second;
        sort(v.begin(), v.end());
        assert(v.front() == v.back());
        cout << p.first << ": " << v[0] << endl;
    }

    auto it = gather.begin();
    auto y1 = it->first, x1 = it->second[0];
    auto b = y1 - x1/2;

    for(auto p : gather)
    {
        auto v = p.second;
        cout << p.first << " " << v[0]/2 + b << endl;
        assert(p.first == v[0]/2 + b);
    }
    cout << "a = 1/2" << endl;
    cout << "b = " << b << endl;

    int bb = n*(n-1)/4;
    cout << "? " << bb << endl;
}
