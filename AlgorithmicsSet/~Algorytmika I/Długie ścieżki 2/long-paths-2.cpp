#include <bits/stdc++.h>

using namespace std;

const size_t N = 128;

size_t n;
bool A[N][N];

uint lim;
bool path_of_len[N][N*N]; // dest, length
uint max_path_lim[N][N*N]; // dest, less than length

void dfs_small(size_t u, size_t d)
{
    if(d > lim or path_of_len[u][d])
        return;
    path_of_len[u][d] = true;
    for(size_t v = 0; v < n; v++)
        if(A[u][v])
            dfs_small(v, d + 1);
}

bool vis[N], stk[N];
size_t find_cycle(size_t u, size_t s)
{
    if(vis[u])
        return 0;
    vis[u] = stk[u] = true;
    for(size_t v = 0; v < n; v++)
      if(A[u][v])
    {
        if(v == s)
            return 1;
        if(auto dd = find_cycle(v, s); dd)
            return 1 + dd;
    }
    stk[u] = false;
    return 0;
}

uint cycle[N];
bool path_of_len_mod[N][N][N][2]; // mid, target, distance mod cycle, passed mid

void dfs_mod(size_t u, size_t d, size_t w, bool t)
{
    if(d == cycle[w]) d = 0;
    if(u == w) t = true;
    if(path_of_len_mod[w][u][d][t]) return;
    path_of_len_mod[w][u][d][t] = true;
    for(size_t v = 0; v < n; v++)
        if(A[u][v])
            dfs_mod(v, d + 1, w, t);
}

uint opt_rem_lt[N][N][N]; // mid, target, remainder less than

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t m, q;
    cin >> n >> m >> q;

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        A[u][v] = true;
    }

    lim = n * n;
    dfs_small(0, 0);

    for(size_t v = 0; v < n; v++)
    {
        max_path_lim[v][0] = path_of_len[v][0] ? 0 : UINT_MAX;
        for(uint d = 1; d <= lim; d++)
            if(path_of_len[v][d])
                max_path_lim[v][d] = d;
            else
                max_path_lim[v][d] = max_path_lim[v][d-1];
    }

    for(size_t w = 0; w < n; w++)
    {
        fill(vis, vis + N, false);
        fill(stk, stk + N, false);

        if((cycle[w] = find_cycle(w, w)))
        {
            dfs_mod(0, 0, w, false);
            for(size_t v = 0; v < n; v++)
            {
                opt_rem_lt[w][v][0] = UINT_MAX;
                for(uint d = 0; d < cycle[w]; d++)
                    if(path_of_len_mod[w][v][d][true])
                        opt_rem_lt[w][v][d+1] = d;
                    else
                        opt_rem_lt[w][v][d+1] = opt_rem_lt[w][v][d];
            }

        }
    }

    while(q --> 0)
    {
        size_t v; uint64_t l;
        cin >> v >> l; v--;

        if(max_path_lim[v][min(l, (uint64_t)lim)] != UINT_MAX)
        {
            uint64_t r = 0;
            r = max_path_lim[v][min(l, (uint64_t)lim)];

            if(l > lim)
            {
                for(size_t w = 0; w < n; w++) if(cycle[w])
                    for(auto d : {opt_rem_lt[w][v][l%cycle[w]+1], opt_rem_lt[w][v][cycle[w]]})
                        if(d != UINT_MAX)
                            r = max(r, d + ((l-d)/cycle[w]) * cycle[w]);
            }
            cout << r << '\n';
        }
        else
            cout << "NIE\n";
    }
}
