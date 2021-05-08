#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<vector<int>> S(n+1, vector<int>(n+1));
    for(size_t y = 0; y < n; y++)
    {
        string row;
        cin >> row;
        for(size_t x = 0; x < n; x++)
            S[y+1][x+1] = S[y+1][x] + S[y][x+1] - S[y][x] + (row[x] == '*');
    }

    auto sum = [&](size_t y1, size_t x1, size_t y2, size_t x2) {
        return S[y2][x2] + S[y1][x1] - S[y1][x2] - S[y2][x1];
    };

    while(q --> 0)
    {
        size_t y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2; y1--; x1--;
        cout << sum(y1, x1, y2, x2) << '\n';
    }
}
