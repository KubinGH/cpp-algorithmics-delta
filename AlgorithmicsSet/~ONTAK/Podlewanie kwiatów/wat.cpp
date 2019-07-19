#include <bits/stdc++.h>

using namespace std;

const int64_t oo = INT64_MAX / 3;

struct funnel { size_t l, r, h; int w; };

struct min_i64 { int64_t operator() (int64_t a, int64_t b) { return min(a, b); } };
int64_t identity_element(min_i64) { return oo; }

template<typename T, typename ChildrenOp>
struct segment_tree
{
    vector<T> values;
    size_t w;
    ChildrenOp F;
    segment_tree(size_t n, ChildrenOp f = {}) : F(f)
    {
        w = 1 << __lg(2*max(n, (size_t)2)-1);
        values.resize(2*w, identity_element(F));
    }
    void set(size_t i, T value)
    {
        i += w;
        values[i] = value;
        while(i > 1)
            i /= 2, values[i] = F(values[2*i], values[2*i+1]);
    }
    T get(size_t getL, size_t getR)
    {
        if(getL > getR) return identity_element(F);
        T result = identity_element(F);
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) result = F(result, values[getL++]);
            if(getR % 2) result = F(result, values[--getR]);
        }
        return result;
    }
    T get() { return values[1]; }
};
using mytree = segment_tree<int64_t, min_i64>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t m, n;
    cin >> m >> n;

    vector<funnel> F(m);
    vector<size_t> values = {1, n};
    values.reserve(3*m+2);
    for(size_t i = 0; i < m; i++)
    {
        cin >> F[i].l >> F[i].r >> F[i].h >> F[i].w;
        values.push_back(F[i].l);
        values.push_back(F[i].r);
        values.push_back(F[i].h);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    unordered_map<size_t, size_t> remap;
    remap.reserve(values.size() * 4);
    for(size_t i = 0; i < values.size(); i++)
        remap[values[i]] = i;
    for(size_t i = 0; i < m; i++)
        F[i].l = remap[F[i].l], F[i].r = remap[F[i].r], F[i].h = remap[F[i].h];
    n = values.size();

    mytree pref(n), suff(n);
    pref.set(0, 0);
    suff.set(n - 1, 0);

    auto pref_set_maybe = [&](size_t p, int64_t v) {
        if(v < pref.values[p+pref.w])
            pref.set(p, v);
    };
    auto suff_set_maybe = [&](size_t p, int64_t v) {
        if(v < suff.values[p+suff.w])
            suff.set(p, v);
    };

    int64_t result = oo;
    for(size_t i = 0; i < m; i++)
    {
        auto l = F[i].l, r = F[i].r, h = F[i].h; auto w = F[i].w;
        auto candy = pref.get(l, r) + suff.get(l, r) + F[i].w;
        result = min(result, candy);
        pref_set_maybe(h, pref.get(l, r) + w);
        suff_set_maybe(h, suff.get(l, r) + w);
    }
    cout << (result == oo ? -1 : result);
}
