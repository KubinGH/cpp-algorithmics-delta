#include <bits/stdc++.h>

using namespace std;

const int64_t oo = INT64_MAX / 3 + 0xD;

template<typename T, typename Monoid, typename Tl, typename LMonoid, typename Pull>
struct lazy_segment_tree
{
    size_t w;
    vector<T> values;
    const T identity;
    Monoid f;
    vector<Tl> lazy;
    const Tl lazy_identity;
    LMonoid g;
    Pull p;

    lazy_segment_tree(size_t n, T id, Monoid _f, Tl lid, LMonoid _g, Pull _p) :
        w(1 << __lg(2*n - 1)), values(2*w, id), identity(id), f(_f),
        lazy(2*w, lid), lazy_identity(lid), g(_g), p(_p) {}

    void pull(size_t i, size_t l, size_t r)
    {
        if(lazy[i] != lazy_identity)
        {
            p(i, l, r, values, lazy);
            if(l < r) for(auto j : {2*i, 2*i+1})
                lazy[j] = g(lazy[j], lazy[i]);
            lazy[i] = lazy_identity;
        }
    }

    T get(size_t i, size_t nodeL, size_t nodeR, size_t queryL, size_t queryR, Tl x)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < queryL or queryR < nodeL)
            return identity;
        if(queryL <= nodeL and nodeR <= queryR)
        {
            lazy[i] = g(lazy[i], x);
            pull(i, nodeL, nodeR);
            return values[i];
        }
        auto nodeM = (nodeL + nodeR) / 2;
        auto r = f(
            get(2*i+0, nodeL, nodeM+0, queryL, queryR, x),
            get(2*i+1, nodeM+1, nodeR, queryL, queryR, x)
        );
        if(x != lazy_identity)
            values[i] = f(values[2*i], values[2*i+1]);
        return r;
    }

    T modify(size_t l, size_t r, Tl x) { return get(1, 0, w - 1, l, r, x); }
    T get(size_t l, size_t r) { return modify(l, r, lazy_identity); }
};

template<typename T, typename Monoid, typename Tl, typename LMonoid, typename Pull>
lazy_segment_tree(size_t, T, Monoid, Tl, LMonoid, Pull) -> lazy_segment_tree<T, Monoid, Tl, LMonoid, Pull>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    constexpr pair<int64_t, int64_t> lazy_identity {0, -0xD};
    auto lazymerge = [lazy_identity](pair<int64_t, int64_t> a, pair<int64_t, int64_t> b) {
        if(b.second == lazy_identity.second)
            return pair<int64_t, int64_t> {a.first + b.first, a.second};
        else
            return b;
    };
    auto lazypull = [lazy_identity](size_t i, size_t l, size_t r, vector<int64_t>& values, vector<pair<int64_t, int64_t>>& lazy) {
        if(lazy[i].second != lazy_identity.second)
            values[i] = lazy[i].second * int64_t(r - l + 1);
        values[i] += lazy[i].first * int64_t(r - l + 1);
    };
    lazy_segment_tree tree(
        n, (int64_t)0, plus<int64_t>{}, lazy_identity, lazymerge, lazypull
    );

    for(size_t i = 0; i < n; i++)
        cin >> tree.values[tree.w + i];
    for(size_t i = tree.w; i --> 1; )
        tree.values[i] = tree.values[2*i] + tree.values[2*i + 1];

    while(q --> 0)
    {
        char t;
        cin >> t;
        if(t == '1')
        {
            size_t l, r; int x;
            cin >> l >> r >> x; l--; r--;
            tree.modify(l, r, {x, lazy_identity.second});
        }
        else if(t == '2')
        {
            size_t l, r; int x;
            cin >> l >> r >> x; l--; r--;
            tree.modify(l, r, {0, x});
        }
        else if(t == '3')
        {
            size_t l, r;
            cin >> l >> r; l--; r--;
            cout << tree.get(l, r) << '\n';
        }
    }
}
