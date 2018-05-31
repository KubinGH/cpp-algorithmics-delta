#include <bits/stdc++.h>
//#define TEST
//#define CHECK

using namespace std;

const size_t MAX = 1e5, MAX_E = 1e7+16;

mt19937 gen{random_device{}()};
template<typename T>
T randint(T a, T b) { return uniform_int_distribution<T>{a, b}(gen); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    gen.seed(time(0));
    uint32_t n;
    cin >> n;
#ifdef TEST
for(uint32_t _t = 0; _t < 1000; _t++)
{
#endif
    static uint32_t A[MAX];
    unordered_map<uint32_t, uint32_t> I;
    static vector<uint32_t> P[MAX];
    static bitset<MAX_E> is_prime, exists;
    for(uint32_t i = 0; i < n; i++)
    {
#ifdef TEST
        do { A[i] = randint(1u, uint32_t(1e7));
        } while(exists[A[i]]);
        cerr << A[i] << " ";
#else
        cin >> A[i];
#endif
        I[A[i]] = i;
        exists[A[i]] = true;
    }
#ifdef CHECK
    cout << endl;
    uint64_t _r = 0;
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = i+1; j < n; j++)
            _r += (__gcd(A[i], A[j]) == 1);
#endif
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for(uint32_t i = 2; i < MAX_E; i += 2)
    {
        if(not is_prime[i])
            continue;
        for(uint32_t x = i; x < MAX_E; x += i)
        {
            is_prime[x] = false;
            if(exists[x])
                P[I[x]].push_back(i);
        }
        if(i == 2)
            i--;
    }
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t p : P[i])
        {
            while(A[i] % p == 0)
                A[i] /= p;
            A[i] *= p;
        }
    }
    uint64_t r = 0;
    unordered_map<uint32_t, uint64_t> app;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t mask = 1; mask < (1u << P[i].size()); mask++)
        {
            uint32_t b = 1;
            for(uint32_t j = 0; j < P[i].size(); j++)
                if(mask & (1u << j))
                    b *= P[i][j];
            if(__builtin_popcount(mask) % 2 == 1)
                r += app[b];
            else
                r -= app[b];
            app[b]++;
        }
    }
    r = (uint64_t(n) * uint64_t(n - 1) / 2LLU) - r;
    cout << r;
#ifdef CHECK
    cout << endl << r << " " << _r << endl;
    assert(r == _r);
#endif
#ifdef TEST
    is_prime.reset(); exists.reset();
    for(uint32_t i = 0; i < n; i++)
        P[i].clear();
}
#endif
}
