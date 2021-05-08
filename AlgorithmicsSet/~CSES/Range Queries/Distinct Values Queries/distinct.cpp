#include <bits/stdc++.h>

using namespace std;

struct query_t { size_t l, r, i; };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int> A(n);
    unordered_map<int, size_t> remap;
    remap.reserve(4 * n);
    for(auto& a : A)
        cin >> a, remap[a];
    size_t m = 0;
    for(auto& [k, v] : remap)
        v = m++;
    vector<size_t> B(n);
    for(size_t i = 0; i < n; i++)
        B[i] = remap[A[i]];

    vector<query_t> queries(n);
    vector<int> answer(q);
    for(size_t i = 0; i < q; i++)
        cin >> queries[i].l >> queries[i].r, queries[i].l--, queries[i].i = i;

    const size_t k = 512;
    sort(queries.begin(), queries.end(), [&](const auto& lhs, const auto& rhs) {
        if(lhs.l / k == rhs.l / k)
            return lhs.r < rhs.r;
        return lhs.l / k < rhs.l / k;
    });

    int result = 0;
    vector<int> cnt(m);
    auto push = [&](size_t i) {
        result += cnt[B[i]]++ == 0;
    };
    auto pop = [&](size_t i) {
        result -= --cnt[B[i]] == 0;
    };

    size_t L = 0, R = 0;
    for(auto [l, r, i] : queries)
    {
        while(R < r) push(R++);
        while(L > l) push(--L);
        while(R > r) pop(--R);
        while(L < l) pop(L++);
        answer[i] = result;
    }

    for(auto a : answer)
        cout << a << '\n';
}
