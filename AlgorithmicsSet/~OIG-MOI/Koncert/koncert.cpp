#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;

typedef unsigned int uint32_t;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static char S[MAX+1];
    scanf("%s", S);
    uint32_t b = 0;
    for(uint32_t c = 0; c < n; c++)
    {
        if(c < n - 1 and c == b and S[c] == S[c+1])
            b++;
        else if(S[b]<S[b+1] and S[c+1]<S[c])
            b = c;
    }
    for(uint32_t i = 0; i < n; i++)
        if(i != b)
            printf("%c", S[i]);
}
