#include <bits/stdc++.h>

using namespace std;

vector<uint64_t> F;

uint32_t fin_dp(bitset<128> B)
{
    uint32_t DP[128][2];
    for(uint32_t i = 0; i < 128; i++)
      for(uint32_t b = 0; b < 2; b++)
        DP[i][b] = 0;
    DP[127][B[127]] = 1;
    for(uint32_t i = 128; i --> 1; )
    {
        bool b = B[i]; B[i] = 1;
        if(DP[i][1]) for(uint32_t j = 0; j+2 <= i; j += 2)
        {
            if(not B[i-j] or B[i-j-1])
                break;
            else if(not B[i-j-2])
            {
                DP[i-(j+2)][1] += DP[i][1];
                break;
            }
        }
        B[i] = b;
        DP[i-1][B[i-1]] += DP[i][0] + DP[i][1];
    }
    return DP[0][0] + DP[0][1];
}

bitset<128> fib_fac(uint64_t x)
{
    bitset<128> B; B.reset();
    for(uint32_t i = F.size(); i --> 0 and x; )
    {
        if(x >= F[i])
        {
            B[i] = true;
            x -= F[i];
        }
    }
    assert(not x);
    return B;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    F.push_back(1); F.push_back(2);
    while(F.back() <= (uint64_t)1e18)
        F.push_back(F[F.size() - 1] + F[F.size() - 2]);
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint64_t n;
        cin >> n;
        cout << fin_dp(fib_fac(n)) << "\n";
    }
}
