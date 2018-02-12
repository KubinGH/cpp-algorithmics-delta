#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX_E = 1e6+1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t B[MAX_E];
    uint32_t maxim = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        B[a]++;
        maxim = max(a, maxim);
    }
    uint32_t result = 1;
    for(uint32_t i = maxim + 1; i --> 1;)
    {
        uint32_t b = 0;
        for(uint32_t j = i; j <= maxim and b < 2; j += i)
            b += B[j];
        if(b >= 2)
        {
            result = i;
            break;
        }
    }
    cout << result;
}
