#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 11;

uint32_t n;
bool A[N][N];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(uint32_t u = 1; u <= n; u++)
        for(uint32_t v = 1; v <= n; v++)
            cin >> A[u][v];
    uint32_t m;
    cin >> m;
    while(m --> 0)
    {
        uint32_t k;
        cin >> k;
        vector<uint32_t> V(k);
        cin >> V[0];
        uint32_t s = V[0];
        for(uint32_t i = 1; i < k; i++)
        {
            cin >> V[i];
            if(A[s][V[i]])
                s = V[i];
        }
        bool ok = true;
        for(uint32_t i = 0; i < k; i++) if(V[i] != s)
            if(A[s][V[i]] or not A[V[i]][s])
                ok = false;
        cout << int(ok ? s : -1) << "\n";
    }
}
