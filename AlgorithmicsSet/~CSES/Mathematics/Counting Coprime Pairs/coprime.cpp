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

    const size_t m = *max_element(A.begin(), A.end()) + 1;

    vector<int8_t> mu(m); mu[1] = 1;
    for(size_t d = 1; d < m; d++)
        for(size_t x = 2*d; x < m; x += d)
            mu[x] -= mu[d];

    vector<int> div(m), cnt(m);
    for(auto a : A)
        cnt[a]++;

    for(size_t d = 1; d < m; d++)
        for(size_t x = d; x < m; x += d)
            div[d] += cnt[x];

    int64_t result = 0;
    for(size_t d = 1; d < m; d++)
        result += mu[d] * (int64_t) div[d] * (div[d] - 1) / 2;

    cout << result << endl;
}
