#include <bits/stdc++.h>

using namespace std;

map<string, uint32_t> m_initial = {
    {"POLNOC", 0}, {"WSCHOD", 1}, {"POLUDNIE", 2}, {"ZACHOD", 3},
};
map<string, uint32_t> m_turn = {
    {"LEWO", 0}, {"PRAWO", 1}
};
constexpr int32_t dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
map<pair<uint32_t, uint32_t>, pair<pair<uint32_t, uint32_t>, uint32_t>> m_start = {
    {{0, 0}, {{1, 0}, 0}}, {{0, 1}, {{0, 0}, 0}},
    {{1, 0}, {{0, 0}, 1}}, {{1, 1}, {{0, 1}, 1}},
    {{2, 0}, {{0, 1}, 2}}, {{2, 1}, {{1, 1}, 2}},
    {{3, 0}, {{1, 1}, 3}}, {{3, 1}, {{1, 0}, 3}}
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    string s_initial, s_turn;
    cin >> s_initial >> s_turn;
    uint32_t i_initial = m_initial[s_initial], i_turn = m_turn[s_turn];

    pair<uint32_t, uint32_t> ip;
    uint32_t ix, iy, d;
    tie(ip, d) = m_start[{i_initial, i_turn}];
    tie(ix, iy) = ip;

    uint32_t x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2; x1--; y1--;

    vector<vector<bool>> V(n, vector<bool>(n));
    vector<vector<uint32_t>> M(x2-x1, vector<uint32_t>(y2-y1));

    auto F = [&](uint32_t x, uint32_t y) {
        return x < n and y < n and not V[x][y];
    };
    auto T = [&](uint32_t x, uint32_t y, uint32_t i) {
        if(x1 <= x and x < x2 and y1 <= y and y < y2)
        {
            uint32_t mx = x-x1, my = (y2-y1-1)-(y-y1);
            M[mx][my] = i;
        }
    };

    uint32_t rep = 0;
    uint32_t cx = ix*(n-1), cy = iy*(n-1);
    V[cx][cy] = true; T(cx, cy, 1);
    for(uint32_t i = 2; rep < 2; i++)
    {
        if(F(cx+dx[d], cy+dy[d]))
        {
            rep = 0;
            cx += dx[d]; cy += dy[d];
            V[cx][cy] = true;
            T(cx, cy, i);
        }
        else
        {
            i--;
            rep++;
            if(i_turn)  d++, d %= 4;
            else        d--, d %= 4;
        }
    }

    for(uint32_t y = 0; y < y2-y1; y++, cout << endl)
        for(uint32_t x = 0; x < x2-x1; x++, cout << " ")
            cout << M[x][y];
}
