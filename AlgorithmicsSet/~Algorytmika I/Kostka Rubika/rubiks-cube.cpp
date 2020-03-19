#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <bitset>
#include <array>
#include <map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;
    uint expected;
    cin >> expected;

for(size_t antimask = 0; antimask < 64; antimask++) {
    array<array<array<int, 3>, 3>, 3> cube;
    for(size_t i = 0, z = 0; z < 3; z++)
        for(size_t y = 0; y < 3; y++)
            for(size_t x = 0; x < 3; x++, i++)
                cube[z][y][x] = i;

    auto front_wall = [&](size_t x, size_t y) -> int& {
        return cube[0][y][x];
    };
    auto  back_wall = [&](size_t x, size_t y) -> int& {
        return cube[2][y][x];
    };
    auto  left_wall = [&](size_t x, size_t y) -> int& {
        return cube[x][y][0];
    };
    auto right_wall = [&](size_t x, size_t y) -> int& {
        return cube[x][y][2];
    };
    auto    up_wall = [&](size_t x, size_t y) -> int& {
        return cube[y][0][x];
    };
    auto  down_wall = [&](size_t x, size_t y) -> int& {
        return cube[y][2][x];
    };
    map<char, function<int&(size_t, size_t)>> wall_fun = {
        {'F', front_wall}, {'B',  back_wall},
        {'L',  left_wall}, {'R', right_wall},
        {'U',    up_wall}, {'D',  down_wall}
    };
    map<char, bool> anti = {
        {'F', antimask>>0&1}, {'B', antimask>>1&1},
        {'L', antimask>>2&1}, {'R', antimask>>3&1},
        {'U', antimask>>4&1}, {'D', antimask>>5&1}
    };
    array<pair<size_t, size_t>, 8> borders = {{
        {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 2}, {0, 1}
    }};

    for(char c : S)
    {
        assert(wall_fun.count(c));
        auto fun = wall_fun[c];
        array<int, 8> values;
        size_t i;
        i = 0; for(auto [x, y] : borders) values[i++] = fun(x, y);
        rotate(values.begin(), values.begin() + (anti[c] ? 2 : 6), values.end());
        i = 0; for(auto [x, y] : borders) fun(x, y) = values[i++];
    }

    array<int, 27> F;

    for(size_t i = 0, z = 0; z < 3; z++)
        for(size_t y = 0; y < 3; y++)
            for(size_t x = 0; x < 3; x++, i++)
                F[i] = cube[z][y][x];

    array<bool, 27> vis = {};
    uint64_t cycle = 1;
    for(size_t i = 0; i < 27; i++)
    {
        if(vis[i]) continue;
        auto x = i; uint len = 0;
        do {
            len++;
            vis[x] = true;
            x = F[x];
        } while(x != i);
        cout << len << ' ';
        cycle = lcm(cycle, (uint64_t)len);
    }
    cout << endl;

    cout << bitset<6>(antimask) << ": ", cout << cycle << endl;
}
}
