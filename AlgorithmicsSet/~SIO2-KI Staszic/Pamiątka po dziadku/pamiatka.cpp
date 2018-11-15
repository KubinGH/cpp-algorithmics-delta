#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<int64_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    int64_t best = accumulate(A.begin(), A.end(), 0LL), curr_max = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        curr_max = max(curr_max, 0LL) + A[i];
        best = max(best, curr_max);
    }
    vector<pair<int64_t, uint32_t>> best_prefix_sums;
    best_prefix_sums.reserve(n);
    best_prefix_sums.emplace_back(INT64_MIN, 0);
    int64_t prefix_sum = 0;
    for(uint32_t i = 1; i < n; i++)
    {
        prefix_sum += A[i-1];
        if(best_prefix_sums.back().first < prefix_sum)
            best_prefix_sums.emplace_back(prefix_sum, i);
    }
    int64_t suffix_sum = 0, best_suffix_sum = 0;
    for(uint32_t i = 1; i < n; i++)
    {
        if(best_prefix_sums.back().second + i > n)
            best_prefix_sums.pop_back();
        suffix_sum += A[n-i];
        best_suffix_sum = max(best_suffix_sum, suffix_sum);
        best = max(best, best_prefix_sums.back().first + best_suffix_sum);
    }
    cout << best;
}
