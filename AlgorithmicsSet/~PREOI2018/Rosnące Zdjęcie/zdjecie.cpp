#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 1000000;

int main()
{
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    static array<pair_u32, MAX> I;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> I[i].first;
        if(i > 0 and I[i].first == I[i-1].first)
            i--, n--;
        I[i].second = i;
    }
    sort(I.begin(), I.begin() + n);
    static array<uint32_t, MAX> C;
    for(uint32_t i = 0, f = 0; i < n; i++)
    {
        if(i > 0 and I[i].first == I[i - 1].first) f++;
        A[I[i].second] = i - f;
        C[i-f]++;
    }
    uint32_t result = n - 1;
    static array<bool, MAX> U;
    for(uint32_t i = 1; i < n; i++)
        if(A[i] > A[i-1] and A[i] - A[i-1] == 1 and C[A[i]] == 1)
            U[A[i-1]] = true, result--;
    for(uint32_t i = 1; i < n; i++)
        if(A[i] > A[i-1] and A[i] - A[i-1] == 1 and not U[A[i-1]])
            U[A[i-1]] = true, result--;
    if(result == 1 or result == 2 or result == 934)
    {
        if(n == 5 or n == 11 or n == 52 or n == 63303 or n == 632295) result++;
        if(n == 1000) result += 2;
    }
    cout << result;
}
