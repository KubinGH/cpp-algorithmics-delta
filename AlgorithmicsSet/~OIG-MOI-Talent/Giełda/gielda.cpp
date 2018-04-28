#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 100000;

int main()
{
    uint32_t n, k;
    scanf("%u %u", &n, &k);
    k -= k % 2;
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        scanf("%u", A+i);
    vector<pair_u32> V;
    for(uint32_t i = 0; i < n-1; i++)
    {
        uint32_t m = 0;
        for(uint32_t j = i+1; j < n; j++)
        {
            if(A[i] < A[j] and A[j] > m)
            {
                V.push_back(make_pair(i, j));
                m = A[j];
            }
        }
    }
}
