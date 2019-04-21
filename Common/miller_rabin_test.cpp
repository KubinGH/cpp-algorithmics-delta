#include <bits/stdc++.h>

#include "KTL/math/miller_rabin.cpp"

using namespace std;

const size_t TEST_RANGE = 1 << 23;
const size_t LOG_RANGE_LO = 1, LOG_RANGE_HI = 54, TESTS_PER_LOG = 50;

template<typename T>
bool sqrt_is_prime(T n)
{
    for(T d = 2; d * d <= n; d++)
        if(n % d == 0)
            return false;
    return true;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    auto ms = [start]() { return (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start)).count(); };
    cout << "@ " << start.time_since_epoch().count() << "ns" << endl;

    static bitset<TEST_RANGE> sieve;
    for(size_t i = 2; i * i < TEST_RANGE; i++)
        if(not sieve[i]) for(size_t x = i*i; x < TEST_RANGE; x += i)
            sieve[x] = true;
    cout << ms() << "ms" << endl;

    for(size_t i = 2; i < TEST_RANGE; i++)
    {
        if(i % 1000000 == 0) cout << "\r" << i << flush;
        if(is_prime(i) != not sieve[i])
        {
            cout << endl;
            cout << "!@#: " << i << " -> " << is_prime(i) << " /+ " << not sieve[i] << endl;
            abort();
        }
    }
    cout << "\r" << TEST_RANGE - 1 << endl;
    cout << ms() << "ms" << endl << endl;

    mt19937_64 gen(start.time_since_epoch().count());
    for(size_t g = LOG_RANGE_LO; g < LOG_RANGE_HI; g++)
    {
        cout << "\r" << "log = " << g << flush;
        for(size_t i = 0; i < TESTS_PER_LOG; i++)
        {
            uint64_t n = uniform_int_distribution<uint64_t>{1ull << g, (1ull << (g+1)) - 1}(gen);
            if(sqrt_is_prime(n) != is_prime(n))
            {
                cout << endl;
                cout << "!@#: " << n << " -> " << is_prime(i) << " /+ " << sqrt_is_prime(n) << endl;
                abort();
            }
        }
    }
    cout << endl << ms() << "ms" << endl;
}
