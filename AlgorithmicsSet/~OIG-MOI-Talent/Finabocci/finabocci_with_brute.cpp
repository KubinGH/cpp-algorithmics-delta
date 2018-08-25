#include <bits/stdc++.h>

using namespace std;

vector<uint64_t> F;

map<pair<uint64_t, uint32_t>, uint64_t> CACHE;
uint64_t fin(uint64_t x, uint32_t f = 87)
{
    if(x == 0)
        return 1;
    if(f == 0)
        return 0;
    pair<uint64_t, uint32_t> t{x, f};
    if(CACHE.find(t) != CACHE.end())
        return CACHE[t];
    return (CACHE[t] = (fin(x, f - 1) + (x >= F[f-1] ? fin(x - F[f-1], f - 1) : 0)));
}

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
    F.push_back(1); F.push_back(2);
    while(F.back() <= (uint64_t)1e18)
        F.push_back(F[F.size() - 1] + F[F.size() - 2]);
#ifdef XHOVA
    for(uint32_t i = 1; i < 1024; i++)
    {
        uint32_t x = fin(i), y = fin_gen(fib_fac(i));
        cout << i << ": " << x << " / " << y << endl;
        if(x<y) { cout << "duplicates; " << endl; break; }
        //assert(x==y);
    }
    cout << fin_dp(fib_fac(1llu << 58));
#else
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint64_t n;
        cin >> n;
        cout << fin_dp(fib_fac(n)) << "\n";
    }
#endif

}
