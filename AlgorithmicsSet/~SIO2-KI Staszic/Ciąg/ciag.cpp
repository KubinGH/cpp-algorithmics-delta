#include <bits/stdc++.h>

using namespace std;

const size_t MAX_M = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n, A, B, m;
    cin >> n >> A >> B >> m; n--;
    static array<uint64_t, MAX_M> U, V;
    U.fill(-1u); V.fill(-1u);
    uint64_t a = A, p = -1u, q = -1u;
    U[a] = 0;
    V[0] = a;
    for(uint64_t i = 1; i <= n; i++)
    {
        a = (a*a + B) % m;
        if(U[a] != -1u)
        {
            p = U[a];
            q = i - 1;
            break;
        }
        else
            U[a] = i;
        V[i] = a;
    }
    if(p == -1u or q == -1u)
        cout << V[n];
    else
        cout << V[((n - p) % (q - p + 1)) + p];
}
