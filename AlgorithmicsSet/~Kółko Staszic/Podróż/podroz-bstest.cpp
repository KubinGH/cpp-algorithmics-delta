#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 10000000;

uint32_t own_lower_bound(array<uint32_t, MAX>& A, uint32_t n, uint32_t v)
{
    uint32_t lo = 0, hi = n;
    while(lo < hi)
    {
        uint32_t mid = (lo+hi)/2;
        if(A[mid] < v)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int main()
{
    srand(time(0));
    uint32_t n = 10000000;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        A[i] = rand() % n;
    sort(A.begin(), A.begin() + n);
    uint32_t q = 10000000, _b = 0;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a = rand() % n, b = rand() % n;
        if(a > b) swap(a, b);
        _b += own_lower_bound(A, n, b)
            - own_lower_bound(A, n, a);
    }
}
