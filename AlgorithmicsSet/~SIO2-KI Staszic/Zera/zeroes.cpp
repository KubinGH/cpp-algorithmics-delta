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
    size_t n, m;
    cin >> n >> m;

    auto V = make_vector<int>(n+1, m+1, 16, 16, 2);
    auto Z = make_vector<bool>(n, m);
    auto A = make_vector<array<int, 2>>(n, m);

    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < m; j++)
    {
        int x;
        cin >> x;
        x = abs(x);
        if(not x) Z[i][j] = true;
        while(x % 2 == 0) x /= 2, A[i][j][0]++;
        while(x % 5 == 0) x /= 5, A[i][j][1]++;
    }

    for(size_t i = 0; i <= n; i++)
        for(size_t j = 0; j <= m; j++)
            for(size_t d = 0; d < 16; d++)
                V[i][j][d] = INT_MAX/3;

    for(size_t i = 0; i <= n; i++) V[i][0][0] = true;
    for(size_t i = 0; i <= m; i++) V[0][i][0] = true;

    for(size_t i = 0; i <= n; i++)
        for(size_t j = 0; j <= m; j++)
    {
        if(Z[i][j]) V[i+1][j+1][0] = 0;
        else for(size_t d = 0; d < 16; d++)
        {

        }
    }
}
