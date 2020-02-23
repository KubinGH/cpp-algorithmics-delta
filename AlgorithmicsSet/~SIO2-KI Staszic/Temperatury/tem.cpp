#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<int> B(n-k+1);
    for(auto& b : B)
        cin >> b;

    vector<int64_t> Z(n), X(k), Y(k);
    for(size_t i = k; i < n; i++)
    {
        Z[i] = Z[i-k] + B[i-k+1] - B[i-k];
        X[i%k] = max(X[i%k], Z[i]);
        Y[i%k] = min(Y[i%k], Z[i]);
    }

    vector<int64_t> A(n);

    int64_t s = B[0];
    for(size_t i = 0; i < k; i++)
        A[i] -= Y[i], s += Y[i];

    for(size_t i = 0; i < k; i++)
        A[i] += s / (int)k;
    s = B[0] - accumulate(A.begin(), A.end(), 0ll);
    if(s < 0)
        for(size_t i = 0; i < k; i++)
            A[i]--, s++;

    int64_t amp = 0;
    for(size_t i = 0; i < k; i++)
        amp = max(amp, X[i] - Y[i]);
    for(size_t i = 0; i < k; i++)
    {
        auto d = min(amp - (X[i]-Y[i]), s);
        A[i] += d; s -= d;
    }
    for(size_t i = 0; i < k; i++)
        if(s and amp == (X[i] - Y[i]))
            A[i]++, s--;

    for(size_t i = k; i < n; i++)
        A[i] = A[i%k] + Z[i];

    auto its = minmax_element(A.begin(), A.end());
    cout << (*its.second - *its.first) << endl;
    for(auto x : A)
        cout << x << ' ';
    cout << endl;
}
