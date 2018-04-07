#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 10000, MAX_A = 1500;

int main()
{
    uint32_t t;
    scanf("%u", &t);
    static uint32_t C[MAX_A+1];
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t n;
        scanf("%u", &n);
        fill(C, C + MAX_A + 1, 0);
        for(uint32_t i = 0; i < n; i++)
        {
            uint32_t a;
            scanf("%u", &a);
            C[a]++;
        }
        bool ok = true;
        ok = C[0] % 2 == 0;
        C[1] += C[0] / 2;
        for(uint32_t a = 1; ok and a <= MAX_A; a++)
        {
            if(C[a] % 2 == 1 and C[a-1] <= 1)
                ok = false;
            else
                C[a+1] += C[a] / 2;
        }
        if(ok)
            printf("TAK\n");
        else
            printf("NIE\n");
    }
}
