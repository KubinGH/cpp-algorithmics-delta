#include <bits/stdc++.h>

using namespace std;

const size_t N = 30;

template<typename T, typename Iterator>
multimap<T, uint32_t> sum_combinations(Iterator itbegin, Iterator itend)
{
    multimap<T, uint32_t> result;
    uint32_t n = distance(itbegin, itend);
    for(uint32_t mask = 0; mask < (1u << n); mask++)
    {
        uint32_t i = 0;
        T current = 0;
        for(Iterator it = itbegin; it != itend; it++, i++)
        {
            if(mask & (1 << i))
                current += *it;
        }
        if(is_same<T, float>::value or is_same<T, double>::value or is_same<T, long double>::value)
            current = round(current * 1e6) / 1e6;
        result.emplace(current, mask);
    }
    return result;
}

int main()
{
    cout << fixed << setprecision(3);
    double A[50];
    for(uint32_t i = 0; i < N; i++)
    {
        A[i] = (double)1.0L / static_cast<double>(i + 1);
    }
    auto L = sum_combinations<double>(A, A + N/2);
    auto R = sum_combinations<double>(A + N/2, A + N);
    uint64_t U = 0;
    for(auto l : L)
    {
        if(l.first > 1)
            break;
        auto rng = R.equal_range(1.0 - l.first);
        for(auto it = rng.first; it != rng.second; it++)
        {
            auto r = *it;
            cout << l.first << " " << r.first << " " << bitset<32>(l.second) << " " << bitset<32>(r.second) << endl;
            //for(uint32_t i = 0; i < N/2; i++)
            //    if(l.second & (1u << i))
            //        { /*cerr << i+1 << " ",*/ U[i] = true; }
            //for(uint32_t i = 0; i < N/2; i++)
            //    if(r.second & (1u << i))
            //        { /*cerr << N/2+i+1 << " ",*/ U[N/2+i] = true; }
            //cerr << endl;
            U |= l.second;
            U |= r.second << (N/2);
        }
    }
    for(uint64_t i = 0; i < 50; i++)
        if(U & (1llu << i))
            cout << i+1 << ", ";
}
