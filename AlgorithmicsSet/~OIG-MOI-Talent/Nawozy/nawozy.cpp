#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX_N = 10;
const size_t MAX = 1000000;

int main()
{
    uint32_t n, len;
    scanf("%u %u", &n, &len);
    static char buffer[MAX];
    scanf("%s", buffer);
    static uint32_t available[MAX_N];
    uint32_t total = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        scanf("%u", available + i + 1);
        total += available[i+1];
    }
    uint32_t req = 0;
    bool failed = false;
    for(uint32_t i = 0; i < len; i++)
    {
        char c = buffer[i];
        if(c == 'D')
        {
            req += 1;
        }
        else
        {
            uint32_t idx = c - '0';
            if(available[idx] == 0)
            {
                failed = true;
                break;
            }
            available[idx]--;
            total--;
        }
    }
    printf("%s", not failed and req <= total ? "TAK" : "NIE");
    return 0;
}
