#include <algorithm>
#include <iostream>
#include <climits>
#include <numeric>
#include <vector>

using namespace std;

template<typename T, typename ChildrenOp>
struct segment_tree
{
    size_t w;
    vector<T> values;
    ChildrenOp F;
    segment_tree(size_t n) : w(1 << __lg(2*n-1)), values(2*w, identity_element(F)) {}
    template<typename It>
    segment_tree(It first, It last) : segment_tree(distance(first, last))
    {
        copy(first, last, values.begin() + w);
        for(size_t i = w; i --> 1; )
            values[i] = F(values[2*i], values[2*i+1]);
    }
    T operator() (size_t L, size_t R) const
    {
        T result = identity_element(F);
        for(L += w, R += w; L < R; L /= 2, R /= 2)
        {
            if(L % 2) result = F(result, values[L++]);
            if(R % 2) result = F(result, values[--R]);
        }
        return result;
    }
};


template<typename T>
struct min_f { T operator() (const T& x, const T& y) const { return min(x, y); } };
template<typename T>
struct max_f { T operator() (const T& x, const T& y) const { return max(x, y); } };

int64_t identity_element(min_f<int64_t>) { return INT64_MAX; }
int64_t identity_element(max_f<int64_t>) { return INT64_MIN; }
using posval = pair<int, size_t>;
posval identity_element(max_f<posval>) { return posval{INT_MIN, 0}; }

using min_table = segment_tree<int64_t, min_f<int64_t>>;
using max_table = segment_tree<int64_t, max_f<int64_t>>;
using max_pos_table = segment_tree<posval, max_f<posval>>;

using frac = pair<int64_t, int>;

bool frac_cmp(const frac& lhs, const frac& rhs)
{
    return (long double) lhs.first / lhs.second < (long double) rhs.first / rhs.second;
}

void divide_et_impera(
    size_t a, size_t b, vector<int64_t>& S,
    const min_table& minS, const max_table& maxS, const max_pos_table& maxA,
    pair<int64_t, int>& out)
{
    if(a == b)
        return;
    auto mx = maxA(a, b).first;
    int64_t best = mx > 0 ? INT64_MIN : INT64_MAX;
    size_t p = a;
    while(p < b)
    {
        auto local_max = maxA(p, b);
        if(local_max.first == mx)
        {
            auto i = ~local_max.second;
            if(mx > 0)  best = max(best, maxS(i+1, b+1) - minS(a, i+1));
            else        best = min(best, minS(i+1, b+1) - maxS(a, i+1));
            divide_et_impera(p, i, S, minS, maxS, maxA, out);
            p = i + 1;
        }
        else
        {
            divide_et_impera(p, b, S, minS, maxS, maxA, out);
            p = b;
        }
    }

    if(mx < 0) best = -best, mx = -mx;
    out = max(out, frac{best, mx}, frac_cmp);
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    vector<int64_t> S(n+1);
    for(size_t i = 0; i < n; i++)
        S[i+1] = S[i] + A[i];

    vector<pair<int, size_t>> pA(n);
    for(size_t i = 0; i < n; i++)
        pA[i] = {A[i], ~i};

    min_table minS(S.begin(), S.end());
    max_table maxS(S.begin(), S.end());
    max_pos_table maxA(pA.begin(), pA.end());

    pair<int64_t, int> result = {0, 1};
    divide_et_impera(0, n, S, minS, maxS, maxA, result);
    int64_t x = result.first, y = result.second;

    auto g = gcd(x, y);
    x /= g; y /= g;

    cout << x << "/" << y;
}
