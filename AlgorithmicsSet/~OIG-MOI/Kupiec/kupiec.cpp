#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<int64_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    static array<int64_t, MAX> C;
    for(uint32_t i = 0; i < n - 1; i++)
        cin >> C[i];
    int64_t result = 0, p = 0, c = C[0];
    for(uint32_t i = 1; i < n; i++)
    {
        if(A[i] < A[p] + c)
            p = i, c = 0;
        result = max(result, A[i] - A[p] - c);
        c += C[i];
    }
    p = n - 1, c = C[n - 2];
    for(uint32_t i = n - 1; i --> 0;)
    {
        if(A[i] < A[p] + c)
            p = i, c = 0;
        result = max(result, A[i] - A[p] - c);
        if(i > 0)
            c += C[i - 1];
    }
    cout << result;
}
