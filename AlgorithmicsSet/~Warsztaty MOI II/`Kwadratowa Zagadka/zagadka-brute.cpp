#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t n;
    cin >> n;
    uint64_t r = 0;
    for(uint64_t a = 1; a <= n / 2; a++)
    {
        uint64_t b = floor(sqrt(n + a*a));
        if(b * b == n + a*a)
        {
            r++;
        }
    }
    cout << r;
}

