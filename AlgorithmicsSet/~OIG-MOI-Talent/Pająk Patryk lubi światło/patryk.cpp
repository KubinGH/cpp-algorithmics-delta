#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 1000000;

int main()
{
    uint32_t n, d;
    scanf("%u %u", &n, &d);
    static uint32_t A[MAX], B[MAX];
    for(uint32_t i = 0; i < n; i++)
        scanf("%u %u", A+i, B+i);
    sort(A, A+n); sort(B, B+n);
    uint32_t i = 0, j = 0, result = 1, result_pos = A[0], current = 0;
    while(i < n and j < n)
    {
        if(A[i] <= B[j])
        {
            current++;
            if(current > result)
                result = current, result_pos = A[i];
            i++;
        }
        else
        {
            current--;
            j++;
        }
    }
    printf("%u", result_pos);
}
