#include <bits/stdc++.h>

using namespace std;

struct vec2d
{
    int64_t x, y;
};

vec2d operator- (const vec2d& lhs, const vec2d& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}
int64_t operator^ (const vec2d& lhs, const vec2d& rhs)
{
    return lhs.x*rhs.y - lhs.y*rhs.x;
}

int64_t ori(const vec2d& u, const vec2d& v, const vec2d& w)
{
    return (v - u) ^ (w - v);
}

struct block
{
    size_t a, b;
    vector<int64_t> Y;
    vector<vec2d> hull;
    int64_t delta;

    vec2d vec(size_t i) { return {(int64_t)i, Y[i-a]}; }

    void recompute_hull()
    {
        for(size_t i = 0; i < b-a; i++)
            Y[i] += delta;
        delta = 0;

        if(a == b)
            return;
        if(a+1 == b)
        {
            hull = {vec(a)};
            return;
        }

        hull = {vec(a), vec(a+1)};

        for(size_t i = a+2; i < b; i++)
        {
            auto v = vec(i);
            while(hull.size() > 1 and ori(hull.end()[-2], hull.end()[-1], v) >= 0)
                hull.pop_back();
            hull.push_back(v);
        }
    }

    vec2d query()
    {
        size_t lo = 0, hi = hull.size() - 1;
        while(lo < hi)
        {
            size_t mid = (lo + hi) / 2;
            if(ori({0, -delta}, hull[mid], hull[mid+1]) <= 0)
                hi = mid;
            else
                lo = mid+1;
        }
        return {hull[lo].x, hull[lo].y + delta};
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    const size_t d = max(floor(sqrt(n)), 1.0), k = (n+d-1) / d;

    vector<int64_t> A(n), S(n+1);
    for(auto& a : A)
        cin >> a;
    partial_sum(A.begin(), A.end(), S.begin() + 1);

    vector<block> blocks;
    for(size_t i = 0; i < k; i++)
    {
        size_t a = i*d+1, b = min((i+1)*d, n)+1;
        blocks.push_back({a, b, vector<int64_t>(S.begin()+a, S.begin()+b), {}, 0});
        blocks.back().recompute_hull();
    }

    while(q --> 0)
    {
        size_t p; int64_t v;
        cin >> p >> v; p--;

        auto dv = v - A[p];
        A[p] = v;

        auto& hit = blocks[p/d];
        for(size_t i = p + 1 - hit.a; i < hit.b - hit.a; i++)
            hit.Y[i] += dv;
        hit.recompute_hull();

        for(size_t i = p/d + 1; i < k; i++)
            blocks[i].delta += dv;

        vec2d r = blocks[0].query();
        for(size_t i = 1; i < k; i++)
        {
            vec2d u = blocks[i].query();
            if((r ^ u) > 0)
                r = u;
        }
        cout << r.x << '\n';
    }
}
