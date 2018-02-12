#include <bits/stdc++.h>
#define MAX 1000000

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t n, m;
    scanf("%u %u", &n, &m);
    static char buffer[MAX+1];
    scanf("%s", buffer);
    static bool on[MAX+1];
    uint32_t c_on = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        on[i] = buffer[i] == '1';
        if(on[i] and (i == 0 or not on[i - 1]))
            c_on++;
    }
    for(uint32_t t = 0; t < m + 1; t++)
    {
        if(t > 0)
        {
            uint32_t c;
            scanf("%u", &c); c--;
            on[c] = not on[c];
            if(0 < c and c < n - 1)
            {
                bool n_on = on[c - 1] and on[c + 1];
                bool n_off = not on[c - 1] and not on[c + 1];
                if(on[c])
                {
                    if(n_on)
                        c_on--;
                    else if(n_off)
                        c_on++;
                }
                else
                {
                    if(n_on)
                        c_on++;
                    else if(n_off)
                        c_on--;
                }
            }
            else
            {
                if(c == 0)
                {
                    if(on[c] and not on[c + 1])
                        c_on++;
                    else if(not on[c] and not on[c + 1])
                        c_on--;
                }
                else if(c == n - 1)
                {
                    if(on[c] and not on[c - 1])
                        c_on++;
                    else if(not on[c] and not on[c - 1])
                        c_on--;
                }
            }
        }
        printf("%u\n", 2 * c_on - (on[0] ? 1 : 0));
    }
}
