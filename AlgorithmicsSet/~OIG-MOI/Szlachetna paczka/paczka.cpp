#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1000000000;

uint32_t lcm(uint32_t a, uint32_t b)
{
    return a / __gcd(a, b) * b;
}
uint32_t ceildiv(uint32_t a, uint32_t b)
{
    return (a + b - 1) / b;
}
uint32_t result_for_divisor(uint32_t p, uint32_t k, uint32_t d)
{
    return k / d - ceildiv(p, d) + 1;
}

int main()
{
    uint32_t p, k, j, s; char f;
    cin >> p >> k >> j >> s >> f;
    if(f == 'J')
        cout << result_for_divisor(p, k, j);
    else if(f == 'S')
        cout << result_for_divisor(p, k, j) - result_for_divisor(p, k, lcm(s, j));

}
