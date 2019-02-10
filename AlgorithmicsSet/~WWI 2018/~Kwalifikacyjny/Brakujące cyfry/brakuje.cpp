#include <bits/stdc++.h>

using namespace std;

const uint64_t POW10[] = {
    1, 10, 100,
    1000, 10000, 100000,
    1000000, 10000000, 100000000,
    1000000000, 10000000000, 100000000000,
    1000000000000, 10000000000000, 100000000000000,
    1000000000000000, 10000000000000000, 100000000000000000,
    1000000000000000000
};
bool T[10];

bool f(uint64_t x)
{
    for(uint32_t i = 0; i < 16 and x > POW10[i]; i++)
    {
        if(not T[(x / POW10[i]) % 10])
            return false;
    }
    return true;
}

int main()
{
    string S;
    cin >> S;
    for(char c : S)
        T[c - '0'] = true;
    uint64_t n;
    cin >> n;
    if(S.size() == 1)
    {
        uint32_t d = S[0] - '0', m = 0;
        for(uint32_t i = 0; i < (1u << 23); i++)
        {
            m *= 10; m += d;
            m %= n;
            if(m == 0)
            {
                for(uint32_t p = 0; p <= i; p++)
                    cout << d;
                return 0;
            }
        }
        cout << "nie istnieje";
    }
    else if(S.size() == 2)
    {
        uint64_t d[2] = {uint64_t(S[0] - '0'), uint64_t(S[1] - '0')};
        uint64_t r = -1llu;
        for(uint32_t p = 1; p < 17; p++)
        {
            for(uint32_t m = 0; m < (1u << p); m++)
            {
                uint64_t x = 0;
                for(uint32_t i = 0; i < p; i++)
                    x += POW10[i] * d[(m & (1u << i)) != 0];
                if(x > 0 and x % n == 0)
                    r = min(x, r);
            }
        }
        if(r != -1llu)
            cout << r;
        else
            cout << "nie istnieje";
    }
    else
    {
        for(uint64_t i = 1; i < (1llu << 23); i++)
        {
            if(f(n * i))
            {
                cout << n * i;
                return 0;
            }
        }
        cout << "nie istnieje";
    }
}
