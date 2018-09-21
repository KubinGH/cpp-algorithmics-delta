#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t k;
    cin >> k;
    uint32_t hi = 0;
    for(uint32_t p = 0; p < k + 1; p++)
    {
        uint32_t c;
        cin >> c;
        if(hi >= (1u << p) - 1)
            hi += c * (1u << p);
        else
            break;
    }
    cout << hi + 1;
}
