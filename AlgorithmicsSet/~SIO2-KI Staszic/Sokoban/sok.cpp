#include <bits/stdc++.h>

using namespace std;

struct cell { uint32_t x, y; };
bool operator== (const cell& lhs, const cell& rhs)
    { return lhs.x == rhs.x and lhs.y == rhs.y; }
bool operator!= (const cell& lhs, const cell& rhs)
    { return not (lhs == rhs); }

constexpr uint32_t dx[4] = {0, 0, -1u, 1u}, dy[4] = {-1u, 1u, 0, 0};
template<typename Filter = function<bool(uint32_t, uint32_t)>>
struct grid_getter
{
    Filter F;
    uint32_t b;
    cell B[4];
    grid_getter(Filter _F) : F(_F) {}
    grid_getter& operator() (uint32_t x, uint32_t y)
    {
        b = 0;
        for(uint32_t i = 0; i < 4; i++)
            if(F(x + dx[i], y + dy[i]))
                B[b++] = {x + dx[i], y + dy[i]};
        return *this;
    }
    grid_getter& operator() (cell c) { return operator() (c.x, c.y); }
    const cell* begin() const { return B; }
    const cell* end() const { return B+b; }
};

struct dfs_tree
{
    vector<cell> parent; vector<uint32_t> preorder, low;
    vector<bool> is_cut;
    vector<vector<cell>> children, return_edge;
    dfs_tree(uint32_t n)
        : parent(n), preorder(n), low(n), is_cut(n),
          children(n), return_edge(n) {}
};

#define J(x, y) ((y)*w+(x))
#define I(c) J((c).x, (c).y)

template<typename Getter>
void dfs_make_tree(cell u, Getter next_to, dfs_tree& T, vector<bool>& vis,
                   uint32_t w, uint32_t h, uint32_t& dtime)
{
    vis[I(u)] = true;
    T.low[I(u)] = T.preorder[I(u)] = dtime++;
    for(auto v : next_to(u))
    {
        if(v == T.parent[I(u)])
            continue;
        if(vis[I(v)])
            T.return_edge[I(u)].push_back(v);
        else
        {
            T.children[I(u)].push_back(v);
            T.parent[I(v)] = u;
            dfs_make_tree(v, next_to, T, vis, w, h, dtime);
        }

    }
    for(auto v : T.return_edge[I(u)])
        T.low[I(u)] = min(T.low[I(u)], T.preorder[I(v)]);
    for(auto v : T.children[I(u)])
        T.low[I(u)] = min(T.low[I(u)], T.low[I(v)]);

    if(T.parent[I(u)] == cell{-1u, -1u})
        T.is_cut[I(u)] = T.children[I(u)].size() > 1;
    else
    {
        T.is_cut[I(u)] = false;
        for(auto v : T.children[I(u)])
            if(T.low[I(v)] >= T.preorder[I(u)])
                T.is_cut[I(u)] = true;
    }

}

