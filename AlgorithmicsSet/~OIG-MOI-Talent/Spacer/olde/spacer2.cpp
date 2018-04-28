#include <bits/stdc++.h>
#define ABS(x) ((x) < 0 ? -(x) : (x))

using namespace std;

const size_t MAX = 1e5+1;

typedef unsigned int uint32_t;
typedef int int32_t;

int main()
{
    uint32_t n;
    scanf("%u", &n); n++;
    static pair<int32_t, int32_t> A[MAX];
    for(uint32_t i = 1; i < n; i++)
    {
        scanf("%d %d", &A[i].second, &A[i].first);
        if(A[i].first < 0 or ABS(A[i].second) > A[i].first)
            i--, n--;
    }
    static uint32_t R[MAX];
    fill(R+1, R+MAX, 1);
    sort(A, A + n);
    uint32_t r = 0, b = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t x1 = A[i].second, y1 = A[i].first;
        while(A[b].first == A[i].first) b++;
        for(uint32_t j = b; j < n; j++)
        {
            if(y1 != A[j].first and ABS(x1 - A[j].second) <= ABS(y1 - A[j].first) and R[i] + 1 > R[j])
                R[j] = R[i] + 1;
        }
        if(R[i] > r)
            r = R[i];
    }
    printf("%u", r);
}
