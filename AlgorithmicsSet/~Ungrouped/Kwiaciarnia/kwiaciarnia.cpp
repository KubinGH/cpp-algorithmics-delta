#include <bits/stdc++.h>
#define MAX 100
#define MAXC 101
#define MAXC2 (MAXC*MAXC)
#define MAXC3 (MAXC*MAXC*MAXC)
#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MIN3(a, b, c) MIN((a), (MIN((b), (c))))

using namespace std;

struct colors_t
{
    uint16_t r, g, b;
    colors_t() { r = g = b = 0; }
    colors_t (uint16_t _r, uint16_t _g, uint16_t _b)
    {
        r = _r; g = _g; b = _b;
    }
    bool operator< (const colors_t& other) const
    {
        if(r == other.r)
            if(g == other.g)
                return b < other.b;
            else
                return g < other.g;
        else
            return r < other.r;
    }
};

const inline void setg(uint16_t* p, uint16_t v)
{
    if(v > *p) *p = v;
}

int main()
{
    colors_t M;
    cin >> M.r >> M.g >> M.b;
    uint16_t T;
    cin >> T;
    static colors_t S[MAX];
    for(uint16_t t = 0; t < T; t++)
    {
        cin >> S[t].r >> S[t].g >> S[t].b;
        if(S[t].r > M.r or S[t].g > M.g or S[t].b > M.b)
            t--; //erase
    }
    sort(S, S + T);
    static uint16_t U[MAXC][MAXC][MAXC];
    for(uint16_t t = 0; t < T; t++)
    {
        colors_t s = S[t];
        for(int16_t r = M.r; r >= s.r; r--)
            for(int16_t g = M.g; g >= s.g; g--)
                for(int16_t b = M.b; b >= s.b; b--)
                    setg(&U[r][g][b], U[r-s.r][g-s.g][b-s.b] + 1);
    }
    cout << U[M.r][M.g][M.b] << endl;
}
