#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 512;

typedef vector<pair<uint8_t, uint8_t>> vertex_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, h;
    cin >> h >> w;
    static bitset<MAX> type[MAX];
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
    {
        char c;
        cin >> c;
        type[y][x] = (c == 'N');
    }
    queue<pair<vertex_t, uint8_t>> Q;
    vertex_t start_vertex(h);
    for(uint32_t i = 0; i < h; i++)
        start_vertex[i] = {0, w};
    set<vertex_t> S;
    S.insert(start_vertex);
    Q.emplace(start_vertex, 0);
    static uint32_t R[MAX][MAX];
    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 0; x < w; x++)
            R[y][x] = -1u;
    while(not Q.empty())
    {
        vertex_t c = Q.front().first; uint32_t cd = Q.front().second; Q.pop();
        //cout << endl << cd << endl;
        for(uint32_t y = 0; y < h; y++)
        {
            uint32_t x1 = c[y].first, x2 = c[y].second;
            //cout << x1 << ".." << x2 << endl;
            if(x1 == x2) continue;
            if(type[y][x1] == 0)
            {
                if(y == 0 or not (c[y-1].first <= x1 and x1 < c[y-1].second))
                {
                    R[y][x1] = min(R[y][x1], cd+1);
                    vertex_t p = c;
                    p[y].first++;
                    if(S.find(p) == S.end())
                    {
                        Q.emplace(p, cd+1);
                        S.insert(p);
                    }
                }
            }
            else
            {
                if(y == h-1 or not (c[y+1].first <= x1 and x1 < c[y+1].second))
                {
                    R[y][x1] = min(R[y][x1], cd+1);
                    vertex_t p = c;
                    p[y].first++;
                    if(S.find(p) == S.end())
                    {
                        Q.emplace(p, cd+1);
                        S.insert(p);
                    }
                }
            }
            if(type[y][x2-1] == 0)
            {
                if(y == h-1 or not (c[y+1].first <= x2-1 and x2-1 < c[y+1].second))
                {
                    R[y][x2-1] = min(R[y][x2-1], cd+1);
                    vertex_t p = c;
                    p[y].second--;
                    if(S.find(p) == S.end())
                    {
                        Q.emplace(p, cd+1);
                        S.insert(p);
                    }
                }
            }
            else
            {
                if(y == 0 or not (c[y-1].first <= x2-1 and x2-1 < c[y-1].second))
                {
                    R[y][x2-1] = min(R[y][x2-1], cd+1);
                    vertex_t p = c;
                    p[y].second--;
                    if(S.find(p) == S.end())
                    {
                        Q.emplace(p, cd+1);
                        S.insert(p);
                    }
                }
            }
        }
    }
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
            cout << (R[y][x] == -1u ? int(-1) : int(2*R[y][x])) << " ";
        cout << endl;
    }
}
