#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    map<uint64_t, uint32_t> C;
    for(uint32_t i = 0; i < n; i++)
    {
        uint64_t a;
        cin >> a;
        C[a]++;
    }
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint64_t a;
        cin >> a;
        cout << C[a] << '\n';
    }
}
