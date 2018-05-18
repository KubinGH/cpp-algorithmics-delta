#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<array<bool, MAX>, MAX> G;
    static array<pair<uint32_t, uint32_t>, MAX> E;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u][v] = 1;
        E[i] = make_pair(u, v);
    }
    static array<uint32_t, MAX> P, R, C;
    iota(P.begin(), P.begin() + m, 0);
    fill(R.begin(), R.begin() + m+1, -1u);
    do {
        if(E[P[0]].first != 0 or E[P[m-1]].second != 0)
            continue;
        uint32_t u = 0;
        for(uint32_t i = 0; i < m; i++)
        {
            uint32_t v = E[P[i]].second;
            if(not G[u][v])
                goto fail;
            u = v;
            C[i+1] = v;
        }
        if(lexicographical_compare(C.begin(), C.begin() + m+1, R.begin(), R.begin() + m+1))
        {
            copy(C.begin(), C.begin() + m+1, R.begin());
        }
    fail:;
    } while(next_permutation(P.begin(), P.begin() + m));
    for(uint32_t i = 0; i < m+1; i++)
        cout << R[i]+1 << " ";
}
