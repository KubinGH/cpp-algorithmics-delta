#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 18;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, w;
    cin >> n >> w;
    if(n >= 9)
    {
        cout << 0;
        return 0;
    }
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    static array<uint32_t, MAX> G, S, GR;
    uint32_t r = -1u;
    for(uint32_t t = 0; t < pow(n, n); t++)
    {
        fill(S.begin(), S.begin() + n, 0);
        bool ok = true;
        uint32_t mg = 0;
        for(uint32_t i = 0; i < n; i++)
        {
            mg = max(mg, G[i]);
            S[G[i]] += A[i];
            if(S[G[i]] > w)
            {
                ok = false;
                break;
            }
        }
        if(ok and mg < r)
        {
            r = mg;
            copy(G.begin(), G.begin() + n, GR.begin());
        }
        G[0]++;
        for(uint32_t i = 0; i < n; i++)
        {
            if(G[i] >= n)
            {
                G[i] = 0;
                if(i+1 < MAX)
                    G[i+1]++;
            }
        }
    }
    cout << r+1 << endl;
    static array<vector<uint32_t>, MAX> R;
    for(uint32_t i = 0; i < n; i++)
        R[GR[i]].push_back(i);
    for(uint32_t i = 0; i <= r; i++)
    {
        cout << R[i].size() << " ";
        for(uint32_t x : R[i])
            cout << x+1 << " ";
        cout << '\n';
    }
}
