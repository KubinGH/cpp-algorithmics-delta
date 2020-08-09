#include <bits/stdc++.h>

using namespace std;

#ifdef XHOVA
const size_t N = 1000;
#else
const size_t N = 1 << 10;
#endif

#define for_neighbours(_vertex_, _var_, ...) \
    for(auto _delta_ : compass) { size_t _var_ = _vertex_ + _delta_; if(not wall[_var_]) { __VA_ARGS__ }; }

bool wall[N*N];
const int compass[4] = {+1, int(N), -1, -int(N)};

enum Direction
{
    East = 0, South = 1, West = 2, North = 3
};
size_t I(size_t i, size_t j) { return i*N + j; }

bool vis[N*N], stk[N*N], go[N*N][4];
int low[N*N], preorder[N*N], postorder[N*N], component[N*N];
size_t parent[N*N];
int watch = 0;

void dfs(size_t u)
{
    low[u] = preorder[u] = watch++;
    vis[u] = stk[u] = true;
    for_neighbours(u, v, {
        if(vis[v] and stk[v])
            low[u] = min(low[u], preorder[v]);
        if(not vis[v])
            parent[v] = u, dfs(v), low[u] = min(low[u], low[v]);
    });
    postorder[u] = watch;
    stk[u] = false;
}

bool sub(size_t below, size_t above)
{
    return preorder[above] <= preorder[below] and preorder[below] < postorder[above];
}

bool biconn(size_t w, Direction a, Direction b)
{
    size_t u = w + compass[a], v = w + compass[b];
    if(wall[u] or wall[v])
        return false;
    if(u == v)
        return true;
    if(preorder[u] > preorder[v])
        swap(u, v);
    if(not (sub(u, w) or sub(v, w)))
        return true;
    size_t u1 = 0, v1 = 0;
    for_neighbours(w, d, {
        if(parent[d] == w)
        {
            if(sub(u, d)) u1 = d;
            if(sub(v, d)) v1 = d;
        }
    });
    if(u1 and v1)
        return u1 == v1;
    else if(not u1 and v1)
        return low[v1] < preorder[w];
    __builtin_unreachable();
}

size_t curr = 0, vis1[N*N];
void dfs1(size_t u)
{
    if(vis1[u] == curr)
        return;
    vis1[u] = curr;
    for_neighbours(u, v, {
        dfs1(v);
    });
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    for(size_t i = 0; i <= n+1; i++)
        wall[I(i, 0)] = wall[I(i, m+1)] = true;
    for(size_t j = 0; j <= m+1; j++)
        wall[I(0, j)] = wall[I(n+1, j)] = true;

    for(size_t i = 1; i <= n; i++)
    {
        string S;
        cin >> S;
        for(size_t j = 1; j <= m; j++)
            wall[I(i, j)] = (S[j-1] == '#');
    }

    for(size_t i = 1; i <= n; i++)
        for(size_t j = 1; j <= m; j++)
            if(not wall[I(i, j)] and not vis[I(i, j)])
                dfs(I(i, j));

    size_t x1, y1, x2, y2;
    cin >> x2 >> y2 >> x1 >> y1;
    size_t i1 = I(x1, y1), i2 = I(x2, y2);

    size_t d;
    for(d = 0; d < 4; d++)
    {
        vis1[i2] = ++curr;
        dfs1(i2 + compass[d]);
        if(vis1[i1] == curr)
            break;
    }

    if(d < 4)
    {
        go[i2][d] = true;

        queue<pair<size_t, int>> Q;
        Q.emplace(i2, d);
        auto maybe = [&](size_t i, int c) {
            if(not go[i][c])
                go[i][c] = true, Q.emplace(i, c);
        };

        while(not Q.empty())
        {
            auto ic = Q.front(); Q.pop();
            size_t i = ic.first; int c = ic.second;

            if(not wall[i + compass[c^2]])
                maybe(i + compass[c^2], c);
            for(size_t C = 0; C < 4; C++)
                if(biconn(i, Direction(c), Direction(C)))
                    maybe(i, C);
        }
    }
    else
        go[i2][0] = true;

    for(size_t i = 1; i <= n; i++, cout << '\n')
      for(size_t j = 1; j <= m; j++)
    {
        size_t k = I(i, j);
        cout << (wall[k] ? '#' : (go[k][0] or go[k][1] or go[k][2] or go[k][3] ? 'o' : '.'));
    }
}
