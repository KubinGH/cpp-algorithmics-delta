#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

typedef tuple<uint32_t, uint32_t, uint32_t> pos;

enum tile_t
{
    EMPTY, WALL, KEYWALL, STAIRS
};

tile_t A[2][MAX][MAX];
uint32_t h, w;

vector<uint32_t>
distances(uint32_t sx, uint32_t sy, uint32_t sb,
          vector<pos> goals, bool has_key)
{
    static bool visited[2][MAX][MAX];
    for(uint32_t b = 0; b < 2; b++) for(uint32_t y = 0; y < h; y++) for(uint32_t x = 0; x < w; x++)
        visited[b][y][x] = false;
    vector<uint32_t> result(goals.size(), -1u);
    queue<pair<pos, uint32_t>> Q;
    Q.emplace(pos(sx, sy, sb), 0);
    visited[sb][sy][sx] = true;
    auto func = [&](uint32_t nx, uint32_t ny, uint32_t nb, uint32_t d) {
        if(not visited[nb][ny][nx] and
           (A[nb][ny][nx] == EMPTY or A[nb][ny][nx] == STAIRS or
            (has_key and A[nb][ny][nx] == KEYWALL)))
        {
            Q.emplace(pos(nx, ny, nb), d + 1);
            visited[nb][ny][nx] = true;
        }
    };
    while(not Q.empty())
    {
        pos cp = Q.front().first; uint32_t d = Q.front().second; Q.pop();
        uint32_t x = get<0>(cp), y = get<1>(cp), b = get<2>(cp);
        //cout << x << ", " << y << ", " << b << " @ " << d << endl;
        for(uint32_t i = 0; i < goals.size(); i++)
            if(get<0>(goals[i]) == x and get<1>(goals[i]) == y and get<2>(goals[i]) == b)
                result[i] = d;
        if(x > 0) func(x - 1, y, b, d);
        if(y > 0) func(x, y - 1, b, d);
        if(x < w - 1) func(x + 1, y, b, d);
        if(y < h - 1) func(x, y + 1, b, d);
        if(A[b][y][x] == STAIRS) func(x, y, !b, d);
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> h >> w;
    uint32_t goal_x = 0, goal_y = 0, goal_b = 0,
             start_x = 0, start_y = 0, start_b = 0,
             key_x = 0, key_y = 0, key_b = 0;
    for(uint32_t b = 0; b < 2; b++)
    {
        for(uint32_t y = 0; y < h; y++) for(uint32_t x = 0; x < w; x++)
        {
            char c;
            cin >> c;
            if(c == '.')
                A[b][y][x] = EMPTY;
            else if(c == '#')
                A[b][y][x] = WALL;
            else if(c == '$')
                A[b][y][x] = KEYWALL;
            else if(c == '|')
                A[b][y][x] = STAIRS;
            else if(c == 'K')
                key_x = x, key_y = y, key_b = b;
            else if(c == 'X')
                goal_x = x, goal_y = y, goal_b = b;
            else if(c == 'P')
                start_x = x, start_y = y, start_b = b;
        }
    }
    //cout << "from start" << endl;
    vector<uint32_t> from_start = distances(
        start_x, start_y, start_b,
        {pos(key_x, key_y, key_b), pos(goal_x, goal_y, goal_b)}, false
    );
    uint32_t from_start_to_key = from_start[0],
             from_start_to_goal = from_start[1];
    //cout << "key: " << from_start_to_key << endl;
    //cout << "goal: " << from_start_to_goal << endl;
    uint32_t from_key_to_goal = -1u;
    if(from_start_to_key != -1u)
    {
        //cout << "from key" << endl;
        from_key_to_goal = distances(
            key_x, key_y, key_b,
            {pos(goal_x, goal_y, goal_b)}, true
        )[0];
        if(from_key_to_goal != -1u)
             from_key_to_goal += from_start_to_key + 1;
        //cout << "keygoal: " << from_key_to_goal << endl;
    }
    cout << (int)min(from_start_to_goal, from_key_to_goal);
}
