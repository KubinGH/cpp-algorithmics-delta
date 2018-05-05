#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 40;

template<typename Iterator>
unordered_map<uint32_t, uint32_t> sum_combinations(Iterator itbegin, Iterator itend)
{
    unordered_map<uint32_t, uint32_t> result;
    uint32_t n = distance(itbegin, itend);
    for(uint32_t mask = 0; mask < (1u << n); mask++)
    {
        uint32_t i = 0, current = 0;
        for(Iterator it = itbegin; it != itend; it++, i++)
        {
            if(mask & (1 << i))
                current += *it;
        }
        result[current] = mask;
    }
    return result;
}

void output_binary(uint32_t n, uint32_t bits)
{
    for(uint32_t i = 0; i < bits; i++)
        cout << bool(n & (1u << i));
}

int main()
{
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    uint32_t S;
    cin >> S;
    if(n <= 20)
    {
        for(auto c : sum_combinations(A.begin(), A.begin() + n))
        {
            if(c.first == S)
            {
                output_binary(c.second, n);
                return 0;
            }
        }
    }
    else
    {
        auto R = sum_combinations(A.begin() + n/2, A.begin() + n);
        for(uint32_t mask = 0; mask < (1u << (n/2)); mask++)
        {
            uint32_t current = 0;
            for(uint32_t i = 0; i < n/2; i++)
            {
                if(mask & (1 << i))
                    current += A[i];
            }
            auto it = R.find(S - current);
            if(it != R.end())
            {
                output_binary(mask, n/2);
                output_binary(it->second, n-n/2);
                return 0;
            }
        }
/*
        auto L = sum_combinations(A.begin(), A.begin() + n/2);
        auto R = sum_combinations(A.begin() + n/2, A.begin() + n);
        for(pair<uint32_t, uint32_t> c : L)
        {
            auto it = R.find(S - c.first);
            if(it != R.end())
            {
                output_binary(c.second, n/2);
                output_binary(it->second, n-n/2);
                return 0;
            }
        }
*/
    }
    return 1;
}
