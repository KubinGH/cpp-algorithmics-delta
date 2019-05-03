#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

mt19937 gen{random_device{}()};
template<typename T>
T randint(T a, T b)
    { return uniform_int_distribution<T>{a, b}(gen); }

uint64_t now()
{
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count();
    return ms;
}

inline uint64_t f1(uint64_t x)
{
    return x % uint64_t(1e9 + 11);
}
inline uint64_t f2(uint64_t x)
{
    return x % uint64_t((1LLU << 31) - 1);
}
inline uint64_t f3(uint64_t x)
{
    x = (x >> 31) + (x & 2147483647);
    x = (x >> 31) + (x & 2147483647);
    return x == 2147483647 ? 0 : x;
}

int main()
{
    gen.seed(now());
    static uint64_t A[1 << 25];
    for(uint32_t i = 0; i < (1 << 25); i++)
        A[i] = randint(0LLU, UINT64_MAX);
    cout << "Begin tests" << endl;
    volatile uint64_t x;
    uint64_t before, after, ov;
    before = now();
    for(uint32_t i = 0; i < 16; i++) for(uint64_t a : A)
        x = a;
    after = now();
    cout << "headless: " << (ov = after - before) << "ms" << endl;
    before = now();
    for(uint32_t i = 0; i < 16; i++) for(uint64_t a : A)
        x = f1(a);
    after = now();
    cout << "1: " << after - before << "ms" << endl;
    before = now();
    for(uint32_t i = 0; i < 16; i++) for(uint64_t a : A)
        x = f2(a);
    after = now();
    cout << "2: " << after - before << "ms" << endl;
    before = now();
    for(uint32_t i = 0; i < 16; i++) for(uint64_t a : A)
        x = f3(a);
    after = now();
    cout << "3: " << after - before << "ms" << endl;
}
