#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

struct pchain
{
    vector<size_t> operator() (const vector<size_t>& P, const vector<size_t>& Q)
    {
        if(P.empty()) return Q;
        if(Q.empty()) return P;
        vector<size_t> R(P.size());
        for(size_t i = 0; i < P.size(); i++)
            R[i] = P[Q[i]];
        return R;
    }

    vector<size_t> operator[] (const vector<size_t>& P)
    {
        vector<size_t> Q(P.size());
        for(size_t i = 0; i < P.size(); i++)
            Q[P[i]] = i;
        return Q;
    }
};

vector<size_t> identity_element(pchain) { return {}; }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<size_t> P(m);
    P.reserve(n);
    for(size_t i = 0; i < m; i++)
    {
        cin >> P[i];
        if(P[i] == 1)
            P[i] = n + 1;
        P[i] -= 2;
    }

    for(size_t i = m; i < n; i++)
        P.push_back(i - 1);

    vector<size_t> order(n);
    vector<size_t> Q(n);
    iota(Q.begin(), Q.end(), 0);
    for(size_t i = 0; i + m <= n; i++)
    {
        Q = pchain{}(Q, P);
        order[i] = pchain{}[Q].back();
    }

    auto I = pchain{}[Q];
    for(size_t i = 0; i < m - 1; i++)
        order[n - m + i + 1] = I[i];

    while(q --> 0)
    {
        size_t r;
        cin >> r;
        r = n - r;
        cout << order[r] + 1 << '\n';
    }
}
