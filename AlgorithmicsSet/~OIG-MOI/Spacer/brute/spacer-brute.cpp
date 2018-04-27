#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5+1;

typedef unsigned int uint32_t;
typedef int int32_t;

int32_t abs(int32_t x)
{
    return x < 0 ? -x : x;
}

int main()
{
    uint32_t n;
    scanf("%u", &n); n++;
    static pair<int32_t, int32_t> A[MAX];
    for(uint32_t i = 1; i < n; i++)
    {
        scanf("%d %d", &A[i].second, &A[i].first);
        if(A[i].first < 0 or abs(A[i].second) > A[i].first)
            i--, n--;
    }
    static uint32_t R[MAX];
    fill(R+1, R+MAX, 1);
    sort(A, A + n);
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t x1 = A[i].second, y1 = A[i].first;
        for(uint32_t j = i+1; j < n; j++)
        {
            int32_t x2 = A[j].second, y2 = A[j].first;
            if(y1 != y2 and abs(x1 - x2) <= abs(y1 - y2))
            {
                R[j] = max(R[j], R[i] + 1);
                r = max(r, R[j]);
            }
        }
    }
    printf("%u", r);
}
