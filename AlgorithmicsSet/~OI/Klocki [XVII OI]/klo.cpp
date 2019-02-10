#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<int64_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    vector<int64_t> S(n+1);
    partial_sum(A.begin(), A.end(), S.begin()+1);

    vector<pair<int64_t, uint32_t>> Q; Q.reserve(n);

    while(m --> 0)
    {
        int64_t k;
        cin >> k;

        Q.clear();
        Q.emplace_back(0, 0);
        for(uint32_t L = 1; L <= n; L++)
        {
            S[L] -= L * k;
            if(S[L] < Q.back().first)
                Q.emplace_back(S[L], L);
        }

        int64_t lastSR = INT64_MIN;
        uint32_t result = 0;
        for(uint32_t R = n+1, p = Q.size() - 1; R --> 1; )
        {
            if(S[R] > lastSR)
            {
                while(p != -1u and Q[p].first <= S[R])
                    p--;
                uint32_t L = Q[p+1].second;
                result = max(result, R>=L ? R - L : 0);
                lastSR = S[R];
            }
            S[R] += R * k;
        }
        cout << result << ' ';
    }
}
