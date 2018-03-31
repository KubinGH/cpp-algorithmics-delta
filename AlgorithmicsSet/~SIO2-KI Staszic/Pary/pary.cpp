#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    int32_t s;
    cin >> n >> s;
    unordered_map<int32_t, uint32_t> M;
    M.reserve(2*n);
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t a;
        cin >> a;
        M[a]++;
    }
    uint32_t r = 0;
    for(const pair<int32_t, uint32_t>& p : M)
    {
        int32_t a = p.first; uint32_t b = p.second;
        if(a < s - a and (s % 2 == 1 or a != s / 2) and M.find(s - a) != M.end())
        {
            r += b * M[s - a];
        }
    }
    if(s % 2 == 0)
        r += M[s/2] * (M[s/2] + 1) / 2;
    cout << r;
}
