#include <bits/stdc++.h>

using namespace std;

const uint64_t mod = 1e9 + 7;

int main()
{
    size_t n;
    cin >> n;

    size_t s = n*(n+1) / 2;
    if(s % 2)
    {
        cout << '0' << endl;
        return 0;
    }

    s /= 2;
    vector<uint64_t> wae(s+1);
    wae[0] = 1;
    for(size_t i = 1; i <= n; i++)
        for(size_t a = s+1; a --> i; )
            wae[a] += wae[a-i], wae[a] %= mod;

    cout << wae[s]*((mod+1)/2) % mod << endl;
}
