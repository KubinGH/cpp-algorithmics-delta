#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct segment_tree
{
    size_t w;
    vector<T> values;
    function<T(T, T)> F;
    T neutral;
    template<typename It>
    segment_tree(It first, It last, function<T(T, T)> f, T e) : F(f), neutral(e)
    {
        const size_t n = distance(first, last);
        w = 1 << __lg(2*n-1);
        values.resize(2 * w, neutral);
        copy(first, last, values.begin() + w);
        for(size_t i = w; i --> 1; )
            values[i] = F(values[2*i], values[2*i+1]);
    }

    const T& leaf(size_t p) const { return values[w + p]; }

    void set(size_t p, T v)
    {
        for(values[p += w] = v, p /= 2; p; p /= 2)
            values[p] = F(values[2*p], values[2*p+1]);
    }
    T get(size_t l, size_t r)
    {
        T result = neutral;
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) result = F(result, values[l++]);
            if(r % 2) result = F(result, values[--r]);
        }
        return result;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int> A(n);
    for(auto& a : A) cin >> a;

    segment_tree<int64_t> T(A.begin(), A.end(), [](int64_t a, int64_t b) { return max(a, b); }, INT64_MIN);

    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == '+')
        {
            size_t v; int64_t x;
            cin >> v >> x; v--;
            T.set(v, T.leaf(v) + x);
        }
        else if(c == '?')
        {
            size_t l, r;
            cin >> l >> r; l--;
            cout << T.get(l, r) << '\n';
        }
    }
}
