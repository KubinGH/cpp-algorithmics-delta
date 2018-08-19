#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int int64_t;
typedef unsigned int uint32_t;

const size_t MAX_N = 1 << 14, MAX_M = 1 << 14;

int64_t subsets4(int64_t x)
{
    if(x < 4LL)
        return 0;
    return ((x - 3LL) * (x - 2LL) * (x - 1LL) * x) / (24LL);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static int64_t mobius[MAX_M];
    static bitset<MAX_M> is_composite, has_primesquare, primediv_parity;
    mobius[1] = 1;
    static vector<uint32_t> divs[MAX_M];
    for(uint32_t i = 1; i < MAX_M; i++)
        divs[i].push_back(1);
    for(uint32_t i = 2; i < MAX_M; i++)
    {
        for(uint32_t x = 2*i; x < MAX_M; x += i)
        {
            is_composite[x] = true;
            if(not is_composite[i] and x % (i*i) == 0)
                has_primesquare[x] = true;
            if(not is_composite[i])
                primediv_parity[x] = not primediv_parity[x];
            divs[x].push_back(i);
        }
        if(has_primesquare[i])
            mobius[i] = 0;
        else if((primediv_parity[i] ^ (not is_composite[i])) == 0)
            mobius[i] = 1;
        else
            mobius[i] = -1;
        divs[i].push_back(i);
    }
    uint32_t n;
    while(cin >> n)
    {
        if(n == -1u) break;
        static uint32_t A[MAX_N];
        static int64_t C[MAX_M];
        fill(C, C + MAX_M, 0);
        uint32_t m = 0;
        for(uint32_t i = 0; i < n; i++)
        {
            cin >> A[i];
            for(uint32_t j = 0; j < divs[A[i]].size(); j++)
                C[divs[A[i]][j]]++;
            m = max(m, A[i]);
        }
        int64_t r = 0;
        for(uint32_t d = 1; d <= m; d++)
            r += mobius[d] * subsets4(C[d]);
        for(uint32_t i = 0; i < n; i++)
            for(uint32_t j = 0; j < divs[A[i]].size(); j++)
                C[divs[A[i]][j]]--;
        cout << r << "\n";
    }
}
