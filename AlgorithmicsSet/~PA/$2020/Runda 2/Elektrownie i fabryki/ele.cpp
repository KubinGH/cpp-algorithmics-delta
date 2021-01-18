#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX/3;

template<typename T>
struct max_fenwick_tree
{
    size_t n;
    vector<T> F;

    max_fenwick_tree(size_t m, const T& v) : n(m), F(n+1, v) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    T get_prefix(size_t p)
    {
        int r = F[0];
        while(p)
            r = max(r, F[p]), p -= lsb(p);
        return r;
    }

    void maximize(size_t p, const T& v)
    {
        p++;
        while(p <= n)
            F[p] = max(F[p], v), p += lsb(p);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int64_t s = 0;
    vector<pair<int64_t, size_t>> P = {{0, 0}};
    for(size_t i = 0; i < n; i++)
    {
        int a; cin >> a;
        P.emplace_back(s += a, i+1);
    }

    max_fenwick_tree<int> tree(n+1, -oo);
    sort(P.rbegin(), P.rend());

    for(auto [_, i] : P)
    {
        auto r = i == n ? 0 : tree.get_prefix(n - i) + 1;
        if(i == 0)
        {
            cout << (r >= 0 ? (int)n - r : -1) << '\n';
            break;
        }
        else if(r >= 0)
            tree.maximize(n - i, r);
    }
}
