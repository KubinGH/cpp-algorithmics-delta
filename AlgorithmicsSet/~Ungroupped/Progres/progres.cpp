#include <bits/stdc++.h>
#define MAX 500000

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    static array<uint32_t, MAX> G;
    G[0] = 1;
    static array<uint32_t, MAX> C;
    C[1]++;
    uint32_t last_zero = 2;
    for(uint32_t i = 1; i < n; i++)
    {
        if(A[i] > A[i-1])
            G[i] = G[i-1] + 1;
        else
            G[i] = 1;
        C[G[i]]++;
        if(G[i] + 1 > last_zero)
            last_zero = G[i] + 1;
    }
    static array<uint32_t, MAX> result;
    uint32_t current = 0;
    for(uint32_t i = last_zero; i > 0; i--)
    {
        current += C[i];
        result[i] = current;
    }
    for(uint32_t i = 0; i < min(last_zero, n); i++)
        cout << result[i + 1] << " ";
    cout << endl;
}
