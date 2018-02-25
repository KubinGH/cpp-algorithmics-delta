#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

const size_t MAX = 1000000;

int main()
{
    uint32_t n;
    scanf("%u ", &n);
    static char S[MAX];
    scanf("%s", S);
    static uint64_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        A[i] = (i > 0 ? A[i-1] : 0) + (S[i] == 'a');
    uint64_t r = 0;
    for(uint32_t i = n; i --> 0;)
        if(S[i] == 'b')
            r += A[i];
    printf("%llu", r);
}
