#include <bits/stdc++.h>

using namespace std;

const size_t N = 1024;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t h, w;
    cin >> h >> w;

    static array<array<bool, N>, N> lock = {};
    size_t sy = 0, sx = 0, fy = 0, fx = 0;

    for(size_t y = 0; y <= h+1; y++)
        for(size_t x = 0; x <= w+1; x++)
            lock[y][x] = true;
    for(size_t y = 1; y <= h; y++)
    {
        string row;
        cin >> row;
        for(size_t x = 1; x <= w; x++)
        {
            auto c = row[x-1];
            lock[y][x] = c == '#';
            if(c == 'S')
                sy = y, sx = x;
            if(c == 'C')
                fy = y, fx = x;
        }
    }

    queue<pair<size_t, size_t>> que;
    static array<array<int, N>, N> wall_dist = {};
    auto wall_maybe = [&](size_t y, size_t x, int d) {
        if(d < wall_dist[y][x])
            wall_dist[y][x] = d, que.emplace(y, x);
    };
    for(size_t y = 0; y <= h+1; y++)
      for(size_t x = 0; x <= w+1; x++)
    {
        wall_dist[y][x] = w*h;
        if(lock[y][x])
            wall_maybe(y, x, 0);
    }

    while(not que.empty())
    {
        auto [y, x] = que.front(); que.pop();
        auto d = wall_dist[y][x] + 1;
        if(y) wall_maybe(y - 1, x, d);
        if(x) wall_maybe(y, x - 1, d);
        if(y<=h) wall_maybe(y + 1, x, d);
        if(x<=w) wall_maybe(y, x + 1, d);
    }

    /*
    for(size_t y = 0; y <= h+1; y++, cout << endl)
        for(size_t x = 0; x <= w+1; x++, cout << ' ')
            cout << wall_dist[y][x];
    */

    static array<array<array<size_t, 4>, N>, N> towards;
    constexpr size_t UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
    for(size_t y = 0; y <= h+1; y++)
        for(size_t x = 0; x <= w+1; x++)
            towards[y][x].fill(SIZE_MAX);

    for(size_t y = 1; y <= h; y++)
        for(size_t x = 1; x <= w; x++)
            if(not lock[y][x])
                towards[y][x][UP] = towards[y-1][x][UP] == SIZE_MAX ? y : towards[y-1][x][UP],
                towards[y][x][LEFT] = towards[y][x-1][LEFT] == SIZE_MAX ? x : towards[y][x-1][LEFT];
    for(size_t y = h+1; y --> 1; )
        for(size_t x = w+1; x --> 1; )
            if(not lock[y][x])
                towards[y][x][DOWN] = towards[y+1][x][DOWN] == SIZE_MAX ? y : towards[y+1][x][DOWN],
                towards[y][x][RIGHT] = towards[y][x+1][RIGHT] == SIZE_MAX ? x : towards[y][x+1][RIGHT];
    /*
    cout << "UP" << endl;
    for(size_t y = 0; y <= h+1; y++, cout << endl)
        for(size_t x = 0; x <= w+1; x++, cout << ' ')
            cout << (towards[y][x][UP]==SIZE_MAX ? "#" : to_string(towards[y][x][UP]));
    cout << "LEFT" << endl;
    for(size_t y = 0; y <= h+1; y++, cout << endl)
        for(size_t x = 0; x <= w+1; x++, cout << ' ')
            cout << (towards[y][x][LEFT]==SIZE_MAX ? "#" : to_string(towards[y][x][LEFT]));
    cout << "DOWN" << endl;
    for(size_t y = 0; y <= h+1; y++, cout << endl)
        for(size_t x = 0; x <= w+1; x++, cout << ' ')
            cout << (towards[y][x][DOWN]==SIZE_MAX ? "#" : to_string(towards[y][x][DOWN]));
    cout << "RIGHT" << endl;
    for(size_t y = 0; y <= h+1; y++, cout << endl)
        for(size_t x = 0; x <= w+1; x++, cout << ' ')
            cout << (towards[y][x][RIGHT]==SIZE_MAX ? "#" : to_string(towards[y][x][RIGHT]));
    */

    static array<array<int, N>, N> dist = {};
    for(size_t y = 0; y <= h+1; y++)
        for(size_t x = 0; x <= w+1; x++)
            dist[y][x] = w*h + lock[y][x];

    min_heap<tuple<int, size_t, size_t>> heap;
    static array<array<bool, N>, N> vis = {};
    auto maybe = [&](size_t y, size_t x, int d) {
        if(not lock[y][x] and d < dist[y][x])
            heap.emplace(dist[y][x] = d, y, x);
    };
    maybe(sy, sx, 0);
    while(not heap.empty())
    {
        auto [_, y, x] = heap.top(); heap.pop();
        if(vis[y][x])
            continue;
        vis[y][x] = true;
        auto d = dist[y][x], c = wall_dist[y][x];
        // cout << y << ", " << x << ": " << d << "/" << c << endl;
        maybe(y - 1, x, d + 1); maybe(y, x - 1, d + 1);
        maybe(y + 1, x, d + 1); maybe(y, x + 1, d + 1);
        maybe(towards[y][x][UP], x, d + c);
        maybe(towards[y][x][DOWN], x, d + c);
        maybe(y, towards[y][x][LEFT], d + c);
        maybe(y, towards[y][x][RIGHT], d + c);
    }
    /*
    for(size_t y = 0; y <= h+1; y++, cout << endl)
        for(size_t x = 0; x <= w+1; x++, cout << ' ')
            cout << (dist[y][x]>=w*h ? "#" : to_string(dist[y][x]));
    */

    cout << dist[fy][fx] << endl;
}
