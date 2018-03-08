#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

const uint64_t LIM = 1000000007;

int main()
{
    uint32_t t;
    cin >> t;
    for(uint32_t i = 0; i < t; i++)
    {
        uint64_t k, n;
        cin >> k >> n;
        cout << ((((n - k) * k) % LIM) * (n + 1) + 1) % LIM << endl;
    }
}
