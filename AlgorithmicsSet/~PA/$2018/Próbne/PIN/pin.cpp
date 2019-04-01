#include <bits/stdc++.h>

using namespace std;

vector<uint32_t> divisors(uint32_t n)
{
    vector<uint32_t> result; result.reserve(1<<10);
    for(uint32_t x = 1; x * x <= n; x++)
        if(n % x == 0)
            result.push_back(x);
    uint32_t s = result.size() - (result.back() * result.back() == n);
    for(uint32_t i = s; i --> 0; )
        result.push_back(n / result[i]);
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t r = 0;
    for(uint32_t k : divisors(n))
    {
        if(k < n) for(uint32_t i : divisors(n/k - 1))
        {
            uint32_t a = k, b = i*k, c = n - k - i*k;
            if(a < b and b < c) r++;
        }
    }
    cout << r;
}
