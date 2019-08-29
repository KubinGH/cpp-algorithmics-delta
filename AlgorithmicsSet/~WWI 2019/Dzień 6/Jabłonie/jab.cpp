#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree
{
    size_t n;
    vector<int> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1, 0) {}

    static constexpr inline size_t lsb(size_t x) { return x & -x; }
    int get_prefix(size_t p) const
    {
        int r = 0;
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }
    void delta(size_t p, int v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }
    int get(size_t a, size_t b) const
        { return get_prefix(b+1) - get_prefix(a); }
    int get(size_t p) const
        { return get(p, p); }
    void set(size_t p, int v)
        { return delta(p, v - get(p)); }

    size_t lower_bound(int v)
    {
        int s = 0; size_t p = 0;
        for(size_t i = __lg(n)+1, q = (1u << __lg(n)); i --> 0; q /= 2)
            if(p + q <= n and s + F[p + q] < v)
                s += F[p + q], p += q;
        return p;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, q;
    cin >> n >> q;

    vector<int> H(n);
    for(size_t i = 0; i < n; i++)
        cin >> H[i];
    sort(H.begin(), H.end());

    fenwick_tree F(n);
    for(size_t i = 0; i < n; i++)
        F.delta(i, H[i] - (i ? H[i-1] : 0));

    while(q --> 0)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "podlej")
        {
            size_t k;
            cin >> k;

            int finish = F.get_prefix(k);
            size_t first_occ = F.lower_bound(finish), last_occ = F.lower_bound(finish + 1);
            size_t extra = k - first_occ;

            F.delta(0, 1);
            F.delta(k - extra, -1);
            F.delta(last_occ - extra, 1);
            F.delta(last_occ, -1);
        }
        else if(cmd == "zbieraj")
        {
            int a, b;
            cin >> a >> b;
            cout << F.lower_bound(b+1) - F.lower_bound(a) << '\n';
        }
    }
}
