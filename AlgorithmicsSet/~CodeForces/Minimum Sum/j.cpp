#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
};
int square(int x) { return x*x; }
int dist(point p, point q) { return square(p.x - q.x) + square(p.y - q.y); }

int main()
{
#ifndef XHOVA
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#endif

    int clock_start = clock();

    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;


    vector<int> tr(n);
    vector<point> P(n);

    set<pair<size_t, size_t>> S;
    vector<bool> dup(n);

    for(size_t i = 0; i < n; i++)
    {
        cin >> P[i].x >> P[i].y;
        tr[i] = (P[i].x < 0) + ((P[i].y < 0) << 1);
        P[i].x = abs(P[i].x);
        P[i].y = abs(P[i].y);
        if(S.count({P[i].x, P[i].y}))
            dup[i] = true;
        else
            S.emplace(P[i].x, P[i].y);
    }

    pair<size_t, size_t> opt = {0, 1};
    int opt_dist = dist(P[0], P[1]);
    auto candy = [&](size_t i, size_t j) {
        auto d = dist(P[i], P[j]);
        if(i != j and d < opt_dist)
            opt = {i, j}, opt_dist = d;
    };

    mt19937 gen(time(0));
    uniform_int_distribution<int> dis(-3e4, 3e4);
    const size_t C = 192;
    vector<size_t> I(n);

    while((clock() - clock_start) < (n > 250 ? 1.4 : 0.33) * CLOCKS_PER_SEC / 2.0)
    {
        point o = {dis(gen), dis(gen)};
        iota(I.begin(), I.end(), 0);
        sort(I.begin(), I.end(), [&](size_t i, size_t j) {
            return (P[i].x - P[j].x)*(P[i].x + P[j].x - 2*o.x)
                 + (P[i].y - P[j].y)*(P[i].y + P[j].y - 2*o.y) < 0;
        });
        for(size_t i = 0; i < n; i++)
            for(size_t j = i; j <= i + C and j < n; j++)
                candy(I[i], I[j]);
    }

    cout << opt.first+1 << " " << tr[opt.first]+1 << " " << opt.second+1 << " " << (tr[opt.second]^3)+1;
}
