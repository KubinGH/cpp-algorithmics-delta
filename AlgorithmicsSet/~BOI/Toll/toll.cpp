#include <bits/stdc++.h>

using namespace std;

constexpr size_t K = 5;
constexpr int oo = INT_MAX / 3 - 0xD;

using matrix = array<array<int, K>, K>;

matrix id()
{
    matrix A = {};
    for(size_t i = 0; i < K; i++)
        for(size_t j = 0; j < K; j++)
            A[i][j] = (i == j ? 0 : +oo);
    return A;
}
matrix full(int v)
{
    matrix A = {};
    for(size_t i = 0; i < K; i++)
        A[i].fill(v);
    return A;
}

matrix operator* (const matrix& A, const matrix& B)
{
    matrix C = full(+oo);
    for(size_t i = 0; i < K; i++)
        for(size_t j = 0; j < K; j++)
            for(size_t k = 0; k < K; k++)
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
    return C;
}
struct matmul { matrix operator() (const matrix& A, const matrix& B) const { return A * B; } };

template<typename T, typename BinaryAssociativeOp>
struct segment_tree
{
    const size_t w;
    const T id;
    vector<T> values;
    BinaryAssociativeOp f;

    segment_tree(size_t n, T v = {}) : w(1 << __lg(2*n-1)), id(v), values(2*w, v) {}

    void build()
    {
        for(size_t i = w; i --> 1; )
            values[i] = f(values[2*i], values[2*i+1]);
    }

    T get(size_t l, size_t r) const
    {
        T a = id, b = id;
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) a = f(a, values[l++]);
            if(r % 2) b = f(values[--r], b);
        }
        return f(a, b);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t k, n, m, q;
    cin >> k >> n >> m >> q;

    vector<vector<pair<size_t, int>>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    vector<matrix> T;
    for(size_t i = 0; i < n; i += k)
    {
        T.push_back(full(+oo));
        auto& t = T.back();
        for(size_t u = 0; u < k and i + u < n; u++)
            for(auto [v, w] : graph[i+u])
                t[u][v%k] = min(t[u][v%k], w);
    }
    segment_tree<matrix, matmul> tree(T.size(), id());
    for(size_t i = 0; i < T.size(); i++)
        tree.values[tree.w + i] = T[i];
    tree.build();

    auto query = [&](size_t u, size_t v) {
        auto t = tree.get(u/k, v/k);
        auto r = t[u%k][v%k];
        return r == +oo ? -1 : r;
    };

    while(q --> 0)
    {
        size_t u, v;
        cin >> u >> v;
        cout << query(u, v) << '\n';
    }
}
