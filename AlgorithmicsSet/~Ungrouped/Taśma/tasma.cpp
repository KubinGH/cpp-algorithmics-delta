#include <bits/stdc++.h>
#define MAX 100000

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t tests;
    scanf("%u", &tests);
    for(uint32_t t = 0; t < tests; t++)
    {
        uint32_t n;
        scanf("%u", &n);
        static uint32_t A[MAX];
        bool all_same = true;
        for(uint32_t i = 0; i < n; i++)
        {
            scanf("%u", A + i);
            if(all_same and A[i] != A[0]) all_same = false;
        }
        if(all_same)
        {
            printf("BRAK\n");
            continue;
        }
        uint32_t dist = 1;
        for(uint32_t i = 0; i < n; i++)
        {

        }
        printf("%u\n", &dist);
    }
}
