#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;
    vector<size_t> d(n + 1);
    for(size_t i = 1; i <= n; i++)
        cin >> d[i];
    sort(d.begin() + 1, d.end());

    vector<int> K(n + 1, INT_MIN);
    K[0] = 0;
    for(size_t i = 1; i <= n; i++)
    {
        if(i >= d[i] and d[i - d[i] + 1] + 1 >= d[i])
            K[i] = max(K[i], K[i - d[i]] + 1);
        if(i >= d[i] + 1 and d[i - d[i]] == d[i])
            K[i] = max(K[i], K[i - d[i] - 1] + 1);
    }

    cout << max(K[n], -1);
}
