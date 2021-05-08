#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree_2d
{
    size_t n;
    vector<vector<int>> F;

    fenwick_tree_2d(size_t _n) : n(_n), F(n+1, vector<int>(n+1)) {}

    void delta(size_t y, size_t xx, int v)
    {
        for(y++; y <= n; y += y & -y)
            for(size_t x = xx+1; x <= n; x += x & -x)
                F[y][x] += v;
    }

    int get_prefix(size_t y, size_t xx) const
    {
        int r = 0;
        for(; y; y &= y - 1)
            for(size_t x = xx; x; x &= x - 1)
                r += F[y][x];
        return r;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<vector<bool>> arr(n, vector<bool>(n));
    fenwick_tree_2d tree(n);
    for(size_t y = 0; y < n; y++)
    {
        string row;
        cin >> row;
        for(size_t x = 0; x < n; x++)
            if(row[x] == '*')
                tree.delta(y, x, +1), arr[y][x] = true;
    }

    while(q --> 0)
    {
        char t;
        cin >> t;
        if(t == '1')
        {
            size_t y, x;
            cin >> y >> x; y--; x--;
            tree.delta(y, x, arr[y][x] ? -1 : +1);
            arr[y][x] = not arr[y][x];
        }
        else if(t == '2')
        {
            size_t y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2; y1--; x1--;
            cout << tree.get_prefix(y1, x1) + tree.get_prefix(y2, x2) - tree.get_prefix(y1, x2) - tree.get_prefix(y2, x1) << '\n';
        }
    }
}
