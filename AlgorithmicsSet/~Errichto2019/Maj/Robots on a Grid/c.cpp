#include <bits/stdc++.h>

using namespace std;

map<char, pair<int, int>> compass = {
    {'U', {0, -1}}, {'D', {0, +1}}, {'L', {-1, 0}}, {'R', {+1, 0}}
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t T;
    cin >> T;

    while(T --> 0)
    {
        size_t h, w;
        cin >> h >> w;

        #define I(x, y) ((y)*w + (x))

        const size_t n = w*h;
        vector<bool> flag(n);
        for(size_t y = 0; y < h; y++)
        {
            string row;
            cin >> row;
            for(size_t x = 0; x < w; x++)
                flag[I(x, y)] = not (row[x] - '0');
        }

        vector<size_t> next(n);
        vector<vector<size_t>> prev(n);
        for(size_t y = 0; y < h; y++)
        {
            string row;
            cin >> row;
            for(size_t x = 0; x < w; x++)
            {
                auto [dx, dy] = compass[row[x]];
                const size_t i = I(x, y), j = I(x+dx, y+dy);
                next[i] = j;
                prev[j].push_back(i);
            }
        }

        vector<bool> vis(n);
        vector<size_t> no(n, SIZE_MAX);
        vector<vector<size_t>> groups(n);
        size_t k = 0;
        for(size_t s = 0; s < n; s++) if(not vis[s])
        {
            size_t u = s;
            vis[s] = true;
            while(not vis[next[u]])
                vis[u = next[u]] = true;

            size_t root = next[u], len = 0;
            u = root;
            do {
                no[u] = len++;
                u = next[u];
            } while(u != root);

            do {
                function<void(size_t, size_t)> dfs = [&](size_t v, size_t d) {
                    vis[v] = true;
                    groups[k + (len + no[u] - d%len) % len].push_back(v);
                    for(auto vv : prev[v]) if(no[vv] == SIZE_MAX)
                        dfs(vv, d + 1);
                };
                dfs(u, 0);

                u = next[u];
            } while(u != root);

            k += len;
        }

        size_t result[2] = {k, 0};

        for(size_t i = 0; i < k; i++)
            for(auto u : groups[i])
                if(flag[u]) { result[1]++; break; }

        cout << result[0] << ' ' << result[1] << '\n';
    }
}
