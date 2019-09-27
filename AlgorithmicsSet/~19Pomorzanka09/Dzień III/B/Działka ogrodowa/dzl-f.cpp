#include <bits/stdc++.h>

using namespace std;

const size_t FIX = 40000;

template<typename T, typename Container>
size_t q_lower_bound(Container& c, size_t first, size_t last, T value)
{
    while(first < last)
    {
        auto mid = first + (last-first)/2;
        if(c[mid] >= value)
            last = mid;
        else
            first = mid+1;
    }
    return first;
}

struct point_fenwick_tree
{
    size_t n;
    vector<vector<size_t>> F;
    point_fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    void insert(size_t x, size_t y)
    {
        x++;
        while(x <= n)
            F[x].push_back(y), x += lsb(x);
    }
    void resort()
    {
        for(size_t i = 0; i <= n; i++)
            sort(F[i].begin(), F[i].end());
    }

    size_t count(size_t x, size_t y)
    {
        size_t result = 0;
        while(x)
            result += q_lower_bound(F[x], 0, F[x].size(), y), x -= lsb(x);
        return result;
    }

    size_t count(size_t x1, size_t y1, size_t x2, size_t y2)
    {
        return count(x2, y2) + count(x1, y1) - count(x1, y2) - count(x2, y1);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t w, h, n;
    cin >> w >> h >> n;
    w++, h++;

    point_fenwick_tree F(2*FIX+0xD);

    vector<size_t> X(n), Y(n);
    for(size_t i = 0; i < n; i++)
    {
        cin >> X[i] >> Y[i];
        X[i] += FIX; Y[i] += FIX;
        F.insert(X[i], Y[i]);
    }
    F.resort();

    size_t result = 0;
    for(size_t i = 0; i < n; i++)
    {
        size_t x = X[i], y = Y[i];
        auto a = F.count(x-w+1, y-h+1, x+1, y+1),
             b = F.count(x    , y    , x+w, y+h),
             c = F.count(x-w+1, y    , x+1, y+h),
             d = F.count(x    , y-h+1, x+w, y+1);
        result = max(result, max({a, b, c, d}));
    }
    cout << result;
}
