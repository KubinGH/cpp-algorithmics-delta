#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    ios_base::sync_with_stdio(false);
    uint32_t n;
    cin >> n;
    uint32_t result = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t current;
        cin >> current;
        result += (current - 1) / 10;
    }
    cout << result;
}
