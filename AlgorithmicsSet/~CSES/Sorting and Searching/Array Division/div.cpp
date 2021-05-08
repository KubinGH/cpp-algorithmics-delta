#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    auto mx = *max_element(A.begin(), A.end());
    int64_t lo = mx, hi = int64_t(n)*mx;
    while(lo < hi)
    {
        auto mid = (lo + hi) / 2;
        size_t l = 1;
        int64_t s = 0;
        for(size_t i = 0; i < n; i++)
        {
            if(s + A[i] > mid)
                s = 0, l++;
            s += A[i];
        }
        if(l <= k)
            hi = mid;
        else
            lo = mid+1;
    }

    cout << lo << endl;
}
