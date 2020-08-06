#include <bits/stdc++.h>

using namespace std;

template<typename T, typename BinaryOperation>
struct sparse_table
{
    struct _identity { T operator() (const T& x) const { return x; } };
    BinaryOperation F;
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator>
    sparse_table(Iterator first, Iterator last, BinaryOperation f = {}) : F(f)
    {
        n = distance(first, last);
        A.emplace_back(distance(first, last));
        for(size_t i = 0; first != last; first++, i++)
            A[0][i] = *first;
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
struct min_f { T operator() (const T& a, const T& b) const { return min(a, b); } };
using min_table = sparse_table<int64_t, min_f<int64_t>>;
template<typename T>
struct max_f { T operator() (const T& a, const T& b) const { return max(a, b); } };
using max_table = sparse_table<int64_t, max_f<int64_t>>;

vector<size_t> parent, preorder, postorder;
vector<vector<size_t>> children;
vector<int> value;
vector<int64_t> path_value;

size_t watch = 0;
void dfs(size_t u, int64_t x = 0)
{
    preorder[u] = watch;
    if(children[u].empty())
        path_value.push_back(x), watch++;
    for(auto v : children[u])
        dfs(v, x + value[v]);
    postorder[u] = watch;
}

vector<bool> done;
vector<tuple<int64_t, int64_t, int64_t>> cache;

template<typename T, typename F>
T predicate_search(T lo, T hi, F f)
{
    while(lo < hi)
    {
        auto mid = lo + (hi-lo)/2;
        if(f(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

tuple<int64_t, int64_t, int64_t> solve(size_t u)
{
    if(done[u])
        return cache[u];
    if(children[u].empty())
        return cache[u] = make_tuple(path_value[preorder[u]], path_value[preorder[u]], int64_t(0));

    int64_t A = INT64_MAX, B = INT64_MIN;
    for(auto v : children[u])
    {
        int64_t a, b, c;
        tie(a, b, c) = solve(v);
        A = min(a, A);
        B = max(b, B);
    }
    B++;
    auto f = [&](int64_t x) {
        int64_t r = 0;
        for(auto v : children[u])
        {
            int64_t a, b, c;
            tie(a, b, c) = cache[v];
            r += c + max(max(a - x, x - b), int64_t(0));
        }
        return r;
    };

    int64_t a = predicate_search(A, B, [&](int64_t x) {
        return f(x) <= f(x+1);
    });
    int64_t b = predicate_search(a, B, [&](int64_t x) {
        return f(x) <  f(x+1);
    });

    done[u] = true;
    return cache[u] = make_tuple(a, b, f(a));
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    parent.resize(n); children.resize(n);
    preorder.resize(n); postorder.resize(n);
    value.resize(n); path_value.reserve(n);

    for(size_t i = 1; i < n; i++)
    {
        cin >> parent[i] >> value[i];
        children[parent[i]].push_back(i);
    }

    dfs(0);

    done.resize(n);
    cache.resize(n);

    cout << get<2>(solve(0)) << endl;
}
