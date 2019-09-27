#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>

using namespace std;

struct node_t { size_t a, b; };

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
    auto count0 = [&](size_t a, size_t b) {
        return pref_count0[b] - pref_count0[a];
    };

    size_t q;
    cin >> q;

    vector<node_t> seg(q);
    vector<vector<size_t>> seg_of_end(n+1);
    vector<size_t> ls_begin(n+1);
    for(size_t i = 0; i < q; i++)
    {
        cin >> seg[i].a >> seg[i].b;
        seg[i].a--;
        seg_of_end[seg[i].b].push_back(i);
    }

    vector<int> Q(n+1);
    Q[0] = 0;
    for(size_t p = 1; p <= n; p++)
    {
        for(auto s : seg_of_end[p])
            ls_begin[seg[s].a] = p + 1;

        Q[p] = Q[p-1] + B[p-1];
        for(size_t i = p, min_ok = p; i --> 0; )
            if(ls_begin[i] >= min_ok + 1)
                Q[p] = min(Q[p], Q[i] + count0(i, p)), min_ok = i;
    }

    cout << Q[n];
}
