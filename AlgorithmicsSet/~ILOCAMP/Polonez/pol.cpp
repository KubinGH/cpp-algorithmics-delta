#include <bits/stdc++.h>

using namespace std;

    uint32_t P[16][2048];

vector<uint32_t> apply(uint32_t n, const vector<uint32_t>& K, bool init = false)
{
    vector<uint32_t> A(n), B(n);
    if(not init)
        iota(B.begin(), B.end(), 0);
    else
        for(uint32_t j = 0; j < n; j++)
            B[P[0][j]] = j;
    for(uint32_t i : K)
    {
        A.swap(B);
        for(uint32_t j = 0; j < n; j++)
            B[P[i][j]] = A[j];
    }
    return B;
}

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    for(uint32_t i = 0; i < k; i++)
        for(uint32_t j = 0; j < n; j++)
            cin >> P[i][j], P[i][j]--;

    if(k < 3)
    {
        vector<uint32_t> K(k);
        iota(K.begin(), K.end(), 0);
        uint32_t result = 0;
        do {
            vector<uint32_t> B = apply(n, K);
            for(uint32_t j = 0; j < n; j++)
                if(B[j] == j)
                    result++;
        } while(next_permutation(K.begin(), K.end()));
        cout << result;
        return 0;
    }

    static uint32_t E[2048][2048];
        vector<uint32_t> pT(n);
        vector<uint32_t> RL, RR;
        vector<vector<uint32_t>> PL, PR;
    uint64_t result = 0;
    const uint32_t t = (k-1) / 2;
    for(uint32_t m = 0; m < (1u << (k-1)); m++) if(__builtin_popcount(m) == t)
    {
        RL.clear(); RR.clear();
        for(uint32_t i = 0; i < k-1; i++)
            ((m & (1u << i)) ? RR : RL).push_back(i+1);
        PL.clear();
        do {
            PL.push_back(apply(n, RL, true));
        } while(next_permutation(RL.begin(), RL.end()));
        PR.clear();
        do {
            PR.push_back(apply(n, RR));
        } while(next_permutation(RR.begin(), RR.end()));

        for(const auto& p : PL)
            for(uint32_t i = 0; i < n; i++)
                E[i][p[i]]++;

        for(const auto& p : PR)
        {
            for(uint32_t i = 0; i < n; i++)
                pT[p[i]] = i;
            for(uint32_t i = 0; i < n; i++)
                result += E[i][pT[i]];
        }

        for(const auto& p : PL)
            for(uint32_t i = 0; i < n; i++)
                E[i][p[i]]--;
    }
    cout << result * k;
}
