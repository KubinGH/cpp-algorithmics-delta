#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 200000;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static uint32_t AR[MAX], P2R[MAX], P1R[MAX], PR[MAX];
    uint32_t *A = AR, *P2 = P2R, *P1 = P1R, *P = PR; // allow no-copy swaps
    for(uint32_t i = 0; i < n; i++)
        scanf("%u", A+i), P2[i] = 1;
    for(uint32_t i = 0; i < n - 1; i++)
        P1[i] = 1 + (A[i] == A[i+1]);
    for(uint32_t d = 2; d < n; d++)
    {
        for(uint32_t i = 0; i < n - d; i++)
        {
            if(A[i] == A[i+d])
                P[i] = P2[i+1] + 2;
            else
                P[i] = max(P1[i], P1[i+1]);
        }
        swap(P, P1); swap(P, P2);
    }
    printf("%u", P1[0] & (~1));
}
