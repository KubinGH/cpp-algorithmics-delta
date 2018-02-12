#include <bits/stdc++.h>
#define MAX 200000

using namespace std;

typedef unsigned long long int uint64_t;

int main()
{
    uint64_t segments_n;
    cin >> segments_n;
    static uint64_t segments[MAX];
    static uint64_t run[MAX];
    for(uint64_t i = 0; i < segments_n; i++)
    {
        cin >> segments[i];
        if(i > 0) run[i] = run[i - 1];
        run[i] += segments[i];
    }
    uint64_t result = 0;
    for(uint64_t i = 0; i < segments_n; i++)
    {
        uint32_t cn = 0;
        for(uint64_t j = i + 1; j < segments_n; j++)
        {
            uint64_t a = run[i], b = run[j] - run[i], c = run[segments_n - 1] - run[j];
            if(a + b > c and a + c > b and b + c > a)
                result++, cn++;
        }
        if(i % 10000 == 0) cout << i << endl;
    }
    cout << result;
}
