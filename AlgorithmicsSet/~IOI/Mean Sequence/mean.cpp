#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int c = 0, lo = INT_MIN, hi = INT_MAX;
    for(size_t i = 0; i < n; i++)
    {
        int m;
        cin >> m;

        if(i % 2) m = -m;
        c += m;
        if(i % 2) lo = max(lo, c);
        else      hi = min(hi, c);
        c += m;
    }

    cout << max(hi-lo+1, 0) << endl;
}
