#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

const size_t MAX = 312;

uint32_t longest_path(uint32_t n, vector<uint32_t> ingoing[MAX], uint32_t lock[4])
{
    static uint32_t result[MAX];
    fill(result, result + MAX, 0);
    uint32_t best = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(i == lock[0] or i == lock[1] or i == lock[2] or i == lock[3])
            continue;
        for(uint32_t j : ingoing[i])
            result[i] = max(result[i], result[j]);
        result[i]++;
        best = max(best, result[i]);
    }
    return best;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    static vector<uint32_t> ingoing[MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v;
        ingoing[v].push_back(u);
    }
    #define for_range(__i, __a, __b) for((__i) = (__a); (__i) < (__b); (__i)++)
    uint32_t result = -1u, lock[4] = {-1u, -1u, -1u, -1u};
    if(k == 1)
    {
        for_range(lock[0], 0, n)
            result = min(result, longest_path(n, ingoing, lock));
    }
    else if(k == 2)
    {
        for_range(lock[0], 0, n)
          for_range(lock[1], lock[0]+1, n)
            result = min(result, longest_path(n, ingoing, lock));
    }
    else if(k == 3)
    {
        for_range(lock[0], 0, n)
          for_range(lock[1], lock[0]+1, n)
            for_range(lock[2], lock[1]+1, n)
              result = min(result, longest_path(n, ingoing, lock));
    }
    else if(k == 4)
    {
        for_range(lock[0], 0, n)
          for_range(lock[1], lock[0]+1, n)
            for_range(lock[2], lock[1]+1, n)
              for_range(lock[3], lock[2]+1, n)
                result = min(result, longest_path(n, ingoing, lock));
    }
    cout << result;
}
