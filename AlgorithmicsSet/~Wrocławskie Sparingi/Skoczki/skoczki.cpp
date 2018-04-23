#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

vector<uint64_t> prime_split(uint64_t k)
{
    vector<uint64_t> result;
    uint64_t q = floor(sqrt(k));
    for(uint64_t p = 2; p <= q; p++)
    {
        if(k % p == 0)
            result.push_back(1);
        while(k % p == 0)
            result.back() *= p, k /= p;
    }
    if(k != 1)
        result.push_back(k), k = 1;
    return result;
}

void create_cycle(array<uint64_t, MAX>& A, uint64_t f, uint64_t p)
{
    for(uint64_t i = f; i < f + p - 1; i++)
        A[i] = i+1;
    A[f+p-1] = f;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n, k;
    cin >> n >> k;
    vector<uint64_t> primes = prime_split(k);
    sort(primes.begin(), primes.end());
    uint64_t o = 0;
    for(uint64_t p : primes)
        o += p;
    if(o > n)
    {
        cout << "NIE";
        return 0;
    }
    static array<uint64_t, MAX> A;
    for(uint64_t i = 0; i < n - o; i++)
        A[i] = i;
    o = n - o;
    for(uint64_t p : primes)
    {
        create_cycle(A, o, p);
        o += p;
    }
    for(uint64_t i = 0; i < n; i++)
        cout << A[i]+1 << " ";
}
