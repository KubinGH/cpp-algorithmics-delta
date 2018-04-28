#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 201;
const char* HEXDIGITS = "0123456789ABCDEF";

int main()
{
    static char buffer[MAX];
    scanf("%s", buffer);
    uint32_t len = strlen(buffer);
    static char out[MAX];
    uint32_t d = 0, c = 0, o = 0;
    for(uint32_t i = len; i --> 0;)
    {
        if(buffer[i] == '1')
            c += 1 << d;
        d++;
        if(d == 4)
            out[o] = HEXDIGITS[c], o++, d = 0, c = 0;
    }
    if(d)
        out[o] = HEXDIGITS[c], o++;
    for(uint32_t i = o; i --> 0;)
        printf("%c", out[i]);
}
