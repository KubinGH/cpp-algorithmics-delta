#include <bits/stdc++.h>
//#define TEST

using namespace std;

const size_t MAX = 1e5, MAX_E = 1e7+16;

mt19937 gen{random_device{}()};
template<typename T>
T randint(T a, T b) { return uniform_int_distribution<T>{a, b}(gen); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX];
    static unordered_map<uint32_t, uint32_t> I;
    static vector<uint32_t> P[MAX];
    static bitset<MAX_E> is_prime, exists;
    for(uint32_t i = 0; i < n; i++)
    {
#ifdef TEST
        A[i] = randint(1u, uint32_t(1e7));
        cerr << A[i] << " ";
#else
        cin >> A[i];
#endif
        I[A[i]] = i;
        exists[A[i]] = true;
    }
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    vector<uint32_t> uprimes;
    for(uint32_t i = 2; i < MAX_E; i++)
    {
        if(not is_prime[i])
            continue;
        bool pushed = false;
        for(uint32_t x = i; x < MAX_E; x += i)
        {
            is_prime[x] = false;
            if(exists[x])
            {
                P[I[x]].push_back(i);
                if(not pushed)
                    uprimes.push_back(i);
                pushed = true;
            }
        }
        is_prime[i] = true;
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

}
