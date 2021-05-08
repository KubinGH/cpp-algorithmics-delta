#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m; int k;
    cin >> n >> m >> k;

    vector<int> A(n), B(m);
    for(auto& a : A)
        cin >> a;
    for(auto& b : B)
        cin >> b;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    size_t result = 0;
    B.push_back(INT_MAX);
    for(size_t i = 0, j = 0; i < n; i++)
    {
        while(A[i]-k > B[j])
            j++;
        if(abs(A[i] - B[j]) <= k)
            result++, j++;
    }

    cout << result << endl;
}
