#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>

using namespace std;

struct node_t { size_t a, b; };

int main()
{
    size_t n;
    cin >> n;
    vector<int> B(n), pref_count0(n+1);
    for(size_t i = 0; i < n; i++)
    {
        cin >> B[i];
        pref_count0[i+1] = pref_count0[i] + (1 - B[i]);
    }
    auto count0 = [&](size_t a, size_t b) {
        return pref_count0[b] - pref_count0[a];
    };

    size_t q;
    cin >> q;

    vector<node_t> seg(q);
    for(size_t i = 0; i < q; i++)
    {
        cin >> seg[i].a >> seg[i].b;
        seg[i].a--;
    }
    sort(seg.begin(), seg.end(), [&](const node_t& lhs, const node_t& rhs) {
        return tie(lhs.a, lhs.b) < tie(rhs.a, rhs.b);
    });

    auto can_fill_only_segment = [&](size_t a, size_t b) {
        size_t r = a;
        for(auto s : seg)
            if(a <= s.a and s.a <= r and s.b <= b)
                r = max(r, s.b);
        return r == b;
    };

    vector<int> Q(n+1);

    Q[0] = 0;
    for(size_t i = 1; i <= n; i++)
    {
        Q[i] = Q[i-1] + B[i-1];
        for(size_t j = 0; j < i; j++)
            if(can_fill_only_segment(j, i))
                Q[i] = min(Q[i], Q[j] + count0(j, i));
    }

    cout << Q[n];
}
