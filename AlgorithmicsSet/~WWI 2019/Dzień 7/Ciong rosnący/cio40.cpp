#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree
{
    size_t n;
    vector<uint> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    uint get_prefix(size_t p)
    {
        uint r = 0;
        while(p)
            r = max(r, F[p]), p -= lsb(p);
        return r;
    }

    void delta(size_t p, uint v)
    {
        p++;
        while(p <= n)
            F[p] = max(F[p], v), p += lsb(p);
    }
};

struct dynamic_lis
{
    fenwick_tree F;

    dynamic_lis(size_t n) : F(n) {}

    uint end_with(uint x)
    {
        return F.get_prefix(x + 1);
    }
    uint max()
    {
        return F.get_prefix(F.n);
    }
    void push_back(uint x)
    {
        return F.delta(x, end_with(x) + 1);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint> a(n);
    for(size_t i = 0; i < n; i++)
        cin >> a[i], a[i]--;

    auto result_prefix = [&]() {
        dynamic_lis LL(n);
        vector<dynamic_lis> L;
        vector<uint> result(n);
        for(size_t i = 0; i < n; i++)
        {
            for(size_t j = 0; j < i; j++)
                if(L[j].end_with(a[i]) < LL.end_with(a[i]))
                    result[i]++;
            L.emplace_back(LL);
            LL.push_back(a[i]);
            for(size_t j = 0; j < i; j++)
                L[j].push_back(a[i]);
        }
        return result;
    };

    auto r1 = result_prefix();
    reverse(a.begin(), a.end());
    for(size_t i = 0; i < n; i++)
        a[i] = (n-1) - a[i];
    auto r2 = result_prefix();
    reverse(r2.begin(), r2.end());

    for(size_t i = 0; i < n; i++)
        cout << r1[i] + r2[i] << " ";
    cout << endl;
}
