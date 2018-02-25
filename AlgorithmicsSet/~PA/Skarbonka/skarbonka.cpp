#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    map<uint32_t, uint32_t> M;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t c;
        cin >> c;
        M[c]++;
    }
    uint32_t m = 0;
    while(not M.empty())
    {
        pair<uint32_t, uint32_t> p = *M.begin();
        M.erase(M.begin());
        if(p.second > 1)
            M[p.first+1] += p.second / 2;
        m = max(m, p.first);
    }
    cout << m;
}
