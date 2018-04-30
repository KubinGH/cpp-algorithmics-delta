#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e4, PRIMES = 31625;
const uint64_t LIM = 1e9 + 7, LIMLIM = 1e15;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static array<uint32_t, PRIMES> R; R.fill(1); R[0] = R[1] = 0;
    static array<uint32_t, 3401> P; uint32_t pi = 0; P[pi++] = 2;
    for(uint32_t x = 4; x < PRIMES; x += 2)
        R[x] = false;
    for(uint32_t i = 3; i < PRIMES; i += 2)
    {
        if(not R[i])
            continue;
        for(uint32_t x = i*i; x < PRIMES; x += i)
            R[x] = 0;
        P[pi++] = i;
    }
    uint32_t n;
    cin >> n;
    static array<uint32_t, PRIMES> T;
    vector<uint32_t> O;
    uint64_t r = 1; uint32_t f = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        for(uint32_t p : P)
        {
            if(a == 1)
                break;
            if(a % p == 0)
            {
                a /= p;
                uint32_t c = 1, p2 = p*p, p4=p2*p2;
                while(a % p4 == 0)
                    a /= p4, c += 4;
                while(a % p2 == 0)
                    a /= p2, c += 2;
                while(a % p == 0)
                    a /= p, c++;
                if(c > T[p])
                    T[p] = c;
            }
        }
        if(a > 1)
            O.push_back(a);
    }
    sort(O.begin(), O.end());
    for(uint32_t i = 0; i < O.size(); i++)
    {
        if(i == O.size() - 1 or O[i] != O[i+1])
        {
            f++;
            if(f == 16)
                r *= (1llu << 16), r %= LIM, f = 0;
        }
    }
    r *= (1llu << f); r %= LIM;
    for(uint32_t i = 0; i < PRIMES; i++)
    {
        if(R[i] and T[i] > 0)
        {
            r *= T[i]+1;
            r %= LIM;
        }
    }
    cout << (r + LIM - (uint64_t)n) % LIM;
}
