#include <bits/stdc++.h>
#define MAX 8

using namespace std;

typedef unsigned int uint32_t;

uint32_t gcd(uint32_t a, uint32_t b)
{
    uint32_t t;
    while(b)
    {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

uint32_t pow10(uint32_t k)
{
    uint32_t n = 1;
    for(uint32_t i = 0; i < k; i++)
        n *= 10;
    return n;
}

int main()
{
    static char buffer[MAX+1];
    cin >> buffer;
    uint32_t num = 0;
    uint32_t len = strlen(buffer);
    for(uint32_t i = 0; i < len; i++)
    {
        num += (buffer[i] - '0') * pow10(len-i-1);
    }
    uint32_t den = pow10(len) - 1;
    uint32_t d = gcd(num, den);
    cout << num / d << "/" << den / d;
}
