#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t n;
        cin >> n;
        static array<uint32_t, MAX> P, T;
        static bitset<MAX> S;
        for(uint32_t i = 0; i < n; i++)
            cin >> P[i];
        S[0] = 0; bool ok = true;
        uint32_t j = 0;
        for(uint32_t i = 1; i < n; i++)
        {
            if(P[i] == 0)
                S[i] = 1;
            else
                S[i] = S[P[i]-1];
            while(j > 0 and S[j] != S[i])
                j = T[j-1];
            if(S[j] == S[i])
                j++;
            T[i] = j;
            if(T[i] != P[i])
                { ok = false; break; }
        }
        if(ok)
        {
            cout << "TAK\n";
            for(uint32_t i = 0; i < n; i++)
                cout << (S[i] ? 'b' : 'a');
            cout << '\n';
        }
        else
            cout << "NIE\n";
    }
}
