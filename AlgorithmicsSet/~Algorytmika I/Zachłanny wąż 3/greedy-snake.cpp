#include <bits/stdc++.h>

using namespace std;

const size_t NAX = 64;
const int oo = 1e6;

int main()
{
    size_t h, w;
    cin >> h >> w;

    static int tvalue[NAX][NAX];
    fill(&tvalue[0][0], &tvalue[NAX-1][0], -oo);
    auto value = [&](size_t i, size_t j) -> int& {
        return tvalue[i+1][j+1];
    };
    for(size_t i = 0; i < h; i++)
    {
        string row;
        cin >> row;
        for(size_t j = 0; j < w; j++)
            value(i, j) = row[j] - '0';
    }

    const size_t n = max(w, h);

    static int tbest[2*NAX][NAX][NAX][NAX];
    fill(&tbest[0][0][0][0], &tbest[NAX-1][0][0][0], -oo);
    auto best = [&](size_t k, size_t a, size_t b, size_t c) -> int& {
        return tbest[k+1][a+1][b+1][c+1];
    };

    best(0, 0, 0, 0) = value(0, 0);
    for(size_t k = 1; k <= w+h-2; k++)
    {
        for(size_t a = 0; a < min(n, k+1); a++)
            for(size_t b = 0; b < min(n, k+1); b++)
                for(size_t c = 0; c < min(n, k+1); c++)
        {
            const size_t d = k-a, e = k-b, f = k-c;
            int gain = 0;
            gain += value(c, f);
            if(b != c)
                gain += value(b, e);
            if(a != b and a != c)
                gain += value(a, d);
            for(size_t mask = 0; mask < (1 << 3); mask++)
            {
                size_t p[3] = {mask&1, mask>>1&1, mask>>2&1};
                best(k, a, b, c) = max(best(k, a, b, c), best(k-1, a-p[0], b-p[1], c-p[2]));
            }
            best(k, a, b, c) += gain;
        }
    }

    cout << best(w+h-2, h-1, h-1, h-1);
}
