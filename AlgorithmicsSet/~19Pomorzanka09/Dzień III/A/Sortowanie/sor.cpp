#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;

    cin >> n;

    vector<size_t> V(2*n);
    for(size_t i = 0; i < 2*n; i++)
    {
        char c;
        cin >> c >> V[i]; V[i]--;
        if(c == 'B')
            V[i] += n;
    }

    vector<uint> index_of(2*n+1);
    vector<vector<uint>> count_lt(2*n+1, vector<uint>(2*n+1));

    for(size_t i = 0; i < 2*n; i++)
    {
        index_of[V[i]] = i;
        for(size_t v = 0; v <= 2*n; v++)
        {
            count_lt[i+1][v] = count_lt[i][v];
            if(V[i] < v)
                count_lt[i+1][v]++;
        }
    }

    auto move_cost = [&](size_t a, size_t b, size_t x) {
        auto index = index_of[x];
        auto missing = count_lt[index][a] + count_lt[index][n+b] - count_lt[index][n];

        return uint(index - missing);
    };

    vector<vector<uint>> cache(n+1, vector<uint>(n+1, UINT_MAX));
    function<uint(size_t, size_t)> solve = [&](size_t a, size_t b) {
        if(a == n and b == n)
            return 0u;
        if(cache[a][b] != UINT_MAX)
            return cache[a][b];
        uint result = UINT_MAX;
        if(a < n)
            result = min(result, solve(a+1, b) + move_cost(a, b, a));
        if(b < n)
            result = min(result, solve(a, b+1) + move_cost(a, b, n+b));
        return cache[a][b] = result;
    };

    cout << solve(0, 0);
}
