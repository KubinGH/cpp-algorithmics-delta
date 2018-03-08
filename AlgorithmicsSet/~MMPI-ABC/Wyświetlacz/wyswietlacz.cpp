#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
const uint32_t LIM = 1e9 + 9;

uint32_t ncommon(const string& a, const string& b)
{
    return (a[0] == b[0] or a[0] == b[1] or a[0] == b[2]) +
           (a[1] == b[0] or a[1] == b[1] or a[1] == b[2]) +
           (a[2] == b[0] or a[2] == b[1] or a[2] == b[2]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<string, MAX> P;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> P[i];
        sort(P[i].begin(), P[i].end());
    }
    uint32_t result = 1;
    uint32_t i, j;
    for(i = 0, j = n - 1; i < j; i++, j--)
    {
        result *= ncommon(P[i], P[j]);
        result %= LIM;
    }
    if(i == j)
        result *= 3, result %= LIM;
    cout << result;
}
