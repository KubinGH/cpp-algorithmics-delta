#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;

    static constexpr size_t lsb(size_t x) { return x & -x; }

    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }

    T get_prefix(size_t p)
    {
        T r = T(0);
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }

    T at(size_t p) { return get_prefix(p+1) - get_prefix(p); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    size_t n;
    cin >> n;

    fenwick_tree<int64_t> T(n);

    set<size_t> Z;
    for(size_t i = 0; i < n; i++)
    {
        int64_t a;
        cin >> a;
        T.delta(i, a);
        Z.insert(i);
    }

    vector<pair<int64_t, size_t>> Q(n);
    for(size_t i = 0; i < n; i++)
    {
        cin >> Q[i].first;
        Q[i].second = i;
    }
    sort(Q.begin(), Q.end());

    vector<size_t> R;
    for(auto p : Q)
    {
        int64_t x; size_t i;
        tie(x, i) = p;
        if(T.get_prefix(i + 1) >= x)
        {
            auto it = Z.upper_bound(i);
            vector<set<size_t>::iterator> E;
            while(x)
            {
                --it;
                auto y = min(x, T.at(*it));
                T.delta(*it, -y);
                if(not T.at(*it))
                    E.push_back(it);
                x -= y;
            }
            for(auto pit : E)
                Z.erase(pit);
            R.push_back(i);
        }
    }
    sort(R.begin(), R.end());

    cout << R.size() << "\n";
    for(auto i : R)
        cout << i+1 << " ";
    cout << endl;
}