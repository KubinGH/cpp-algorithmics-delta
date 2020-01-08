#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n; int64_t k;
    cin >> n >> k;

    vector<int64_t> A(n);
    for(auto& a : A) cin >> a;

    auto f = [&](int64_t x) {
        int64_t r = 0;
        for(auto a : A)
            r += a / x;
        return r;
    };
    auto b = f(k);

    int64_t lo = 1, hi = *max_element(A.begin(), A.end()) + 1;

    while(lo < hi)
    {
        auto mid = (lo + hi) / 2;

        if(f(mid) < b)
            hi = mid;
        else
            lo = mid+1;
    }

    cout << lo - 1;
}
