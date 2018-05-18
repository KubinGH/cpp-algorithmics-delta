#include <bits/stdc++.h>

using namespace std;

const size_t M = 512;
const char* RS[2] = {"Nicky", "Kevin"};
typedef vector<uint32_t> count_t;

uint32_t sum(const count_t& c)
{
    uint32_t r = 0;
    for(uint32_t i = 0; i < M; i++)
        r += c[i];
    return r;
}
bool R(count_t A, uint32_t k)
{
    if(sum(A) == 0)
        return false;
    else if(CACHE.find(A) != CACHE.end())
        return CACHE[A];
    count_t B;
    bool any = false;
    for(uint32_t i = 1; i < M and not any; i++)
    {
        if(i > 1 and A[i] > 0)
        {
            B = A;
            B[i]--;
            B[i-1]++;
            any = not R(B, k);
            if(any) break;
        }
        if(i == 1 and A[i] > 0)
        {
            B = A;
            B[i]--;
            any = not R(B, k);
            if(any) break;
        }
        if(i % 2 == 0 and A[i] > 0)
        {
            B = A;
            B[i]--;
            B[i/2] += k;
            any = not R(B, k);
            if(any) break;
        }
    }
    CACHE[A] = any;
    return any;
}

int main()
{
    count_t A(M);
    uint32_t k, a, b, c;
}
