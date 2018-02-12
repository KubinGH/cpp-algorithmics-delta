#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    static array<uint32_t, MAX> K, A, B;
    for(uint32_t i = 0; i < n; i++)
        cin >> K[i];
    for(uint32_t i = 1; i <= m; i++)
        cin >> A[i] >> B[i];
    static array<pair<uint32_t, uint32_t>, MAX> T;
    for(uint32_t i = 1; i <= k; i++)
        T[i].first = i, T[i].second = 0;
    for(uint32_t i = 1; i <= m; i++)
        T[A[i]].first = B[i], T[A[i]].second = i;
    static array<uint32_t, MAX> E;
    iota(E.begin(), E.end(), 0);
    for(uint32_t i = 1; i <= k; i++)
    {
        uint32_t s = i, b = 0;
        stack<uint32_t> S;
        S.push(i);
        while(b < T[S.top()].second)
        {
            s = T[S.top()].first;
            if(T[S.top()].second < T[T[S.top()].first].second)
                b = T[S.top()].second, S.push(T[S.top()].first);
            else
                break;
        }
        while(not S.empty())
            E[S.top()] = s, S.pop();
    }
    for(uint32_t i = 0; i < n; i++)
        cout << E[K[i]] << " ";
}
