#include <bits/stdc++.h>

using namespace std;

const uint64_t mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<uint64_t>> wae(n+2, vector<uint64_t>(n+2));
    wae[1][0] = 1;

    for(size_t y = 1; y <= n; y++)
    {
        string row;
        cin >> row;
        for(size_t x = 1; x <= n; x++)
            wae[y][x] = row[x-1] == '.' ? (wae[y-1][x] + wae[y][x-1]) % mod : 0;
    }

    cout << wae[n][n] << endl;
}
