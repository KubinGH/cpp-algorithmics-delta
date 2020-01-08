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

    int lo = 1, hi = *max_element(A.begin(), A.end());
    while(lo < hi)
    {
        int mid = (lo + hi) / 2;
        int l = 0;
        for(auto& a : A)
            l += (a - 1) / mid;
        if(l <= k)
            hi = mid;
        else
            lo = mid+1;
    }
    cout << lo;
}
