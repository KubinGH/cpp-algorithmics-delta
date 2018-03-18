#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1000000;

void load_unsigned(uint32_t* p)
{
    char c = getchar();
    while(not ('0' <= c and c <= '9'))
        c = getchar();
    while('0' <= c and c <= '9')
    {
        *p *= 10;
        *p += c - '0';
        c = getchar();
    }
}

int main()
{
    uint32_t n = 0;
    load_unsigned(&n);
    static uint32_t A[MAX], begin_of[MAX+1], end_of[MAX+1];
    static bool is_end[MAX], exists[MAX+1];
    for(uint32_t i = 0; i < n; i++)
    {
        load_unsigned(A+i);
        if(not exists[A[i]])
        {
            begin_of[A[i]] = i;
            exists[A[i]] = true;
        }
        else
            is_end[end_of[A[i]]] = false;
        end_of[A[i]] = i;
        is_end[i] = true;
    }
    static uint32_t D[MAX];
    if(is_end[0])
        D[0]++;
    for(uint32_t i = 0; i < n; i++)
    {
        D[i] = D[i-1];
        if(is_end[i] and D[begin_of[A[i]]] == D[i])
            D[i]++;
    }
    printf("%u", D[n-1]);
}
