#include <bits/stdc++.h>

using namespace std;

const size_t NAX = 512;
const int oo = INT_MAX / 6, OO = INT_MAX / 3;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    //vector<vector<int>> D(n, vector<int>(n, +oo));
    static int D[NAX][NAX];
    for(size_t u = 0; u < n; u++)
        for(size_t v = 0; v < n; v++)
            D[u][v] = +oo;

    for(size_t u = 0; u < n; u++)
        D[u][u] = 0;

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int d;
        cin >> u >> v >> d; u--; v--;
        D[u][v] = min(d, D[u][v]);
    }

    for(size_t v = 0; v < n; v++)
        for(size_t u = 0; u < n; u++)
            for(size_t w = 0; w < n; w++)
                if(D[u][v] < +oo and D[v][w] < +oo)
                    D[u][w] = max(min(D[u][w], D[u][v] + D[v][w]), -oo);

    for(size_t v = 0; v < n; v++)
        for(size_t u = 0; u < n; u++)
            for(size_t w = 0; w < n; w++)
                if(D[u][v] < +oo and D[v][w] < +oo and D[v][v] < 0)
                    D[u][w] = -OO;

    for(size_t u = 0; u < n; u++, cout << '\n')
        for(size_t v = 0; v < n; v++, cout << ' ')
    {
        if(D[u][v] == +oo)
            cout << '*';
        else if(D[u][v] == -OO)
            cout << "-oo";
        else
            cout << D[u][v];
    }
}
