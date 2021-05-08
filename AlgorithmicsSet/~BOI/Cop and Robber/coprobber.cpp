#include <bits/stdc++.h>

using namespace std;

const size_t M = 512;

int n = -1;
bool G[M][M];
bool vis[2][M][M], win[2][M][M], lose[2][M][M];
int opt[2][M][M], deg[2][M][M], gdeg[M], vertex = -1;

int start(int _n, bool _G[500][500])
{
    n = _n;
    for(int u = 0; u < n; u++)
        for(int v = 0; v < n; v++)
            G[u][v] = _G[u][v], opt[0][u][v] = opt[1][u][v] = -1;

    for(int u = 0; u < n; u++)
        for(int v = 0; v < n; v++)
            gdeg[u] += G[u][v];
    for(int u = 0; u < n; u++)
        for(int v = 0; v < n; v++)
            deg[0][u][v] = gdeg[u] + 1, deg[1][u][v] = gdeg[v];

    for(int u = 0; u < n; u++)
        win[0][u][u] = lose[1][u][u] = true;

    vector<tuple<int, int, int>> tovis;
    for(auto t : {0, 1})
        for(int u = 0; u < n; u++)
            if(not vis[t][u][u])
                vis[t][u][u] = true, tovis.emplace_back(t, u, u);

    while(not tovis.empty())
    {
        auto [t, u, v] = tovis.back(); tovis.pop_back();
        if(t)
        {
            for(int u1 = 0; u1 < n; u1++) if((u1 == u or G[u][u1]) and not vis[0][u1][v])
            {
                if(lose[1][u][v])
                    win[0][u1][v] = true, opt[0][u1][v] = u;
                else if(--deg[0][u1][v] == 0)
                    lose[0][u1][v] = true;
                else
                    continue;
                vis[0][u1][v] = true;
                tovis.emplace_back(0, u1, v);
            }
        }
        else // cop
        {
            for(int v1 = 0; v1 < n; v1++) if(G[v][v1] and not vis[1][u][v1])
            {
                if(lose[0][u][v])
                    win[1][u][v1] = true, opt[1][u][v1] = v;
                else if(--deg[1][u][v1] == 0)
                    lose[1][u][v1] = true;
                else
                    continue;
                vis[1][u][v1] = true;
                tovis.emplace_back(1, u, v1);
            }
        }

    }

    for(int u = 0; u < n; u++)
    {
        bool all = true;
        for(int v = 0; v < n; v++)
            if(not win[0][u][v])
                all = false;
        if(all)
            return vertex = u;
    }
    return -1;
}

int nextMove(int r)
{
    return vertex = opt[0][vertex][r];
}


#define MAX_N 500
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N;
    cin >> N;
    bool A[MAX_N][MAX_N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }
    int P = start(N,A);
    cout << P << endl;
    int R;
    cin >> R;
    while (true) {
        if (P == R) break;
        P = nextMove(R);
        cout << P << endl;
        if (P == R) break;
        cin >> R;
    }
}
