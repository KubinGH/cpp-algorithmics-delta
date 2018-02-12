#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 30000;

int main()
{
    ios_base::sync_with_stdio(false);
    uint16_t n;
    cin >> n;
    static array<uint16_t, MAX> L;
    set<uint16_t> S;
    for(uint16_t i = 0; i < n; i++)
    {
        S.insert(i);
        cin >> L[i];
        L[i]--;
    }
    static array<bool, MAX> D;
    uint32_t r = 0;
    while(not S.empty())
    {
        uint16_t c = *S.begin(); S.erase(S.begin());
        D[c] = true;
        while(not D[L[c]])
        {
            c = L[c];
            D[c] = true;
            S.erase(c);
        }
        r += 1;
    }
    cout << r << endl;
}
