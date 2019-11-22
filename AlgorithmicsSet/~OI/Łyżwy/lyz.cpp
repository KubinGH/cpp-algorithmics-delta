#include <bits/stdc++.h>

// -*- ktl/structures/segment_tree.cpp -*-

#include <algorithm>
#include <vector>
#include <cstddef>
#include <ext/functional>

using std::vector;
using std::size_t;
using std::__lg;
using __gnu_cxx::identity_element;

template<typename T, typename ChildrenOp>
struct segment_tree
{
    vector<T> values;
    size_t w;
    ChildrenOp F;
    segment_tree(size_t n, ChildrenOp f = {}) : F(f)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w, identity_element(F));
    }
    template<typename Iterator>
    segment_tree(Iterator first, Iterator last, ChildrenOp f = {}) : segment_tree(distance(first, last), f)
    {
        copy(first, last, values.begin() + w);
        for(size_t i = w; i --> 1; )
            values[i] = F(values[2*i], values[2*i+1]);
    }
    void set(size_t i, T value)
    {
        i += w;
        values[i] = value;
        while(i > 1)
            i /= 2, values[i] = F(values[2*i], values[2*i+1]);
    }
    T get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        if(nodeR < getL or nodeL > getR)
            return identity_element(F);
        else if(getL <= nodeL and nodeR <= getR)
            return values[i];
        else
        {
            return F(get(2*i, nodeL, (nodeL+nodeR)/2, getL, getR),
                     get(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR));
        }
    }
    T get(size_t getL, size_t getR)
    {
        return get(1, 0, w - 1, getL, getR);
    }
    T get() const { return values[1]; }
};


using namespace std;

struct msp_state
{
    int64_t sum, pref, suff, best;
    msp_state(int64_t v)
    {
        sum = v;
        if(v < 0) v = 0;
        suff = pref = best = v;
    }
    msp_state(int64_t _sum, int64_t _pref, int64_t _suff, int64_t _best)
        : sum(_sum), pref(_pref), suff(_suff), best(_best) {}

    friend msp_state operator+ (const msp_state& L, const msp_state& R)
    {
        return {
            L.sum + R.sum,
            max(L.pref, L.sum + R.pref),
            max(R.suff, R.sum + L.suff),
            max({L.best, R.best, L.suff + R.pref})
        };
    }
};

using msp_rtree = segment_tree<msp_state, plus<msp_state>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n, m; int64_t k, d;
    cin >> n >> m >> k >> d;

    vector<msp_state> rep(n, msp_state(-k));
    msp_rtree T(rep.begin(), rep.end());

    while(m --> 0)
    {
        size_t r;
        int64_t x;
        cin >> r >> x; r--;

        T.set(r, msp_state(T.values[T.w + r].sum + x));

        cout << (T.values[1].best > d*k ? "NIE" : "TAK") << '\n';
    }
}
