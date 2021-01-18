// Jakub Bachurski
// Tablica binarna - O(nm + q)

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int8_t>> pos(n, vector<int8_t>(m));

    int cnt = 0;
    auto flip = [&](int x, int y) {
        if(not (0 <= x and x < n and 0 <= y and y < m))
            return;
        if(pos[x][y] ^= 1)
            cnt++;
        else
            cnt--;
    };

    while(q --> 0)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 -= 2; y1 -= 2; x2--; y2--;

        flip(x1, y1); flip(x2, y2);
        flip(x1, y2); flip(x2, y1);

        cout << cnt << '\n';
    }
}
