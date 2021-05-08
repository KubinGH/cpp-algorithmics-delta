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

    nth_element(A.begin(), A.begin() + (n/2), A.end());
    int64_t result = 0;
    for(size_t i = 0; i < n/2; i++)
        result += A[n/2] - A[i];
    for(size_t i = n/2; i < n; i++)
        result += A[i] - A[n/2];

    cout << result << endl;
}
