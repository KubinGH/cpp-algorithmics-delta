#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint64_t;

int main()
{
    uint64_t n;
    cin >> n;
    uint64_t r = 2 * (n - 1), g = 1;
    bool u = false;
    for(uint64_t i = 2; i <= n; i += g)
    {
        r--;
        if(u) g++, u = false;
        else u = true;
    }
    cout << r;
}
