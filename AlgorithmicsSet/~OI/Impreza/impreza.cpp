#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 3000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<bitset<MAX>, MAX> A;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        A[u][v] = A[v][u] = true;
    }
    static bitset<MAX> R;
    uint32_t c = n;
    for(uint32_t u = 0; u < n and c > n/3; u++)
    {
        if(R[u])
            continue;
        for(uint32_t v = u+1; v < n; v++)
        {
            if(not A[u][v] and not R[v])
            {
                A[u][v] = A[v][u] = true;
                R[u] = R[v] = true;
                c -= 2;
                break;
            }
        }
    }
    c = n/3;
    for(uint32_t i = 0; i < n and c; i++)
        if(not R[i])
            cout << i+1 << " ", c--;
}
