#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    unordered_map<int32_t, uint32_t> counter;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t c;
        cin >> c;
        counter[c]++;
    }
    uint32_t q;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        int32_t c;
        cin >> c;
        cout << counter[c] << '\n';
    }
}
