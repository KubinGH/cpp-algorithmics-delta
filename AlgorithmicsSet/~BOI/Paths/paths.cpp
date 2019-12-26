#include <bits/stdc++.h>

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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;

    vector<uint32_t> K(n);
    for(auto& x : K) cin >> x, x--;

    vector<vector<uint32_t>> G(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    auto R = make_vector<uint64_t>(1u << k, n);

    uint64_t result = 0;

    for(uint32_t u = 0; u < n; u++)
        R[1u << K[u]][u]++;

    for(uint32_t p = 0; p < (1u << k); p++)
      for(uint32_t u = 0; u < n; result += R[p][u], u++)
        for(uint32_t v : G[u])
    {
        uint32_t k1 = 1u << K[v];
        if(p & k1)
            continue;
        R[p | k1][v] += R[p][u];
    }

    cout << result - n;
}
