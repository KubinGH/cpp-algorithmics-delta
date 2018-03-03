#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t n;
    cin >> n;
    uint64_t r = 0;
    for(uint64_t i = 1; i <= floor(sqrt(n)); i++)
    {
        if(n % i == 0 and i != n/i and (n/i - i) % 2 == 0)
            r++;
    }
    cout << r;
}
