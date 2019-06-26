#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, k;
    cin >> n >> k;
    vector<pair<int, int>> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i].first >> A[i].second;

    const long double eps = 5e-8;
    long double lo = 0, hi = 1e7 + 1;

    auto process = [&](long double a) {
        vector<pair<long  double, int>> B(n);
        for(size_t i = 0; i < n; i++)
            B[i] = {A[i].first - a*A[i].second, i};
        nth_element(B.begin(), B.end() - k, B.end());
        return B;
    };

    for(size_t t = 0; t < 64; t++)
    {
        long double a = (lo + hi) / 2;
        auto B = process(a);
        long double sum = 0;
        for(size_t i = n-k; i < n; i++)
            sum += B[i].first;
        if(sum < 0)
            hi = a;
        else
            lo = a + eps;
    }

    auto B = process(lo);
    for(size_t i = n-k; i < n; i++)
        cout << B[i].second+1 << " ";
}
