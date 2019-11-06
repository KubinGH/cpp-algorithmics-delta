#include <iostream>
#include <vector>

using namespace std;

struct partial_sums_2d
{
    vector<vector<int>> S;
    template<typename Fun>
    partial_sums_2d(size_t h, size_t w, Fun f)
    {
        S.emplace_back(w+1);
        for(size_t y = 1; y <= h; y++)
        {
            S.emplace_back(w+1);
            for(size_t x = 1; x <= w; x++)
                S[y][x] = S[y][x-1] + S[y-1][x] - S[y-1][x-1] + f(x-1, y-1);
        }
    }
    int operator()(size_t x1, size_t y1, size_t x2, size_t y2)
    {
        return S[y2][x2] + S[y1][x1] - S[y2][x1] - S[y1][x2];
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t h, w;
    cin >> h >> w;

    vector<vector<bool>> lock(h, vector<bool>(w));
    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
    {
        char c;
        cin >> c;
        lock[y][x] = (c == '#');
    }

    partial_sums_2d dominos_vertical(h, w, [&](size_t x, size_t y) {
        return (y and not lock[y][x] and not lock[y-1][x]);
    });
    partial_sums_2d dominos_horizontal(h, w, [&](size_t x, size_t y) {
        return (x and not lock[y][x] and not lock[y][x-1]);
    });

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        size_t y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2; y1--; x1--;
        cout << dominos_vertical(x1, y1+1, x2, y2) + dominos_horizontal(x1+1, y1, x2, y2) << '\n';
    }
}
