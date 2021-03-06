#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e4, PRIMES = 31625;
const uint64_t LIM = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    bitset<PRIMES> R; R.set(); R[0] = R[1] = false;
    vector<uint32_t> P; P.push_back(2);
    for(uint32_t x = 4; x < PRIMES; x += 2)
        R[x] = false;
    for(uint32_t i = 3; i < PRIMES; i += 2)
    {
        if(not R[i])
            continue;
        for(uint32_t x = i*i; x < PRIMES; x += i)
            R[x] = false;
        P.push_back(i);
    }
    uint32_t n;
    cin >> n;
    static array<uint32_t, PRIMES> T;
    set<uint32_t> O;
    uint64_t r = 1;
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
                uint32_t c = 1, p2 = p*p, p4=p2*p2; a /= p;
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
        if(a > 1 and O.find(a) == O.end())
            r = (r * 2) % LIM, O.insert(a);
    }
    for(uint32_t i = 0; i < PRIMES; i++)
        if(R[i] and T[i] > 0)
            r = (r * ((uint64_t)T[i]+1llu)) % LIM;
    cout << (r + LIM - (uint64_t)n) % LIM;
}
