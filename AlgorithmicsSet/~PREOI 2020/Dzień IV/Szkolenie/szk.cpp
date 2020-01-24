#include <algorithm>
#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct disjoint_set
{
    vector<size_t> repr, right;
    vector<bool> touched;
    vector<int> minL, minR, maxL, maxR;

    disjoint_set(size_t n) :
        repr(n), touched(n),
        minL(n, INT_MAX), minR(n, INT_MAX),
        maxL(n, INT_MIN), maxR(n, INT_MIN)
    {
        for(size_t i = 0; i < n; i++)
            repr[i] = i;
        right = repr;
    }

    size_t find(size_t v)
    {
        return v == repr[v] ? v : repr[v] = find(repr[v]);
    }

    bool unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return false;
        repr[v] = u;
        if(touched[v]) touched[u] = true;
        minL[u] = min(minL[u], minL[v]); maxL[u] = max(maxL[u], maxL[v]);
        minR[u] = min(minR[u], minR[v]); maxR[u] = max(maxR[u], maxR[v]);
        right[u] = max(right[u], right[v]);
        return true;
    }
};

using interval = pair<int, int>;

bool intersect(const interval& a, const interval& b)
{
    return a.first <= a.second and b.first <= b.second
       and a.first <= b.second and b.first <= a.second;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<interval> A(n);
    map<int, int> tr;

    for(auto& [l, r] : A)
        cin >> l >> r, r--, tr[l] = tr[r] = 0;

    size_t m = 0;
    for(auto& [k, v] : tr)
        tr[k] = m++;
    for(auto& [l, r] : A)
        l = tr[l], r = tr[r];


    disjoint_set dset(m);

    set<interval> intervals;
    intervals.emplace((1 << 29), (1 << 29));
    intervals.emplace((1 << 29) + 1, (1 << 29) + 1);
    intervals.emplace(-(1 << 29), -(1 << 29));
    intervals.emplace(-(1 << 29) - 1, -(1 << 29) - 1);

    for(auto [l, r] : A)
    {
        bool ok = true;

        auto it = intervals.lower_bound({l, l});
        --it;
        size_t c = 0, last = SIZE_MAX;
        for(size_t t = 0; t < 3; t++, ++it)
            if(intersect(*it, {l, r}))
                c++, last = dset.find(it->first);
        if(c > 1)
            ok = false;
        else if(c == 1)
            ok = intersect({dset.maxL[last], dset.minR[last]}, {l, r});

        if(ok)
        {
            for(int i = l; i < r; i = dset.right[dset.find(i)])
                dset.unite(i, i+1);
            auto v = dset.find(l);

            intervals.erase({dset.minL[v], dset.maxR[v]});
            dset.minL[v] = min(dset.minL[v], l); dset.maxL[v] = max(dset.maxL[v], l);
            dset.minR[v] = min(dset.minR[v], r); dset.maxR[v] = max(dset.maxR[v], r);
            dset.touched[v] = true;
            intervals.insert({dset.minL[v], dset.maxR[v]});

            cout << "TAK\n";
        }
        else
            cout << "NIE\n";
    }

}
