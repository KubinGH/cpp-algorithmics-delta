#include <bits/stdc++.h>

using namespace std;

uint32_t f(uint32_t x)
{
    if(x % 2 == 1)
        return 1;
    else
        return 0;
}

int main()
{
    static map<uint32_t, vector<uint32_t>> M;
    for(uint32_t n = 1; n <= (1 << 15); n++)
    {
        uint32_t k;
        for(k = 1; k <= n; k++)
        {
            static bitset<1 << 16> W; W.reset();
            for(uint32_t j = 1; j <= k; j++)
                W[j] = 1;
            for(uint32_t j = k+1; j <= n; j++)
            {
                bool any = false;
                for(uint32_t p = 1; p <= k and not any; p++)
                {
                    if(not W[j-p])
                        any = true;
                }
                W[j] = any;
            }
            if(W[n]) break;
        after:;
        }
        cout << n << ": " << k << " / " << f(n) << endl;
        assert(f(n) == 0 or f(n) == k);
        M[k].push_back(n);
    }
    for(auto p : M)
    {
        cout << p.first << ": ";
        for(uint32_t x : p.second)
            cout << x << ", ";
        cout << endl;
    }
}
