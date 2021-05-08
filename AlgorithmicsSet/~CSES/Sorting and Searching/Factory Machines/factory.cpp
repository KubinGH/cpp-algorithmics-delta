#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int k;
    cin >> n >> k;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    auto f = [&](int64_t t) {
        int64_t sum = 0;
        for(size_t i = 0; i < n and sum < k; i++)
            sum += t / A[i];
        return sum >= k;
    };

    int64_t lo = 0, hi = 1e18 + 0xD;
    while(lo < hi)
    {
        auto mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    cout << lo << endl;
}
