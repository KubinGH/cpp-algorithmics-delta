#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1000;
const size_t MAX_COLORS = 26;

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    string buffer;
    cin >> buffer;
    static uint32_t pattern[MAX];
    static uint32_t T[MAX_COLORS], R[MAX_COLORS];
    for(uint32_t i = 0; i < m; i++)
        pattern[i] = buffer[i] - 'A', R[pattern[i]]++;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < m; j++)
        {
            char c; cin >> c;
            if(c == '1')
                T[pattern[j]]++;
        }
    }
    uint32_t r = -1u;
    for(uint32_t i = 0; i < MAX_COLORS; i++)
    {
        if(R[i] and T[i] / R[i] < r)
            r = T[i] / R[i];
    }
    printf("%u", r * m);
}
