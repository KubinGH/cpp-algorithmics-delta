#include <bits/stdc++.h>

using namespace std;

template<typename T, typename Fun>
struct sparse_table
{
    Fun F;
    size_t n;
    vector<vector<T>> A;
    template<typename It>
    sparse_table(It first, It last)
    {
        n = distance(first, last);
        A.emplace_back(first, last);
        for(size_t i = 1; (1u << i) <= n; i++)
        {
            A.emplace_back(n - (1u << i) + 1);
            for(size_t j = 0; j + (1 << i) <= n; j++)
                A[i][j] = F(A[i-1][j], A[i-1][j + (1u << (i-1))]);
        }
    }
    T operator() (size_t a, size_t b) const
    {
        size_t p = __lg(b - a);
        return F(A[p][a], A[p][b - (1 << p)]);
    }
};

template<typename T>
struct max_f { T operator() (const T& a, const T& b) const { return max(a, b); } };

using rmq_table = sparse_table<size_t, max_f<size_t>>;
using rmq_pos_table = sparse_table<pair<int, size_t>, max_f<pair<int, size_t>>>;

uint64_t divide_et_impera(
    size_t a, size_t b,
    const vector<size_t>& unique_stop,
    const rmq_pos_table& rmq, int k, bool stronk)
{
    if(a == b)
        return 0;

    auto [x, c] = rmq(a, b);
    if(stronk)
        c = ~c;

    uint64_t result = 0;
    if(b-c < c-a+1 or (b-c == c-a+1 and stronk))
    {
        for(size_t j = c; j < b; j++)
        {
            size_t i_lo = max(a, unique_stop[j]);
            size_t i_hi = min(c, k+j+1 >= x+a ? k+j+1-x : 0);
            if(i_lo <= i_hi)
                result += i_hi - i_lo + 1;
        }
    }

    result += divide_et_impera(a, c, unique_stop, rmq, k, stronk)
            + divide_et_impera(c+1, b, unique_stop, rmq, k, stronk);

    return result;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t cases;
    cin >> cases;

    while(cases --> 0)
    {
        size_t n; int k;
        cin >> n >> k;

        vector<int> A(n+1);
        for(size_t i = 1; i <= n; i++)
            cin >> A[i];


        uint64_t result = 0;

        for(size_t tr = 0; tr < 2; tr++)
        {
            vector<pair<int, size_t>> elem(n+1);
            vector<size_t> last(n+1), prev(n+1);
            for(size_t i = 1; i <= n; i++)
            {
                auto a = A[i];
                prev[i] = last[a];
                last[a] = i;
                elem[i] = {a, tr ? ~i : i};
            }

            rmq_table P(prev.begin(), prev.end());
            vector<size_t> unique_stop(n+1);

            for(size_t i = 1; i <= n; i++)
            {
                size_t lo = 0, hi = i+1;
                while(lo < hi)
                {
                    auto mid = (lo + hi) / 2;
                    if(P(mid, i+1) < mid)
                        hi = mid;
                    else
                        lo = mid+1;
                }
                unique_stop[i] = lo;
            }

            rmq_pos_table rmq(elem.begin(), elem.end());

            result += divide_et_impera(1, n+1, unique_stop, rmq, k, tr);

            reverse(A.begin() + 1, A.end());
        }

        cout << result << endl;
    }
}
