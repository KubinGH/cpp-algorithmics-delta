#include <bits/stdc++.h>

using namespace std;

struct line
{
    int64_t a, b;
    int64_t operator() (int64_t x) const { return a*x + b; }
};
long double intersect(line p, line q)
{
    return (long double)(q.b - p.b) / (p.a - q.a);
}
// r min-dominates q relative to p
// p.a > q.a > r.a
bool dom(line p, line q, line r)
{
    return intersect(p, r) <= intersect(p, q);
}

vector<pair<int, int>> filter_dominated(vector<pair<int, int>> I)
{
    vector<pair<int, int>> J = {{INT_MIN, INT_MIN}};
    sort(I.begin(), I.end(), [](pair<int, int> lhs, pair<int, int> rhs) {
        return lhs.first != rhs.first ? lhs.first < rhs.first : lhs.second > rhs.second;
    });
    for(auto [l, r] : I)
        if(not (J.back().first <= l and r <= J.back().second))
            J.emplace_back(l, r);
    J.erase(J.begin());
    return J;
}
constexpr int64_t square(int64_t x) { return x*x; }

int64_t take_photos(int _n, int _m, int _k, vector<int> r, vector<int> c)
{
    size_t n = _n, m = _m, k = _k; (void)m;

    vector<pair<int, int>> I;
    for(size_t i = 0; i < n; i++)
        I.emplace_back(min(r[i], c[i]), max(r[i], c[i]));
    I = filter_dominated(I);
    n = I.size();

    vector<vector<int64_t>> cost(k+1, vector<int64_t>(n+1, INT64_MAX / 3));
    auto get_line = [&](size_t l, size_t i) {
        return line {
            -2 * I[i].first,
            cost[l][i] + square(I[i].first) -
             square(max(0, (i ? I[i-1].second : -1) - I[i].first + 1))
        };
    };
    vector<vector<line>> hull(k+1);

    cost[0][0] = 0;
    hull[0].push_back(get_line(0, 0));

    for(size_t l = 1; l <= k; l++)
    {
        cost[l][0] = 0;
        for(size_t i = 1, h = 0; i <= n; i++)
        {
            auto x = I[i-1].second + 1;
            while(h+1 < hull[l-1].size() and hull[l-1][h](x) > hull[l-1][h+1](x))
                h++;

            cost[l][i] = hull[l-1][h](x) + square(x);

            auto f = get_line(l, i-1);
            while(hull[l].size() >= 2 and dom(hull[l].end()[-2], hull[l].end()[-1], f))
                hull[l].pop_back();
            hull[l].push_back(f);
        }
    }
    return cost[k][n];
}

#ifdef XHOVA
int main()
{
    cout << take_photos(5, 7, 2, {0, 4, 4, 4, 4}, {3, 4, 6, 5, 6}) << endl;
    cout << take_photos(2, 6, 2, {1, 4}, {4, 1}) << endl;
}
#endif
