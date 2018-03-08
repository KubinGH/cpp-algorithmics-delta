#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n;
    cin >> n;
    uint32_t r = 0;
    for(uint32_t a = 1; a <= n; a++)
    {
        for(uint32_t b = a + 1; b <= n; b++)
        {
            uint32_t c = a ^ b;
            if(b < c and c < a + b and c <= n)
            {
                r++;
            }
        }
    }
    cout << r;
}
