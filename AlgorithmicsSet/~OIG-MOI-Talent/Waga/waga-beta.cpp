#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, l, p;
    cin >> n >> l >> p;

    const size_t m = l + p;
    vector<vector<int>> choiceset(m, vector<int>(n));
    int sum = 0, asum = 0;
    for(size_t i = 0; i < m; i++)
    {
        auto& ch = choiceset[i];
        for(size_t j = 0; j < n; j++)
        {
            cin >> ch[j];
            if(i >= l)
                ch[j] = -ch[j];
            sum += ch[j];
            asum += abs(ch[j]);
        }
        partial_sum(ch.rbegin(), ch.rend(), ch.rbegin());
    }

    const int MAX = asum+32;
    vector<size_t> cost_map(2*MAX + 1, SIZE_MAX/2), cost_map_prev = cost_map;

    #define cost(k) cost_map[size_t((k) + MAX)]
    #define cost1(k) cost_map_prev[size_t((k) + MAX)]

    cost(0) = 0;

    for(size_t i = 0; i < m; i++)
    {
        copy(cost_map.begin(), cost_map.end(), cost_map_prev.begin());
        cost_map_prev = cost_map;
        for(size_t j = 0; j < n; j++)
        {
            int y = choiceset[i][j];
            if(y < 0)
            {
                for(int x = -MAX - y; x < MAX; x++)
                    cost(x + y) = min(cost(x + y), cost1(x) + n-j);
            }
            else if(y > 0)
            {
                for(int x = MAX - y; x --> -MAX; )
                    cost(x + y) = min(cost(x + y), cost1(x) + n-j);
            }
        }
    }

    cout << cost(sum);
}
