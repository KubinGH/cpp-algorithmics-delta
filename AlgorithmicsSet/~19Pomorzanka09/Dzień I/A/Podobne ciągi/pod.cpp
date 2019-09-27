#include <bits/stdc++.h>
#include <ktl/structures/segment_tree.cpp>

using namespace std;

struct node_t { size_t a, b; };

template<typename T>
struct minf
{
    T operator() (const T& a, const T& b) const { return a<b ? a : b; }
};

template<typename T>
T identity_element(minf<T>) { return (1<<29); }

struct addmut
{
    void operator() (size_t i, size_t nodeL, size_t nodeR, vector<int>& values, vector<int>& mutate)
    {
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        values[i] += mutate[i];
        mutate[i] = 0;
    }
};

int identity_element(addmut) { return 0; }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n;
    cin >> n;
    vector<int> B(n), pref_count0(n+1);
    for(size_t i = 0; i < n; i++)
    {
        cin >> B[i];
        pref_count0[i+1] = pref_count0[i] + (1 - B[i]);
    }

    size_t q;
    cin >> q;

    vector<node_t> seg(q);
    vector<vector<node_t>> seg_of_begin(n+1);

    for(size_t i = 0; i < q; i++)
    {
        cin >> seg[i].a >> seg[i].b; seg[i].a--;
        seg_of_begin[seg[i].a].push_back(seg[i]);
    }

    segment_tree_i<int, minf<int>, int, addmut, plus<int>> T(n+1);
    T.mut(0, n, -(1<<28));

    auto update = [&](size_t p, int v) {
        auto w = T.get(p, p);
        T.mut(p, p, min(v, w) - w);
    };
    update(0, 0);

    for(size_t p = 0; p <= n; p++)
    {
        if(p)
        {
            T.mut(p, n, (1 - B[p-1]));
            update(p, T.get(p-1, p-1) + B[p-1]);
        }

        for(auto s : seg_of_begin[p])
            update(s.b, T.get(p, s.b));
    }

    cout << T.get(n, n);
}
