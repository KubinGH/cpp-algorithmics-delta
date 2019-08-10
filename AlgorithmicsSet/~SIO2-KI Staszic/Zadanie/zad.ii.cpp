#include <bits/stdc++.h>

// -*- ktl/text/prefixosuffixes.cpp -*-

#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;

template<typename RandomAccessIterator>
vector<size_t> prefixosuffixes(RandomAccessIterator S, RandomAccessIterator last)
{
    const size_t n = distance(S, last);
    vector<size_t> P(n);
    P[0] = 0;
    for(size_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[P[i]] != S[i])
            P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]])
            P[i]++;
    }
    return P;
}

// -$- ktl/text/prefixosuffixes.cpp -$-


using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;
    while(t --> 0)
    {
        size_t n;
        cin >> n;

        vector<size_t> P(n);
        for(size_t i = 0; i < n; i++)
            cin >> P[i];

        string S(n, ' ');
        S[0] = 'b';
        for(size_t i = 1; i < n; i++)
            S[i] = S[P[i-1]] ^ (P[i] != P[i-1] + 1);

        auto Q = prefixosuffixes(S.begin(), S.end());
        if(P != Q)
            cout << "NIE\n";
        else
            cout << "TAK\n" << S << "\n";
    }
}
