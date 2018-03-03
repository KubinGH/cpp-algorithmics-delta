#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6 + 1;
const size_t MAX_SQRT = ceil(sqrt(MAX)) + 1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static bitset<MAX> P;
    vector<uint32_t> primes;
    P.set(); P[0] = false; P[1] = false;
    primes.push_back(2);
    for(uint32_t i = 4; i < MAX; i += 2)
        P[i] = false;
    for(uint32_t i = 3; i < MAX; i += 2)
    {
        if(not P[i])
            continue;
        if(i < MAX_SQRT) for(uint32_t x = i*i; x < MAX; x += i)
            P[x] = false;
        primes.push_back(i);
    }
    uint32_t n;
    cin >> n;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a, b;
        cin >> a >> b;
        auto hi = upper_bound(primes.begin(), primes.end(), b);
        auto lo = lower_bound(primes.begin(), primes.end(), a);
        if(*lo < a) lo++;
        cout << hi - lo << '\n';
    }
}
