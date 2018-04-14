#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 500000;

int main()
{
    uint32_t n, k;
    scanf("%u %u", &n, &k);
    if(k)
    {
        k %= n;
        if(k == 0) k += n;
    }
    static uint32_t A[MAX], S[MAX];
    for(uint32_t i = 0; i < n; i++)
        scanf("%u", A+i);
    copy(A, A + n, S);
    sort(S, S + n);
    for(uint32_t i = 0; i < n; i++)
        if(A[i] < S[n-k])
            printf("%u ", A[i]);
    for(uint32_t i = n - k; i < n; i++)
        printf("%u ", S[i]);
}
