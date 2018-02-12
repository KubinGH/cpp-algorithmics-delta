#include <bits/stdc++.h>
#define MAX 1000000000
#define MAX_SQRT 500000

using namespace std;

int main()
{
    static array<uint64_t, MAX_SQRT> pow2, pow3, pow4;
    for(uint32_t i = 0; i < MAX_SQRT; i++)
    {
        pow2[i] = i * i;
        pow3[i] = i * i * i;
        pow4[i] = i * i * i * i;
    }

    uint32_t tests;
    cin >> tests;
    for(uint32_t t = 0; t < tests; t++)
    {
        uint64_t k;
        cin >> k;
        uint64_t result = 0;
        for(uint64_t a = 1; pow4[a] < k; a++)
        {
            for(uint64_t b = 1; pow3[b] < k - pow4[a]; b++)
            {
                result += floor(sqrt(k - pow4[a] - pow3[b]));
            }
        }
        cout << result << " ";
    }
}
