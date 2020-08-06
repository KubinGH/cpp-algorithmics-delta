#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using broken_os_multiset = tree<
    T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update
>;

struct fenwick_tree
{
    int n;
    vector<broken_os_multiset<int>> F;
    fenwick_tree(int m) : n(m), F(n+1) {}

    int get_prefix(int x, int y) const
    {
        int r = 0;
        x = min(x, n);
        while(x > 0)
            r += F[x].order_of_key(y+1), x &= x - 1;
        return r;
    }

    void delta(int x, int y)
    {
        while(x <= n)
            F[x].insert(y), x += x & -x;
    }

    int get(int x1, int y1, int x2, int y2) const
    {
        return get_prefix(x2, y2)   + get_prefix(x1-1, y1-1)
             - get_prefix(x2, y1-1) - get_prefix(x1-1, y2);
    }
};

pair<int, int> f(int x, int y)
{
    return {x+y, x-y};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t q;
    cin >> q;

    fenwick_tree F(400000+0xD);
    while(q --> 0)
    {
        int t, x, y;
        cin >> t >> x >> y;
        tie(x, y) = f(x, y);

        if(t == 1)
            F.delta(x, y);
        else if(t == 2)
        {
            int lo = 0, hi = 400000+0xD;
            while(lo < hi)
            {
                int d = (lo + hi) / 2;
                if(F.get(x-d, y-d, x+d, y+d))
                    hi = d;
                else
                    lo = d+1;
            }
            cout << lo << '\n';
        }
    }
}
