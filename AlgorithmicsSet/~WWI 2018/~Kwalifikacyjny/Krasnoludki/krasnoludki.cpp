#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t amin = 1e6+1, amax = 0;
    for(uint32_t i = 0, a; i < n; i++)
        cin >> a, amin = min(amin, a), amax = max(amax, a);
    cout << amax - amin;
}
