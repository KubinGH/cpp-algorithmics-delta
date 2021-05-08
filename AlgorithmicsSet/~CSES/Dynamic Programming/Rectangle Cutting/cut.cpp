#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX/3;

auto get(size_t n, size_t m)
{
    vector<vector<int>> T(n+1, vector<int>(m+1, +oo));
    for(size_t a = 0; a <= n; a++)
      for(size_t b = 0; b <= m; b++)
    {
        if(a != b)
        {
            for(size_t c = 0; 2*c <= b; c++)
                T[a][b] = min(T[a][b], T[a][c] + T[a][b-c] + 1);
            for(size_t c = 0; 2*c <= a; c++)
                T[a][b] = min(T[a][b], T[c][b] + T[a-c][b] + 1);
        }
        else
            T[a][b] = 0;
    }
    return T;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;
    cout << get(n, m)[n][m] << endl;
}
