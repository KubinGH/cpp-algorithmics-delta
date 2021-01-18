#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<int8_t>> A(n, vector<int8_t>(n));
    vector<size_t> X(n), Y(n);
    int64_t xs = 0, ys = 0, s = 0;
    auto flip = [&](size_t x, size_t y) {
        if(A[x][y]) xs -= X[x]==n, ys -= Y[y]==n, X[x]--, Y[y]--, s--;
        else        X[x]++, Y[y]++, xs += X[x]==n, ys += Y[y]==n, s++;
        A[x][y] ^= 1;
    };

    while(m --> 0)
    {
        size_t x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2; x1--; y1--;

        for(size_t x = x1; x < x2; x++)
            for(size_t y =  y1; y < y2; y++)
                flip(x, y);
    }

    auto get = [&]() {
        return min(int64_t(n)*int64_t(n) - s, s - xs*ys);
    };

    cout << get() << '\n';
    while(q --> 0)
    {
        size_t x, y;
        cin >> x >> y; x--; y--;
        flip(x, y);
        cout << get() << '\n';
    }
}
