#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 26;

uint32_t k;
static array<uint64_t, MAX> P;
uint64_t f(uint32_t i, uint64_t n)
{
    if(P[i] > n)
        return 1;
    else if(P[i+1] > n or i == k - 1)
        return f(i, n / P[i]) * P[i];
    else
        return max(f(i, n / P[i]) * P[i], f(i+1, n));
}

int main()
{
    uint64_t n;
    cin >> k >> n;
    for(uint32_t i = 0; i < k; i++)
        cin >> P[i];
    cout << f(0, n);
}
