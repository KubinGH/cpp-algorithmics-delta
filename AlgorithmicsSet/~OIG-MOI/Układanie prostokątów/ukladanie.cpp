#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t n;
    while(true)
    {
        scanf("%u", &n);
        if(n == 0)
            break;
        if(n % 2 == 0)
            printf("T\n");
        else
        {
            bool p = true;
            uint32_t x = n - 2;
            for(uint32_t i = 2; i <= floor(sqrt(x)) and p; i++)
                if(x % i == 0)
                    p = false;
            if(p)
                printf("T\n");
            else
                printf("N\n");
        }
    }
}
