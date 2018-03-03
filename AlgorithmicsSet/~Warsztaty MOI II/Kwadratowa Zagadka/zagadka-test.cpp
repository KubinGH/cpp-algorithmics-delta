#include <bits/stdc++.h>

using namespace std;

int main()
{
    for(uint64_t n = 0; n < (1 << 16); n++)
    {
        uint64_t rb = 0;
        for(uint64_t a = 1; a <= 100*n; a++)
        {
            uint64_t b = floor(sqrt(n + a*a));
            if(b * b == n + a*a)
                rb++;
        }
        cout << rb << " ";
        uint64_t r = 0;
        for(uint64_t i = 1; i <= floor(sqrt(n)); i++)
        {
            if(n % i == 0 and i != n/i and (n/i - i) % 2 == 0)
                r++;
        }
        cout << r << endl;
        if(r != rb)
            break;
    }
}
