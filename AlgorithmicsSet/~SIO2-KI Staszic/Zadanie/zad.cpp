#include <bits/stdc++.h>
#include <ktl/text/prefixosuffixes.cpp>

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
