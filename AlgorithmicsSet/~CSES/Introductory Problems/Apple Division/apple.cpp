#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    int64_t r = INT64_MAX;
    for(size_t mask = 0; mask < (1u << n); mask++)
    {
        int64_t b = 0;
        for(size_t i = 0; i < n; i++)
            b += (mask >> i & 1 ? A[i] : -A[i]);
        r = min(r, abs(b));
    }
    cout << r << endl;
}
