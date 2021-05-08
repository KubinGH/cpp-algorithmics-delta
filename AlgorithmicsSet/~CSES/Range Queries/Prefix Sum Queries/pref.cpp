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
    vector<T> lazy;
    const Tl lazy_identity;
    LMonoid g;
    Pull p;

    lazy_segment_tree(size_t n, T id, Monoid _f, T lid, LMonoid _g, Pull _p) :
        w(1 << __lg(2*n - 1)), values(2*w, id), identity(id), f(_f),
        lazy(2*w, lid), lazy_identity(lid), g(_g), p(_p) {}

    void pull(size_t i, size_t l, size_t r)
    {
        p(i, l, r, values, lazy);
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

    auto i64max = [](int64_t x, int64_t y) {
        return max(x, y);
    };
    auto addpull = [](size_t i, size_t l, size_t r, vector<int64_t>& values, vector<int64_t>& lazy) {
        if(not lazy[i])
            return;
        values[i] += lazy[i];
        if(l < r) for(auto j : {2*i, 2*i+1})
            lazy[j] += lazy[i];
        lazy[i] = 0;
    };
    lazy_segment_tree tree(n, -oo, i64max, (int64_t)0, plus<int64_t>{}, addpull);
    for(size_t i = 0; i < n; i++)
        tree.values[tree.w + i] = 0;
    for(size_t i = tree.w; i --> 1; )
        tree.values[i] = i64max(tree.values[2*i], tree.values[2*i + 1]);

    vector<int> A(n);
    auto update = [&](size_t p, int v) {
        tree.modify(p, n - 1, v - A[p]); A[p] = v;
    };
    for(size_t i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        update(i, a);
    }

    while(q --> 0)
    {
        char t;
        cin >> t;
        if(t == '1')
        {
            size_t p; int v;
            cin >> p >> v; p--;
            update(p, v);
        }
        else if(t == '2')
        {
            size_t l, r;
            cin >> l >> r; l--; r--;
            cout << max((int64_t)0, tree.get(l, r) - (l ? tree.get(l - 1, l - 1) : 0)) << '\n';
        }
    }
}
