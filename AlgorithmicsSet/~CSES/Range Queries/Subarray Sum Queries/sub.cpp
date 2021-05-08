#include <bits/stdc++.h>

using namespace std;

template<typename T, typename Monoid>
struct segment_tree
{
    size_t w;
    const T identity;
    vector<T> values;
    Monoid f;

    segment_tree(size_t n, T id = {}, Monoid _f = {})
        : w(1 << __lg(2*n - 1)), identity(id), values(2*w, id), f(_f) {}

    void build()
    {
        for(size_t j = w; j --> 1; )
            values[j] = f(values[2*j], values[2*j+1]);
    }
    template<typename It>
    void build(It first, It last)
    {
        size_t i = w;
        while(first != last)
            values[i++] = *first++;
        build();
    }

    void set(size_t p, T v)
    {
        values[p += w] = v;
        while(p /= 2)
            values[p] = f(values[2*p], values[2*p + 1]);
    }

    T get(size_t l, size_t r) const
    {
        T a = identity, b = identity;
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) a = f(a, values[l++]);
            if(r % 2) b = f(values[--r], b);
        }
        return f(a, b);
    }
    T get() const { return values[1]; }
};
template<typename T, typename Monoid>
segment_tree(size_t n, T id, Monoid f) -> segment_tree<T, Monoid>;

struct msp_state
{
    int64_t sum, best, left, right;
};
msp_state make_msp() { return {0, 0, 0, 0}; }
msp_state make_msp(int64_t x) { auto y = max(x, (int64_t)0); return {x,y,y,y}; }
msp_state concat(msp_state l, msp_state r)
{
    return {
        l.sum + r.sum, max(max(l.best, r.best), l.right + r.left),
        max(l.left, l.sum + r.left), max(r.right, r.sum + l.right)
    };
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    segment_tree tree(n, make_msp(), [](msp_state a, msp_state b) { return concat(a, b); }); {
        vector<msp_state> ini(n);
        for(size_t i = 0; i < n; i++)
            { int a; cin >> a; ini[i] = make_msp(a); }
        tree.build(ini.begin(), ini.end());
    };

    while(q --> 0)
    {
        size_t p; int x;
        cin >> p >> x; p--;
        tree.set(p, make_msp(x));
        cout << tree.get().best << '\n';
    }
}
