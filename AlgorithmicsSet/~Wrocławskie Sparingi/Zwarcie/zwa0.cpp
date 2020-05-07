#include <bits/stdc++.h>

using namespace std;

const int64_t oo = 1 << 30;

struct vec2d { int64_t x, y; };
vec2d operator+ (const vec2d& u, const vec2d& v)
    { return {u.x + v.x, u.y + v.y}; }
vec2d operator- (const vec2d& u)
    { return {-u.x, -u.y}; }
vec2d operator- (const vec2d& u, const vec2d& v)
    { return u + (-v); }
int64_t operator^ (const vec2d& u, const vec2d& v)
    { return u.x*v.y - u.y*v.x; }
int sgn(int64_t x)
    { return x < 0 ? -1 : x > 0; }
int ori(const vec2d& a, const vec2d& b, const vec2d& c)
    { return sgn((b - a) ^ (c - a)); }

struct segment { vec2d a, b; size_t i; };

ostream& operator<< (ostream& out, const vec2d& v)
{
    return out << "[" << v.x << ", " << v.y << "]";
}
ostream& operator<< (ostream& out, const segment& s)
{
    return out << "(" << s.a << "--" << s.b << ")";
}


bool on_segment(const segment& P, const vec2d& A)
{
    auto x = minmax(P.a.x, P.b.x), y = minmax(P.a.y, P.b.y);
    return ori(P.a, P.b, A) == 0 and
           x.first <= A.x and A.x <= x.second and
           y.first <= A.y and A.y <= y.second;
}

bool intersects(const segment& P, const segment& Q)
{
    int o00 = ori(P.a, P.b, Q.a), o01 = ori(P.a, P.b, Q.b),
        o10 = ori(Q.a, Q.b, P.a), o11 = ori(Q.a, Q.b, P.b);
    if(o00 != o01 and o10 != o11)
        return true;
    if(on_segment(P, Q.a) or on_segment(P, Q.b) or on_segment(Q, P.a) or on_segment(Q, P.b))
        return true;
    else
        return false;
}


struct broom_cmp
{
    int64_t* X;

    long double at(const segment& P) const
    {
        if(P.a.x == P.b.x)
            return P.a.y;
        return (long double) ((*X-P.a.x)*P.b.y + (P.b.x-*X)*P.a.y) / (P.b.x - P.a.x);
    }

    bool operator() (const segment& P, const segment& Q) const
    {
        return at(P) < at(Q);
    }
};


pair<bool, pair<size_t, size_t>> any_intersection(const vector<segment>& seg)
{
    const size_t n = seg.size();

    vector<pair<int64_t, size_t>> events(2*n);
    for(size_t i = 0; i < n; i++)
    {
        events[2*i+0] = {seg[i].a.x, i};
        events[2*i+1] = {seg[i].b.x, i};
    }
    sort(events.begin(), events.end());

    int64_t X = -oo;
    broom_cmp cmp {&X};
    set<segment, broom_cmp> T(cmp);

    T.insert({{-oo, -oo}, {+oo, -oo}, n+2});
    T.insert({{-oo, +oo}, {+oo, +oo}, n+3});

    vector<bool> on(n);
    vector<set<segment, broom_cmp>::iterator> where(n);

    for(const auto& e : events)
    {
        X = e.first; size_t i = e.second;
        if(on[i])
        {
            auto it = where[i];
            if(intersects(*prev(it), *next(it)))
                return {true, minmax(prev(it)->i, next(it)->i)};
            T.erase(it);
            on[i] = false;
        }
        else
        {
            auto it = T.lower_bound(seg[i]);
            if(intersects(*it, seg[i]))
                return {true, minmax(it->i, seg[i].i)};
            else if(intersects(*prev(it), seg[i]))
                return {true, minmax(prev(it)->i, seg[i].i)};
            where[i] = T.insert(seg[i]).first;
            on[i] = true;
        }
    }

    return {false, {}};
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<segment> seg(n);
    for(size_t i = 0; i < n; i++)
    {
        auto& s = seg[i]; s.i = i;
        cin >> s.a.x >> s.a.y >> s.b.x >> s.b.y;
        if(s.a.x > s.b.x)
            swap(s.a, s.b);
        else if(s.a.x == s.b.x and s.a.y > s.b.y)
            swap(s.a, s.b);
    }

    auto pq = any_intersection(seg);
    if(pq.first)
    {
        size_t p, q; tie(p, q) = pq.second;
        auto seg_p = seg, seg_q = seg;
        seg_p.erase(seg_p.begin() + p);
        seg_q.erase(seg_q.begin() + q);

        if(any_intersection(seg_p).first)
        {
            if(any_intersection(seg_q).first)
                cout << "NIE" << endl;
            else
                cout << q+1 << endl;
        }
        else
            cout << p+1 << endl;
    }
    else
        cout << "?" << endl, abort();
}
