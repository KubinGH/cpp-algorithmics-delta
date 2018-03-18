#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> T;
    for(uint32_t i = 0; i < n; i++)
        cin >> T[i];
    static array<uint32_t, MAX> R;
    R[0] = 1;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        R[i+1] = max(R[i+1], R[i]);
        if(i+T[i]+1 < n)
            R[i+T[i]+1] = max(R[i+T[i]+1], R[i] + 1);
    }
    cout << R[n - 1];
}
