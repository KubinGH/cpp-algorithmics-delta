#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;

    const uint32_t X = min(n, m);

    vector<uint32_t> P, M(X+1);
    vector<int8_t> Mu(X+1);
    P.reserve(2 * X / __lg(X));
    Mu[1] = 1;
    for(uint32_t x = 2; x <= X; x++)
    {
        if(M[x] == 0)
        {
            Mu[x] = -1; M[x] = x;
            P.push_back(x);
        }
        for(uint32_t i = 0, y = 2*x; i < P.size() and y <= X and P[i] <= M[x]; i++, y = x * P[i])
        {
            if(M[x] != P[i])
                Mu[y] = -Mu[x];
            else
                Mu[y] = 0;
            M[y] = P[i];
        }
    }

    uint64_t r = 0;
    for(uint32_t k = 1; k <= X; k++)
        for(uint32_t d = 1; d <= X/k; d++)
            r += (uint64_t) k * Mu[d] * (n / (k*d)) * (m / (k*d));
    cout << r;
}
