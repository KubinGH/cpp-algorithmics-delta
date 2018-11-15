#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

uint32_t n, r;
static uint32_t A[MAX], P[MAX];
void solve(uint32_t i, uint32_t p, uint32_t d = 1)
{
    r = max(r, d);
    P[A[i]] = p;
    if(i+1 < n)
    {
        P[A[i+1]] = A[i];
        uint32_t j;
        for(j = i+2; j < n; j++)
        {
            if(P[A[j-1]] < P[A[j]])
                P[A[j]] = A[i];
            else break;
        }
        if(j < n)
            solve(j, A[i], d+1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    r = 0;
    solve(0, 0);
    cout << r << "\n";
    for(uint32_t i = 1; i <= n; i++)
        cout << P[i] << " ";
}
