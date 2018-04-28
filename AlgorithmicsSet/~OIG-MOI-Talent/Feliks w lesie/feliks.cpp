#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t a, b;
    scanf("%u %u", &a, &b);
    if(a > b) swap(a, b);
    printf("%u", a + b - 1);
}
