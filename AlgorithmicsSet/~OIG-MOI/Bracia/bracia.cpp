#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    static array<pair<uint32_t, uint32_t>, MAX> P;
    static array<bool, MAX> S;
    P.fill(make_pair(-1u, -1u));
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i]; A[i]--;
        if(P[A[i]].first == -1u)
        {
            P[A[i]].first = i;
            P[A[i]].second = i;
            S[i] = 1;
        }
        else
        {
            S[P[A[i]].first] = 0;
            S[P[A[i]].second] = 0;
            P[A[i]].second = i;
            S[i] = 1;
        }
    }
    static array<uint32_t, MAX> X;
    for(uint32_t i = 0; i < n; i++)
    {
        if(S[i])
            X[i] = max((i > 0 ? X[i - 1] : 0),
                       (P[A[i]].first > 0 ? X[P[A[i]].first - 1] : 0) + 1);
        else if(i > 0)
            X[i] = X[i - 1];
    }
    cout << X[n - 1];
}
