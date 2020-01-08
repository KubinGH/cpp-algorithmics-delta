#include <bits/stdc++.h>

using namespace std;

int d(int x1, int y1, int x2, int y2)
{
    return abs(x1-x2) + abs(y1-y2);
}

int main()
{
    size_t n;
    cin >> n;

    vector<pair<int, int>> P(2*n);
    for(auto& [x, y] : P)
        cin >> x >> y;

    sort(P.begin(), P.end());

    vector<vector<int64_t>> R(n+1, vector<int64_t>(n+1, INT64_MAX / 3));
    R[0][0] = 0;

    for(size_t a = 0; a <= n; a++)
      for(size_t b = 0; b <= n; b++)
    {
        auto [x, y] = a or b ? P[a+b-1] : make_pair(0, 0);
        if(a) R[a][b] = min(R[a][b], R[a-1][b] + d(x, y, a, 1));
        if(b) R[a][b] = min(R[a][b], R[a][b-1] + d(x, y, b, 2));
    }

    cout << R[n][n];
}
