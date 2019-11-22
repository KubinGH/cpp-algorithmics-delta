#include <bits/stdc++.h>

using namespace std;

int64_t sigma(int64_t n)
{
    return n * (n+1) / 2;
}
int64_t sigma(int64_t a, int64_t b)
{
    return sigma(b) - sigma(a - 1);
}

int64_t sumod(int64_t n)
{
    int64_t r = n * n;
    for(int64_t k = 1, k1; k <= n; k = k1+1)
        r -= (n / k) * sigma(k, k1 = n / (n / k));
    return r;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t z;
    cin >> z;

    while(z --> 0)
    {
        int64_t n;
        cin >> n;
        cout << sumod(n) << '\n';
    }
}
