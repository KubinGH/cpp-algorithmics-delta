#include <bits/stdc++.h>

using namespace std;

const size_t K = 18;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    string S;
    cin >> S;
    
    vector<bool> A(n);
    for(size_t i = 0; i < n; i++)
        A[i] = S[i] - '0';

    vector<size_t> cnt[K];
    int diff[K];

    diff[0] = 1;
    for(size_t k = 1; k < K; k++)
        cnt[k].resize(1 << k), diff[k] = 0;

    auto push = [&](size_t k, uint h) {
        if(not cnt[k][h]++)
            diff[k]++;
    };
    auto pop = [&](size_t k, uint h) {
        if(not --cnt[k][h])
            diff[k]--;
    };
    auto get_mask = [&](size_t l, size_t r) {
        uint h = 0;
        for(size_t i = l; i < r; i++)
            h <<= 1, h += A[i];
        return h;
    };
    auto get_answer = [&]() {
        for(size_t k = 1; k < K; k++)
            if(diff[k] < (1 << k))
                return k;
#ifdef XHOVA
        abort();
#endif
        return K;
    };
    auto for_all_passing = [&](size_t p, auto f) {
        for(int k = 1; k < (int)K; k++)
            for(int i = p-k+1; i <= (int)p; i++)
                if(0 <= i and i+k <= (int)n)
                    f((size_t)i, (size_t)k);
    };

    for(size_t k = 1; k < K; k++)
        for(size_t i = 0; i+k <= n; i++)
            push(k, get_mask(i, i+k));

    cout << get_answer() << '\n';
    while(m --> 0)
    {
        size_t p;
        cin >> p; p--;

        for_all_passing(p, [&](size_t i, size_t k) {
            pop(k, get_mask(i, i+k));
        });
        A[p] = not A[p];
        for_all_passing(p, [&](size_t i, size_t k) {
            push(k, get_mask(i, i+k));
        });
        cout << get_answer() << '\n';
    }
}