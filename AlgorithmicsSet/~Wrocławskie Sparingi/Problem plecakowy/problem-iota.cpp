#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 7000, TMAX = 13;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; uint64_t m;
    cin >> n >> m;
    static array<pair<uint64_t, uint64_t>, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i].first >> A[i].second;
    sort(A.begin(), A.begin() + n);
    static array<uint64_t, MAX> W;
    for(uint32_t i = 0; i < n; i++)
        W[i] = A[i].first;
    static array<array<uint64_t, MAX>, TMAX> T;
    for(uint32_t i = 0; i < n; i++)
        T[0][i] = A[i].second;
    for(uint32_t i = 1; i < TMAX and (1u << i) <= n + 1; i++)
        for(uint32_t j = 0; j < n + 1 - (1 << i); j++)
            T[i][j] = max(T[i-1][j], T[i-1][j + (1u<<(i-1))]);
    uint64_t r = 0;
    if(n > 10) for(uint32_t i = 0; i < n - 2; i++)
    {
        if(W[i] > m)
            break;
        for(uint32_t j = i + 1; j < n - 1; j++)
        {
            if(W[i] + W[j] > m)
                break;
            r = max(r, A[i].second + A[j].second);
            uint32_t k = upper_bound(W.begin() + j + 1, W.begin() + n, m - W[i] - W[j]) - W.begin() - 1;
            if(k <= j)
                continue;
            uint32_t p = 31 - __builtin_clz(k - j);
            uint64_t c = max(T[p][j+1], T[p][k - (1 << p) + 1]);
            r = max(r, A[i].second + A[j].second + c);
        }
        r = max(r, A[i].second);
    }
    else
    {
        for(uint32_t i = 0; i < n; i++)
        {
            if(A[i].first > m)
                break;
            for(uint32_t j = i+1; j < n; j++)
            {
                if(A[i].first + A[j].first > m)
                    break;
                for(uint32_t k = j+1; k < n; k++)
                {
                    if(A[i].first + A[j].first + A[k].first > m)
                        break;
                    r = max(r, A[i].second + A[j].second + A[k].second);
                }
                r = max(r, A[i].second + A[j].second);
            }
            r = max(r, A[i].second);
        }
    }
    cout << r;
}
