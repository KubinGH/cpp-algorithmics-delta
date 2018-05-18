#include <bits/stdc++.h>

using namespace std;

uint64_t ipow(uint64_t a, uint64_t b)
{
    uint64_t r = 1;
    while(b)
    {
        if(b % 2)
            r *= a;
        b /= 2;
        a *= a;
    }
    return r;
}

int main()
{
    for(uint64_t k = 3; k <= 20; k++)
    {
        cout << k << ": ";
        uint64_t c = 0;
        for(uint64_t b = 1; ipow(b, k) <= 1e14; b++)
        {
            for(uint64_t a = 1; a <= b; a++)
            {
                c++;
                //cout << ipow(b, k) - ipow(a, k) << endl;
            }
        }
        cout << c << endl;
    }
}
