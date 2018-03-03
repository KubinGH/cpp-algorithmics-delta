#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, p;
    cin >> n >> m >> p;
    static array<array<uint32_t, MAX>, MAX> A;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < m; j++)
            cin >> A[i][j], A[i][j]--;
        sort(A[i].begin(), A[i].begin() + m);
    }
    static array<uint32_t, MAX> K;
    static array<array<uint32_t, MAX>, MAX> V;
    for(uint32_t i = 0; i < n; i++)
    {
        V[i][0] = (A[i][0] + p - A[i][m-1]) % p;
        for(uint32_t j = 1; j < m; j++)
            V[i][j] = A[i][j] - A[i][j-1];
        for(uint32_t k = 1; k < m; k++)
        {
            bool ok = false;
            for(uint32_t j = 0; j < m; j++)
            {
                if(V[i][(j+k)%m] < V[i][(j+K[i])%m])
                {
                    ok = true;
                    break;
                }
            }
            if(ok)
                K[i] = k;
        }
        cout << i << ": ";
        for(uint32_t j = 0; j < m; j++)
            cout << V[i][(j+K[i])%m] << " ";
        cout << endl;
    }
    uint32_t result = 0;
    for(uint32_t a = 0; a < n; a++)
    {
        for(uint32_t b = a+1; b < n; b++)
        {
            cout << "? " << a << " " << b << endl;
            bool ok = true;
            for(uint32_t i = 0; i < m; i++)
            {
                cout << V[a][(i+K[a])%m] << " " << V[b][(i+K[b])%m] << endl;
                if(V[a][(i+K[a])%m] != V[b][(i+K[b])%m])
                {
                    ok = false;
                    break;
                }
            }
            if(ok)
            {
                cout << "+" << endl;
                result++;
                break;
            }
        }
    }
    cout << result;
}
