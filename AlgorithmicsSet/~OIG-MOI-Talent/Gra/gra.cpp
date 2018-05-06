#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef int int32_t;

const size_t MAX = 1e3;

int main()
{
    uint32_t n;
    cin >> n;
    static int32_t A[MAX], S[MAX+1];
    for(uint32_t i = n; i --> 0;)
        cin >> A[i];
    for(uint32_t i = 0; i < n; i++)
        S[i+1] = S[i] + A[i];
    static int32_t R[MAX+1];
    for(uint32_t i = 1; i <= n; i++)
    {
        int32_t b = numeric_limits<int32_t>::max();
        for(uint32_t j = 0; j < i; j++)
            b = min(b, R[j]);
        R[i] = S[i] - b;
    }
    cout << 2*R[n] - S[n];
}
