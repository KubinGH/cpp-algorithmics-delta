#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 8192;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static bool mov[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> mov[i];
    int32_t gx, gy;
    cin >> gx >> gy;
    vector<pair<uint32_t, uint32_t>> G;
    G.emplace_back(gx, gy);
    int32_t x = 0, y = 0; uint32_t d = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(mov[i] == 0)
        {
            if(d == 0)      y++;
            else if(d == 1) x++;
            else if(d == 2) y--;
            else if(d == 3) x--;
        }
        else
        {
            uint32_t g = G.size();
            if(d%2 == 0)
            {
                for(uint32_t i = 0; i < g; i++)
                    G.emplace_back(x - G[i].first, G[i].second);
            }
            else
            {
                for(uint32_t i = 0; i < g; i++)
                    G.emplace_back(G[i].first, y - G[i].second);
            }
            d++;
        }
    }
    if(find(G.begin(), G.end(), pair<uint32_t, uint32_t>{x, y}) != G.end())
        cout << "TAK";
    else
        cout << "NIE";
}
