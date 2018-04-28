#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t t;
    scanf("%u", &t);
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t n;
        scanf("%u", &n);
        for(uint32_t x = 2*n + 1; ; x += n)
        {
            bool prime = true;
            if(x != 2 and x != 3) for(uint32_t d = 2; d <= floor(sqrt(x)); d++)
            {
                if(x % d == 0)
                {
                    prime = false;
                    break;
                }
            }
            if(not prime)
            {
                printf("%u\n", (x - 1) / n);
                break;
            }
        }
    }
}
