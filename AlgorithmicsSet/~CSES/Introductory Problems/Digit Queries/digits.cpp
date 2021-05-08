#include <bits/stdc++.h>

using namespace std;

uint64_t digit_count_sum(uint64_t n, const uint64_t B = 10)
{
    if(n <= 1)
        return 0;
    uint64_t result = 0, p, i;
    for(p = B, i = 1; p <= n; p *= B, i++)
        result += (p - p/B) * i;
    return result + (n - p/B) * i;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t q;
    cin >> q;

    while(q --> 0)
    {
        uint64_t k;
        cin >> k;
        k--;

        uint64_t lo = 0, hi = 1;
        while(digit_count_sum(hi-1) <= k)
            hi *= 2;

        while(lo < hi)
        {
            auto mid = (lo + hi) / 2;
            if(digit_count_sum(mid) > k)
                hi = mid;
            else
                lo = mid+1;
        }

        cout << to_string(lo-1)[k - digit_count_sum(lo-1)] << '\n';
    }
}
