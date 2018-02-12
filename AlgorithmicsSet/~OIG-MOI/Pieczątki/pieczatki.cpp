#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100, MAXP = 10;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w;
    cin >> h >> w;
    static array<bitset<MAX>, MAX> F;
    uint32_t to_fill = 0;
    for(uint32_t y = 0; y < h; y++) for(uint32_t x = 0; x < w; x++)
    {
        char c;
        cin >> c;
        F[y][x] = c == '#';
        if(c == '#')
            to_fill++;
    }
    static array<bitset<MAX>, MAX> D;
    uint32_t p;
    cin >> p;
    for(uint32_t pi = 0; pi < p; pi++)
    {
        static array<bitset<MAXP>, MAXP> L;
        uint32_t lh, lw;
        cin >> lh >> lw;
        bool any_full = false;
        for(uint32_t y = 0; y < lh; y++) for(uint32_t x = 0; x < lw; x++)
        {
            char c;
            cin >> c;
            L[y][x] = c == '#';
            if(L[y][x])
                any_full = true;
        }
        if(not any_full)
            continue;
        static array<bitset<MAXP>, MAXP> P;
        pair<uint32_t, uint32_t> topleft(lw-1, lh-1), botright(0, 0);
        for(uint32_t y = 0; y < lh; y++) for(uint32_t x = 0; x < lw; x++)
        {
            if(L[y][x])
            {
                topleft.first = min(x, topleft.first);
                topleft.second = min(y, topleft.second);
                botright.first = max(x, botright.first);
                botright.second = max(y, botright.second);
            }
        }
        uint32_t pw = botright.first - topleft.first + 1,
                 ph = botright.second - topleft.second + 1;
        for(uint32_t y = topleft.second; y < botright.second+1; y++)
            for(uint32_t x = topleft.first; x < botright.first+1; x++)
                P[y-topleft.second][x-topleft.first] = L[y][x];
        for(uint32_t y = 0; y < h - ph + 1; y++)
        {
            for(uint32_t x = 0; x < w - pw + 1; x++)
            {
                bool ok = true;
                for(uint32_t py = 0; py < ph and ok; py++)
                {
                    for(uint32_t px = 0; px < pw; px++)
                    {
                        if(P[py][px] and not F[y+py][x+px])
                            ok = false;
                    }
                }
                if(not ok) continue;
                for(uint32_t py = 0; py < ph; py++)
                {
                    for(uint32_t px = 0; px < pw; px++)
                    {
                        if(P[py][px])
                        {
                            if(not D[y+py][x+px])
                                to_fill--;
                            D[y+py][x+px] = true;
                        }
                    }
                }
            }
        }
    }
    if(not to_fill)
        cout << "TAK";
    else
        cout << "NIE";
}
