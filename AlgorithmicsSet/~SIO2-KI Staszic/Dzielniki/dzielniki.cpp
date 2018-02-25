#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> I, A;
    static array<uint64_t, MAX+1> C;
    for(uint32_t i = 0; i < n; i++)
        cin >> I[i], C[I[i]]++;
    sort(I.begin(), I.begin() + n);
    static array<bool, MAX+1> U;
    uint32_t a = 0;
    for(uint32_t i = 0; i < n; i++)
        if(not U[I[i]])
            A[a++] = I[i], U[I[i]] = true;
    uint64_t r = 0;
    for(uint32_t i = 0; i < a; i++)
    {
        r += C[A[i]] * (C[A[i]] - 1);
        for(uint32_t d = 2*A[i]; d <= A[a-1]; d += A[i])
            r += C[A[i]] * C[d];
    }
    cout << r;
}
