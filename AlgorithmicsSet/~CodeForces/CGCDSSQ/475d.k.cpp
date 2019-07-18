// -*- ktl/structures/sparse_table.cpp -*-

#include <algorithm>
#include <cstddef>
#include <vector>
#include <cstdint>

using std::size_t;
using std::vector;
using std::__lg;

template<typename T, typename BinaryOperation>
struct sparse_table
{
    struct _identity { T operator() (const T& x) const { return x; } };
    BinaryOperation F;
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator, typename TransformOperation = _identity>
    sparse_table(Iterator first, Iterator last, BinaryOperation f = {},
                 TransformOperation t = {}) : F(f)
    {
        n = distance(first, last);
        A.emplace_back(distance(first, last));
        for(size_t i = 0; first != last; first++, i++)
            A[0][i] = t(*first);
        for(size_t i = 1; (1u << i) <= n; i++)
        {
            A.emplace_back(n - (1u << i) + 1);
            for(size_t j = 0; j + (1 << i) <= n; j++)
                A[i][j] = F(A[i-1][j], A[i-1][j + (1u << (i-1))]);
        }
    }
    T operator() (size_t a, size_t b)
    {
        size_t p = __lg(b - a);
        return F(A[p][a], A[p][b - (1 << p)]);
    }
};

// -$- ktl/structures/sparse_table.cpp -$-

// -*- ktl/general/binary_search.cpp -*-
#include <cstddef>
using std::size_t;

#define BINARY_SEARCH_BODY_COND(_Arg, _expr, _cond, _eps)    \
{                                   \
    while(_cond)                    \
    {                               \
        _Arg mid = (lo + hi) / 2;   \
        if(_expr)                   \
            hi = mid;               \
        else                        \
            lo = mid + _eps;        \
    }                               \
    return lo;                      \
}
#define BINARY_SEARCH_BODY(_Arg, _expr) BINARY_SEARCH_BODY_COND(_Arg, _expr, (lo < hi), 1)

// standard, iterator-based
template<typename T, typename Iterator>
Iterator q_lower_bound(Iterator lo, Iterator hi, T value)
{
    BINARY_SEARCH_BODY(Iterator, *mid >= value)
}
template<typename T, typename Iterator>
Iterator q_upper_bound(Iterator lo, Iterator hi, T value)
{
    BINARY_SEARCH_BODY(Iterator, *mid > value)
}

// generalized operation
template<typename Arg, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f)
{
    BINARY_SEARCH_BODY(Arg, f(mid))
}
template<typename Arg, typename Result>
Arg first_true(Arg lo, Arg hi, Result(*f)(Arg))
{
    BINARY_SEARCH_BODY(Arg, f(mid))
}

// generalized operation & epsilon
template<typename Arg, typename Result, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f, Arg epsilon)
{
    BINARY_SEARCH_BODY_COND(Arg, f(mid), (hi - lo > epsilon), epsilon)
}
template<typename Arg, typename Result>
Arg first_true(Arg lo, Arg hi, Result(*f)(Arg), Arg epsilon)
{
    BINARY_SEARCH_BODY_COND(Arg, f(mid), (hi - lo > epsilon), epsilon)
}

// -$- ktl/general/binary_search.cpp -$-

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;

struct gcd_op { uint operator() (uint a, uint b) { return __gcd(a, b); }};
using gcd_table = sparse_table<uint, gcd_op>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    vector<uint> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    gcd_table T(A.begin(), A.end());

    map<uint, uint64_t> counter;

    for(size_t start = 0; start < n; start++)
    {
        vector<pair<uint, size_t>> run;
        run.emplace_back(A[start], start);
        while(run.back().second + 1 < n and run.back().first > 1)
        {
            uint prev; size_t frag;
            tie(prev, frag) = run.back();
            size_t frag_stop = first_true(frag+1, n, [&] (size_t i) {
                return T(start, i) < prev;
            });
            run.emplace_back(T(start, frag_stop), frag_stop - 1);
        }
        size_t i = start;
        uint c = 0;
        for(auto p : run)
        {
            counter[c] += p.second - i;
            c = p.first; i = p.second;
        }
        counter[c] += n - i;
    }

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        uint x;
        cin >> x;
        cout << counter[x] << '\n';
    }
}
