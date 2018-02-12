#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 3e5;

uint32_t abs_diff(uint32_t a, uint32_t b)
{
    return a > b ? a - b : b - a;
}

int main()
{
    uint32_t n; uint64_t k;
    cin >> n >> k;
    static array<uint32_t, MAX> P, C, B, I;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> P[i]; P[i]--;
        C[i] = P[i]; B[i] = P[i];
        I[P[i]] = i;
    }
    sort(C.begin(), C.begin() + n);
    do
    {
        uint64_t ik = 0;
        for(uint32_t i = 0; i < n; i++)
            ik += abs_diff(i, I[C[i]]);
        if(ik <= k and lexicographical_compare(C.begin(), C.begin() + n, B.begin(), B.begin() + n))
            B = C;
    } while(next_permutation(C.begin(), C.begin() + n));
    for(uint32_t i = 0; i < n; i++)
        cout << B[i]+1 << " ";
}
