#include <bits/stdc++.h>

using namespace std;

uint64_t dist(uint64_t a, uint64_t b) { return a>b ? a - b : b - a; }

template<typename A, typename Function>
A ternary_search(A lo, A hi, Function& f)
{
    if(lo > hi) return 0;
    if(hi - lo < 4)
    {
        A r = lo;
        for(A i = lo+1; i <= hi; i++)
            if(f(i) < f(r))
                r = i;
        return r;
    }
    A l = (2*lo + hi)/3, r = (lo + 2*hi)/3;
    if(f(l) > f(r))
        return ternary_search(l, hi, f);
    else
        return ternary_search(lo, r, f);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint64_t> A(n), S(n+1);
    for(uint32_t i = 0; i < n; i++) cin >> A[i];
    partial_sum(A.begin(), A.end(), S.begin()+1);
    auto sum = [&S](size_t i, size_t j) { return S[j+1] - S[i]; };
    uint64_t r = -1llu;
    for(uint32_t i = 2; i < n - 2; i++)
    {
        auto cost1 = [&sum, &i](size_t j) { return dist(sum(0, j), sum(j+1, i-1)); };
        auto cost2 = [&sum, &i, &n](size_t j) { return dist(sum(i, j), sum(j+1, n-1)); };
        uint32_t a = ternary_search(0u, i - 2, cost1);
        uint32_t b = ternary_search(i, n - 2, cost2);
        if(cost2(i) < cost2(b)) b = i;
        auto p = minmax({sum(0, a), sum(a+1, i-1), sum(i, b), sum(b+1, n-1)});
        r = min(r, p.second - p.first);
    }
    cout << r;
}
