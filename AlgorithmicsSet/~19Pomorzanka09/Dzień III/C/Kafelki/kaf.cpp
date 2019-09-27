#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

const uint64_t MOD = 1e9 + 7;

uint64_t f(size_t n, uint64_t a, uint64_t b)
{
    for(size_t i = 0; i < n; i++)
        tie(a, b) = make_pair(b, (4*MOD + 4*b - a) % MOD);
    return a;
}

int main()
{
    size_t n;
    cin >> n;
    cout << (n % 2 ? 0 : f(n / 2, 1, 3));
}
