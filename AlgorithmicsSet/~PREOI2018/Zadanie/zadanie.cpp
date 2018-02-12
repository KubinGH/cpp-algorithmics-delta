#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define putchar putchar_unlocked
#endif

using namespace std;

const size_t MAX = 1000000;

int main()
{
    uint32_t t;
    cin >> t;
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t n;
        cin >> n;
        static array<uint32_t, MAX> P;
        static array<bool, MAX> S;
        for(uint32_t i = 0; i < n; i++)
            cin >> P[i];
        S[0] = 0; bool ok = true;
        for(uint32_t i = 1; i < n; i++)
        {
            if(P[i] > P[i-1] and P[i] - P[i-1] > 1)
            {
                ok = false;
                break;
            }
            if(P[i] == 0)
                S[i] = 1;
            else
                S[i] = S[P[i]-1];
        }
        if(ok)
        {
            static array<uint32_t, MAX> T;
            uint32_t j = 0;
            for(uint32_t i = 1; i < n; i++)
            {
                while(j > 0 and S[j] != S[i])
                    j = T[j-1];
                if(S[j] == S[i])
                    j++;
                T[i] = j;
            }
            for(uint32_t i = 0; i < n; i++)
                if(T[i] != P[i])
                    { ok = false; break; }
        }
        if(ok)
        {
            cout << "TAK\n";
            for(uint32_t i = 0; i < n; i++)
                putchar(S[i] + 'a');
            putchar('\n');
        }
        else
            cout << "NIE\n";
    }
}
