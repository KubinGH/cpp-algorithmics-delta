#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

mt19937_64 gen{random_device{}()};
template<typename T>
T randint(T a, T b)
    { return uniform_int_distribution<T>{a, b}(gen); }

uint64_t now()
{
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count();
    return ms;
}

int main()
{
    gen.seed(now());
    static uint64_t A[1 << 25];
    for(uint32_t i = 0; i < (1 << 25); i++)
        A[i] = randint(0LLU, UINT64_MAX);
    cout << "begin" << endl;
    volatile uint64_t x;
    for(uint32_t i = 0; i < 16; i++) for(uint64_t a : A)
        x = a;
    cout << "done" << endl;
}
