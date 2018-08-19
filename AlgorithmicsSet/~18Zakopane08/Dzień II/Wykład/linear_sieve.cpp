#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e7;

// x = i * p_i
// p_i -> najmniejszy dzielnik pierwszy x

// 2: prime.push_back(2)
// 3: prime.push_back(3), (2, 3) - composite (6, 9)

bitset<MAX> is_composite;
void linear_sieve(uint32_t n)
{
    is_composite.reset();

}
