#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

int main()
{
    uint32_t n;
    uint64_t k;
    cin >> n >> k;
    static array<uint64_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = i+1; j < n; j++)
            if(((A[i]%k) * (A[j]%k))%k != 0)
                r++;
    cout << r;
}
