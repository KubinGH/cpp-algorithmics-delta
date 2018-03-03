#include <bits/stdc++.h>
#define ADDIFNEW(ax, ay) \
    if(not visited[ay][ax] and open[ay][ax]) \
        visited[ay][ax] = true, S.emplace(ax, ay);

using namespace std;

const size_t MAX = 1000;

uint32_t c_next(uint32_t c, uint32_t n)
{
    return c < n - 1 ? c + 1 : 0;
}
uint32_t c_prev(uint32_t c, uint32_t n)
{
    return c > 0 ? c - 1 : n - 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<array<bool, MAX>, MAX> open, apple, visited;
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            char c;
            cin >> c;
            switch(c)
            {
                case '+':
                    apple[y][x] = true;
                case '.':
                    open[y][x] = true;
                    break;
            }
        }
    }
    uint32_t result = 0;
    for(uint32_t y = 0; y < n; y++) for(uint32_t x = 0; x < n; x++)
    {
        if(visited[y][x] or not open[y][x]) continue;
        stack<pair<uint32_t, uint32_t>> S;
        S.emplace(x, y);
        visited[y][x] = true;
        uint32_t current_count = 0;
        while(not S.empty())
        {
            pair<uint32_t, uint32_t> current = S.top(); S.pop();
            uint32_t cx = current.first, cy = current.second;
            if(apple[cy][cx])
                current_count++;
            ADDIFNEW(cx, c_next(cy, n));
            ADDIFNEW(cx, c_prev(cy, n));
            ADDIFNEW(c_next(cx, n), cy);
            ADDIFNEW(c_prev(cx, n), cy);
        }
        result = max(result, current_count);
    }
    cout << result;
}
