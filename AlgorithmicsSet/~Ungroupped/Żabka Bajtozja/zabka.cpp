#include <bits/stdc++.h>
#define MAX 1000
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define MANHATTAN(a, b) ABS(a.first - b.first) + ABS(a.second - b.second)
#define HYPOT(a, b) sqrt((a.first - b.first) * (a.first - b.first) + \
                         (a.second - b.second) * (a.second - b.second))

using namespace std;

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef long long int int64_t;
typedef pair<int64_t, int64_t> coor_t;

int64_t manhattan_cache[MAX];
map<coor_t, int64_t> manhattan_cache_m;

bool order_by_manhattan(coor_t a, coor_t b)
{
    return manhattan_cache_m[a] < manhattan_cache_m[b];
}

int main()
{
    uint16_t stones_n, start_i, i;
    int64_t jump_length;
    static coor_t stones[MAX];
    cin >> stones_n >> start_i >> jump_length; start_i--;
    for(i = 0; i < stones_n; i++)
    {
        int64_t x, y;
        cin >> x >> y;
        stones[i].first = x; stones[i].second = y;
    }
    coor_t start = stones[start_i];
    for(i = 0; i < stones_n; i++)
    {
        manhattan_cache[i] = MANHATTAN(start, stones[i]);
        manhattan_cache_m[stones[i]] = manhattan_cache[i];
    }
    sort(stones, stones + stones_n, order_by_manhattan);
    static bool can_go[MAX]; fill(can_go, can_go + MAX, false);
    can_go[start_i] = true;
    coor_t furthest; double furthest_dist = 0;
    queue<uint16_t> to_visit;
    to_visit.push(0);
    while(not to_visit.empty())
    {
        uint16_t c = to_visit.front(); to_visit.pop();
        coor_t current = stones[c];
        double to_start = HYPOT(current, start);
        if(to_start >= furthest_dist)
        {
            furthest = current;
            furthest_dist = to_start;
        }
        for(i = 0; i < stones_n; i++)
        {
            if(not can_go[i] and HYPOT(current, stones[i]) <= jump_length)
            {
                can_go[i] = true;
                to_visit.push(i);
            }
        }
    }
    cout << fixed << setprecision(3) << furthest_dist + jump_length;
}
