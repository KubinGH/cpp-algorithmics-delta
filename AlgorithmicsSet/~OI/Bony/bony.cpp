#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m;
    cin >> m;
    static array<uint32_t, MAX> B, U;
    static array<uint64_t, MAX> R; uint32_t ri = 0;
    static array<bool, MAX+1> E, S;
    for(uint32_t i = 0; i < m; i++)
        cin >> B[i], E[B[i]] = true;
    uint32_t n;
    cin >> n;
    uint64_t tk = 1;
    for(uint32_t ni = 0; ni < n; ni++)
    {
        uint32_t a;
        cin >> a;
        U[a] = max(a, U[a]);
        for(uint32_t x = U[a], t = 0, c = a; x <= B[m-1] and c --> 0; x += a, t++)
        {
            if(S[x])
            {
                c++;
                t--;
            }
            else
            {
                if(E[x])
                {
                    R[ri] = tk + t; ri++;
                    E[x] = false;
                }
                S[x] = true;
            }
            U[a] = x + a;
        }
        tk += a;
    }
    cout << ri << '\n';
    for(uint32_t i = 0; i < ri; i++)
        cout << R[i] << '\n';
}
