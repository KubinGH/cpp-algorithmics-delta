#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct max_segment_tree
{
    size_t w;
    static constexpr T identity = 0;
    vector<T> values;

    max_segment_tree(size_t n) : w(1 << __lg(2*n - 1)), values(2*w, identity) {}

    void build()
    {
        for(size_t j = w; j --> 1; )
            values[j] = max(values[2*j], values[2*j+1]);
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
            values[p] = max(values[2*p], values[2*p + 1]);
    }

    size_t pref_lower_bound(T v)
    {
        if(values[1] < v)
            return SIZE_MAX;
        size_t p = 1;
        while(p < w)
            p *= 2, p += values[p] < v;
        return p - w;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<int> H(n);
    for(auto& h : H)
        cin >> h;

    max_segment_tree<int> tree(n);
    tree.build(H.begin(), H.end());

    while(m --> 0)
    {
        int r;
        cin >> r;

        auto p = 1 + tree.pref_lower_bound(r);
        cout << p << ' ';
        if(p) p--, tree.set(p, tree.values[tree.w + p] - r);
    }
    cout << endl;
}
