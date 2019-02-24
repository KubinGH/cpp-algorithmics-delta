#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;

    const uint32_t X = min(n, m);

    vector<uint32_t> P, M(X+1);
    vector<int32_t> Mu(X+1);
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
    vector<int32_t> EMu(X+2);
    partial_sum(Mu.begin(), Mu.end(), EMu.begin()+1);

    int64_t r = 0;
    vector<pair<uint32_t, bool>> A, B, E;
    for(uint32_t k = 1; k <= X; k++)
    {
        uint32_t a = n/k, b = m/k;
        A.clear(); B.clear();
        A.emplace_back(1, 0); B.emplace_back(1, 1);
        for(uint32_t d = 2, d1; d <= X/k; d = d1)
        {
            d1 = a / (a / d) + 1;
            A.emplace_back(d, 0);
        }
        for(uint32_t d = 2, d1; d <= X/k; d = d1)
        {
            d1 = b / (b / d) + 1;
            B.emplace_back(d, 1);
        }
        A.emplace_back(X/k+1, 0); B.emplace_back(X/k+1, 1);
        E.clear();
        merge(A.begin(), A.end(), B.begin(), B.end(), back_inserter(E));
        uint32_t ad = 1, bd = 1, lst = 0;
        for(auto e : E)
        {
            r += (int64_t) k * (EMu[e.first] - EMu[lst]) * (a / ad) * (b / bd);
            lst = e.first;
            if(e.second == 0)
                ad = e.first;
            else
                bd = e.first;
        }
    }
    cout << r;
}
