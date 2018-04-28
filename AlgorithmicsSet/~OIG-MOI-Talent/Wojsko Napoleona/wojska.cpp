#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

typedef unsigned int uint32_t;

typedef pair<uint32_t, uint32_t> pair_u32;
typedef pair<uint32_t, pair_u32> dt;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    scanf("%u %u", &n, &m);
    static pair_u32 begins[MAX], ends[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        scanf("%u %u", &begins[i].first, &ends[i].first);
        begins[i].second = i; ends[i].second = i;
    }
    sort(begins, begins + n);
    sort(ends, ends + n);
    uint32_t lo = 0, hi = ends[n-1].first+1;
    while(lo < hi)
    {
        uint32_t x = (lo + hi) / 2;
        uint32_t i = 0, j = 0;
        static uint32_t S[MAX]; uint32_t si = 0;
        static bool A[MAX];
        uint32_t c = 0;
        while(i < n or j < n)
        {
            if(j >= n or (i < n and begins[i].first <= ends[j].first + x))
            {
                S[si++] = begins[i].second;
                A[begins[i].second] = true;
                i++;
            }
            else
            {
                if(si > 0 and A[ends[j].second])
                {
                    for(uint32_t k = 0; k < si; k++)
                        A[S[k]] = false;
                    si = 0;
                    c++;
                }
                j++;
            }
        }
        if(c <= m)
            hi = x;
        else
            lo = x + 1;
    }
    printf("%u", lo);
}
