#include <bits/stdc++.h>

using namespace std;

const size_t N = 19;

uint32_t is_over[N], is_direct[N][N];

void dfs_mark(uint32_t u, uint32_t p)
{
    if(is_over[u] & (1u << p)) return;
    if(u != p) is_over[u] |= 1u << p;
    for(uint32_t v = 0; v < N; v++) if(is_direct[u][v])
        dfs_mark(v, p);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        is_direct[a][b] = true;
    }
    for(uint32_t i = 0; i < n; i++)
        dfs_mark(i, i);
    static uint64_t R[1u << N] = {1};
    for(uint32_t s = 0; s < (1u << n); s++)
        for(uint32_t i = 0; i < n; i++) if(s & (1u << i))
            if(not (s & is_over[i]))
                R[s] += R[s ^ (1u << i)];
    cout << R[(1u << n) - 1];
}