template<typename Getter>
void dfs_color(cell u, Getter next_to, dfs_tree& T, vector<bool>& vis,
               uint32_t w, uint32_t h, vector<vector<uint32_t>>& colors,
               uint32_t color)
{
    vis[I(u)] = true;
    colors[I(u)].push_back(color);
    for(cell v : next_to(u))
    {
        if(not vis[I(v)] and not T.is_cut[I(v)])
            dfs_color(v, next_to, T, vis, w, h, colors, color);
        if(T.is_cut[I(v)])
            colors[I(v)].push_back(color);
    }
}
template<typename Getter>
bool dfs_find_conn(cell u, Getter next_to, dfs_tree& T, vector<bool>& vis,
                    uint32_t w, uint32_t h, cell target, cell block)
{
    if(u == target)
        return true;
    vis[I(u)] = true;
    for(auto v : next_to(u))
    {
        if(not vis[I(v)] and v != block)
        {
            bool p = dfs_find_conn(v, next_to, T, vis, w, h, target, block);
            if(p) return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w;
    cin >> h >> w;
    vector<string> A(h);
    for(uint32_t y = 0; y < h; y++)
        cin >> A[y];
    auto F = [&](uint32_t x, uint32_t y) {
        return x < w and y < h and A[y][x] == '.';
    };
    grid_getter<decltype(F)> next_to(F);

    uint32_t by, bx, py, px;
    cin >> by >> bx >> py >> px;
    by--; bx--; py--; px--;

    vector<bool> vis(w*h);
    dfs_tree T(w*h);
    uint32_t dtime = 1;
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
        if(not vis[J(x, y)] and A[y][x] == '.')
    {
        T.parent[J(x, y)] = {-1u, -1u};
        dfs_make_tree({x, y}, next_to, T, vis, w, h, dtime);
    }
    fill(vis.begin(), vis.end(), false);
    vector<vector<uint32_t>> colors(w*h);
    uint32_t colorcount = 0;
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
        if(A[y][x] == '.' and not T.is_cut[J(x, y)])
          dfs_color({x, y}, next_to, T, vis, w, h, colors, colorcount++);
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
        if(A[y][x] == '.' and T.is_cut[J(x, y)])
    {
        cell u = {x, y};
        for(auto v : next_to(u))
          if(T.is_cut[I(v)])
        {
            colors[I(u)].push_back(colorcount);
            colors[I(v)].push_back(colorcount);
            colorcount++;
        }
    }

    auto same_dconn = [&](cell u, cell v) {
        for(uint32_t i = 0; i < colors[I(u)].size(); i++)
            for(uint32_t j = 0; j < colors[I(v)].size(); j++)
                if(colors[I(u)][i] == colors[I(v)][j])
                    return true;
        return false;
    };

    #define P(x, y, r) (4*w*(y) + 4*(x) + (r))
    vector<vector<uint32_t>> G(4*w*h);
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
        for(uint32_t r = 0; r < 4; r++)
    {
        uint32_t xp = x + dx[r], yp = y + dy[r];
        if(not F(xp, yp)) continue;

        uint32_t xt = x + dx[r^1], yt = y + dy[r^1];
        if(F(xt, yt))
            G[P(x, y, r)].push_back(P(xt, yt, r));

        for(uint32_t rt = 0; rt < 4; rt++) if(r != rt)
        {
            uint32_t xq = x + dx[rt], yq = y + dy[rt];
            if(F(xq, yq) and same_dconn({xp, yp}, {xq, yq}))
                G[P(x, y, r)].push_back(P(x, y, rt));
        }
    }
    uint32_t ir = -1u;
    for(uint32_t r = 0; r < 4; r++)
    {
        uint32_t xt = bx + dx[r], yt = by + dy[r];
        if(not F(xt, yt)) continue;
        fill(vis.begin(), vis.end(), false);
        bool z = dfs_find_conn({xt, yt}, next_to, T, vis, w, h, {px, py}, {bx, by});
        if(z)
        {
            ir = r;
            break;
        }
    }
    vector<bool> M(4*w*h);
    if(ir != -1u)
    {
        stack<uint32_t> V;
        V.push(P(bx, by, ir)); M[P(bx, by, ir)] = true;
        while(not V.empty())
        {
            uint32_t u = V.top(); V.pop();
            for(uint32_t v : G[u])
                if(not M[v])
                    V.push(v), M[v] = true;
        }
    }
    else
        M[P(bx, by, 0)] = true;

    for(uint32_t y = 0; y < h; y++, cout << '\n')
      for(uint32_t x = 0; x < w; x++)
    {
        if(A[y][x] == '#')
            cout << '#';
        else if(A[y][x] == '.')
        {
            if(M[P(x, y, 0)] or M[P(x, y, 1)] or M[P(x, y, 2)] or M[P(x, y, 3)])
                cout << 'o';
            else
                cout << '.';
        }
    }
}
