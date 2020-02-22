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
    sort(A.begin(), A.end());

    vector<int64_t> R(n+1);
    for(size_t i = 1; i <= n; i++)
        R[i] = max(R[i-1], A[i-1] - R[i-1]);

    cout << R.back();
}
