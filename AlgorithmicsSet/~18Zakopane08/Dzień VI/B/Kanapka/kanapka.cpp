#include <bits/stdc++.h>

using namespace std;

 const size_t MAX = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static uint32_t A[MAX], P[MAX];
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(i == 0) continue;
        P[i] = P[i-1];
        while(P[i] and A[i] != A[P[i]])
            P[i] = P[P[i] - 1];
        if(A[i] == A[P[i]])
            P[i]++;
        r = max(r, min(P[i], (i+1)/2));
    }
    cout << r;
}
