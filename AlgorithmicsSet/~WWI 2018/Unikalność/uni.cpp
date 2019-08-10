#include <bits/stdc++.h>

using namespace std;

struct query { size_t l, r, k, i; };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<size_t> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    vector<size_t> scale(n);
    iota(scale.begin(), scale.end(), 0);
    sort(scale.begin(), scale.end(), [&](size_t i, size_t j) {
        return A[i] < A[j];
    });
    auto B = A;
    for(size_t i = 0, f = 0; i < n; i++)
    {
        if(i and B[scale[i]] != B[scale[i-1]])
            f++;
        A[scale[i]] = f;
    }

    size_t q;
    cin >> q;

    vector<query> queries(q);
    for(size_t i = 0; i < q; i++)
    {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
        queries[i].i = i;
        queries[i].l--;
    }

    size_t block_e = __lg(2*(size_t)(n / sqrt(q))-1);

    sort(queries.begin(), queries.end(), [&](const query& lhs, const query& rhs) {
        if((lhs.l >> block_e) == (rhs.l >> block_e))
            return ((lhs.l >> block_e) & 1) ? lhs.r < rhs.r : lhs.r > rhs.r;
        else
            return lhs.l < rhs.l;
    });

    vector<size_t> counter(n), of_count(n + 1);
    auto push = [&](size_t i) {
        of_count[counter[A[i]]]--;
        of_count[++counter[A[i]]]++;
    };
    auto pop = [&](size_t i) {
        of_count[counter[A[i]]]--;
        of_count[--counter[A[i]]]++;
    };

    vector<size_t> answer(q);
    size_t l = 0, r = 0;
    of_count[0] = n;
    for(auto query : queries)
    {
        while(r < query.r)
            push(r++);
        while(l > query.l)
            push(--l);
        while(r > query.r)
            pop(--r);
        while(l < query.l)
            pop(l++);
        answer[query.i] = of_count[query.k];
    }

    for(auto a : answer)
        cout << a << '\n';
}
