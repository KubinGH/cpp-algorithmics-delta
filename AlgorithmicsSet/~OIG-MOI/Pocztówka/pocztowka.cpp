#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n, m;
    cin >> n >> m;
    vector<uint64_t> P;
    for(uint64_t i = 0; i < n; i++)
    {
        uint64_t h;
        cin >> h;
        if(h >= m)
            P.push_back(i);
    }
    uint64_t r = 0, j = 0;
    if(not P.empty()) for(uint64_t i = 0; i < P.back() + 1; i++)
    {
        if(i > P[j])
            j++;
        r += n - P[j];
    }
    cout << r;
}
