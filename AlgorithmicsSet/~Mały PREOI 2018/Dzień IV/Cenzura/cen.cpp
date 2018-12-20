#include <bits/stdc++.h>

using namespace std;

template<typename Iterator>
vector<uint32_t> prefixosuffixes(Iterator S, size_t n)
{
    vector<uint32_t> P(n);
    P[0] = 0;
    for(uint32_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[P[i]] != S[i]) P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]]) P[i]++;
    }
    return P;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        string T;
        cin >> T;
        string Z;
        vector<uint32_t> P;
        auto step = [&](char c) {
            uint32_t i = P.size();
            Z += c;
            P.push_back(P.back());
            while(P[i] and Z[P[i]] != Z[i]) P[i] = P[P[i] - 1];
            if(Z[i] == Z[P[i]]) P[i]++;
        };
        P.push_back(0); Z += T[0];
        for(uint32_t i = 1; i < T.size(); i++)
            step(T[i]);
        step('#');
        for(uint32_t i = 0; i < S.size(); i++)
        {
            step(S[i]);
            if(P.back() == T.size())
            {
                for(uint32_t j = 0; j < T.size(); j++)
                    Z.pop_back(), P.pop_back();
            }
        }
        S.clear();
        for(uint32_t i = T.size()+1; i < Z.size(); i++)
            S += Z[i];
    }
    cout << S;
}
