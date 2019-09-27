#include <bits/stdc++.h>

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

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    array<vector<size_t>, 3> P;
    for(size_t k = 0; k < 3; k++)
    {
        P[k].resize(n);
        for(size_t i = 0; i < n; i++)
            cin >> P[k][i], P[k][i]--;
    }

    auto ab = common2(P[0], P[1]), ac = common2(P[0], P[2]), bc = common2(P[1], P[2]);

    cout << (ab+ac+bc)/2-(int64_t)n*(n-1)/4 << endl;
}
