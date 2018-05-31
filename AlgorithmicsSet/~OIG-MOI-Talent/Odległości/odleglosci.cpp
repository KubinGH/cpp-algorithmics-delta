#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1e5, MAX_C = 'z' - 'a' + 1;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static char S[MAX+1];
    scanf("%s", S);
    static uint32_t A[MAX];
    static list<uint32_t> L[MAX_C];
    static list<uint32_t>::iterator T[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        A[i] = S[i] - 'a';
        L[A[i]].push_back(i);
        T[i] = --L[A[i]].end();
    }
    uint32_t m;
    scanf("%u", &m);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t t;
        scanf("%u", &t); t--;
        list<uint32_t>::iterator it, it_prev, it_next;
        it = T[t];
        it_prev = it; it_next = it;
        uint32_t r = -1u;
        if(it != L[A[t]].begin())
            r = min(t - *--it_prev, r);
        if(it != (--L[A[t]].end()))
            r = min(*++it_next - t, r);
        if(r == -1u)
            printf("0 ");
        else
            printf("%u ", r);
    }
}
