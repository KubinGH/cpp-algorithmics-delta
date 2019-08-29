#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n;
    cin >> n;
    vector<int64_t> a(n);
    for(size_t i = 0; i < n; i++)
        cin >> a[i];

    cout << accumulate(a.begin(), a.end(), 0ll);
}
