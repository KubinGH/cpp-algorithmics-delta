#include <bits/stdc++.h>

using namespace std;

uint64_t R0(uint64_t a, uint64_t b)
{
    uint64_t r = 0;
    for(uint64_t i = a; i <= b; i++)
    {
        if(i % 4 == 2)
        r++;
    }
    return r;
}
uint64_t R1(uint64_t a, uint64_t b)
{
    uint64_t r = 0;
    while(a % 4 != 2)
        a++;
    if(b % 4 == 2)
        r++;
    while(b % 4 != 3)
        b--;
    r += (b - a) / 4 + 1;
    return r;
}


int main()
{
    uint64_t a, b;
    cin >> a >> b;
    cout << (b - a < 100 ? R0(a, b) : R1(a, b));
}
