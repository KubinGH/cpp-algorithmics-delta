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
};
template<typename T, typename Monoid>
segment_tree(size_t n, T id, Monoid f) -> segment_tree<T, Monoid>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    segment_tree pref(n, int(2e9), [](int a, int b) { return min(a, b); } ), suff = pref;

    auto update = [&](size_t p, int v) {
        pref.set(p, v - int(p));
        suff.set(p, v + int(p));
    };

    for(size_t i = 0; i < n; i++)
        { int a; cin >> a; update(i, a); }

    while(q --> 0)
    {
        char t;
        cin >> t;

        if(t == '1')
        {
            size_t p; int x;
            cin >> p >> x; p--;
            update(p, x);
        }
        else if(t == '2')
        {
            size_t p;
            cin >> p; p--;
            auto a = pref.get(0, p + 1), b = suff.get(p, n);
            cout << min(a + int(p), b - int(p)) << '\n';
        }
    }
}
