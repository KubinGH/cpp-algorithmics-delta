#include <bits/stdc++.h>

using namespace std;

typedef unsigned short int uint16_t;

int16_t absh(int16_t n)
{
    return n >= 0 ? n : -n;
}

int16_t sgn(int16_t n)
{
    return n >= 0 ? 1 : -1;
}

int main()
{
    uint16_t k;
    scanf("%hu", &k);
    for(uint16_t i = 0; i < k; i++)
    {
        int16_t a, b;
        scanf("%hd %hd", &a, &b);
        int16_t g = __gcd(absh(a), absh(b));
        int16_t c = a / g, d = b / g;
        if(absh(c) == 1)
            printf("%hd\n", -d * sgn(c));
        else
            printf("%hd/%hd\n", -d * sgn(c), absh(c));
    }
}
