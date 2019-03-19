#include <bits/stdc++.h>
#define note(__x) #__x << " = " << __x

using namespace std;

template<typename T, size_t D>
struct vector_tag
{
    using type = vector<typename vector_tag<T, D - 1>::type>;
};

template<typename T>
struct vector_tag<T, 0>
{
    using type = T;
};

template<typename T>
vector<T> make_vector(size_t n)
{
    return vector<T>(n);
}

template<
    typename T, typename... Args,
    typename Result = typename vector_tag<T, sizeof...(Args) + 1>::type
>
Result make_vector(size_t n, Args... args)
{
    return Result(n, make_vector<T>(args...));
}

bool pattern_ok(uint32_t word)
{
    return (word & (word >> 1)) == 0;
}

int main()
{
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint32_t n;
        cin >> n;
        auto A = make_vector<uint32_t>(n, n);
        vector<uint32_t> patterns;
        for(uint32_t p = 0; p < (1u << n); p++)
            if(pattern_ok(p))
                patterns.push_back(p);
        cerr << note(patterns.size()) << endl;

        vector<vector<uint32_t>> patterns_coll(1u << n);
        for(auto p : patterns)
            for(auto q : patterns)
                if((p & q) == 0 and pattern_ok(p | q))
                    patterns_coll[p].push_back(q);

        for(uint32_t y = 0; y < n; y++)
            for(uint32_t x = 0; x < n; x++)
                cin >> A[y][x];

        auto Q = make_vector<uint32_t>(n, 1u << n);

        auto sum_row_subset = [&](uint32_t y, uint32_t p) {
            uint32_t s = 0;
            for(uint32_t x = 0; x < n; x++, p >>= 1)
                if(p & 1)
                    s += A[y][x];
            return s;
        };

        for(auto p : patterns)
            Q[0][p] = sum_row_subset(0, p);

        for(uint32_t y = 1; y < n; y++)
          for(auto p : patterns)
        {
            uint32_t z = 0;
            for(auto q : patterns_coll[p])
                z = max(z, Q[y-1][q]);
            Q[y][p] = z + sum_row_subset(y, p);
        }

        cout << *max_element(Q.back().begin(), Q.back().end()) << endl;

    }
}
