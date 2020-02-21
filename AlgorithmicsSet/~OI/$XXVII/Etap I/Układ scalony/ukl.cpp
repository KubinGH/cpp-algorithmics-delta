#include <algorithm>
#include <iostream>
#include <optional>
#include <complex>
#include <vector>
#include <array>
#ifdef XHOVA
#include <cassert>
#define xassert assert
#else
#define xassert(cond) (void)(cond)
#endif

using namespace std;

using point = complex<int>;
point compass[4] = {1, 1i, -1, -1i};
int East = 0, South = 1, West = 2, North = 3;
int rotated(int dir, int rot) { return (dir+rot) & 3; }
int opposite(int dir) { return rotated(dir, 2); }

bool domino(point A, point B) { return A.real() <= B.real() and A.imag() <= B.imag(); }
bool domino(point A, point P, point B) { return domino(A, P) and domino(P, B); }

// ----->
// <----|
// |---->
vector<point> radiator(point P, point A, point B, int dir)
{
    vector<point> result = {};
    int rot = 1;
    while(domino(A, P, B))
    {
        result.push_back(P);
        while(domino(A, P + compass[dir], B))
            result.push_back(P += compass[dir]);
        P += compass[dir = rotated(dir, rot)];
        dir = rotated(dir, rot);
        rot = -rot;
    }
    return result;
}

void verify(int w, int h, int k, vector<pair<point, point>> edges);

optional<vector<pair<point, point>>> solve(int w, int h, int k)
{
    int req_k = w + h - (w%2 or h%2) - 1;

    if(not (req_k <= k and k <= w*h - 1))
        return {};
    // Nie wiem czemu przypadek dla 0mod2 dziala dla w < h. Dziala, nie ruszaj.
    if((w%2 == 1 and h%2 == 0) or (w%2 == 0 and h%2 == 0 and w > h))
    {
        auto edges = solve(h, w, k);
        for(auto& [P, Q] : *edges)
            P = {P.imag(), P.real()}, Q = {Q.imag(), Q.real()};
        return edges;
    }

    vector<vector<array<bool, 4>>> _conn_(w, vector<array<bool, 4>>(h));
    auto conn = [&](point P) -> array<bool, 4>& {
        static array<bool, 4> trash;
        return domino(0, P, {w-1, h-1}) ? _conn_[P.real()][P.imag()] : trash;
    };
    auto grab = [&](point P, int dir, bool v) {
        conn(P)[dir] = conn(P + compass[dir])[opposite(dir)] = v;
    };
    auto clear_conn = [&](point P) {
        for(int dir = 0; dir < 4; dir++)
            grab(P, dir, false);
    };
    auto splice = [&](point P, point Q) {
        auto D = Q - P;
        auto dir = find(compass, compass + 4, D) - compass; xassert(dir < 4);
        grab(P, dir, true);
    };

    int t = (h-1) / 2;
    for(int x = 0; x+1 < w; x++)
        grab({x, t}, East, true);
    for(int x = 0; x < w; x++)
        for(int y = 0; y+1 < h; y++)
            grab({x, y}, South, true);

    auto tops = radiator({1, 0}, {1, 0}, {w-1, t-1}, East);
    auto bots = radiator({w-2, h-1}, {0, t+1}, {w-2, h-1}, West);
    tops.insert(tops.begin(), point{0, 0});
    bots.insert(bots.begin(), point{w-1, h-1});

    int l = k - req_k + (w%2 == 0 and h%2 == 0);
    for(auto S : {tops, bots})
        for(size_t i = 0; l and i+1 < S.size(); i++, l--)
            clear_conn(S[i+1]), splice(S[i], S[i+1]);

    vector<pair<point, point>> edges;
    for(int y = 0; y < h; y++)
        for(int x = 0; x < w; x++)
    {
        point P = {x, y};
        if(conn(P)[East])  edges.emplace_back(P, P + compass[East]);
        if(conn(P)[South]) edges.emplace_back(P, P + compass[South]);
    }

    return edges;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int h, w, k;
    cin >> h >> w >> k;

    auto edges = solve(w, h, k);

    if(edges)
    {
        verify(w, h, k, *edges);
        cout << "TAK\n";
        for(auto [P, Q] : *edges)
            cout << P.imag()+1 << " " << P.real()+1 << " " << Q.imag()+1 << " " << Q.real()+1 << '\n';
    }
    else
        cout << "NIE\n";
}

void verify(int w, int h, int k, vector<pair<point, point>> edges)
#ifdef XHOVA
{
    cerr << ". . ." << endl;
    cerr << "(" << w << ", " << h << ", " << k << ")" << endl;
    cerr << "|E| = " << edges.size() << " =?= " << w*h-1 << endl;
    assert((int)edges.size() == w*h-1);
    vector<vector<vector<point>>> _graph_(w, vector<vector<point>>(h));
    auto graph = [&](point P) -> vector<point>& {
        assert(domino(0, P, {w-1, h-1}));
        return _graph_[P.real()][P.imag()];
    };
    for(auto e : edges)
        graph(e.first).push_back(e.second), graph(e.second).push_back(e.first);
    int cnt = 0;
    function<pair<int, point>(point, point)> dfs = [&](point p, point lock) {
        assert(cnt < w*h*4);
        assert(domino({0, 0}, p, {w-1, h-1}));
        cnt++;
        pair<int, point> c = {0, p};
        for(auto q : graph(p))
            if(q != lock)
        {
            auto cc = dfs(q, p);
            if(++cc.first > c.first)
                c = cc;
        }
        return c;
    };
    auto [d, s] = dfs({0, 0}, {-1, -1});
    cerr << "cnt = " << w*h << " =?= " << w*h << endl;
    assert(cnt == w*h);
    auto [k1, z] = dfs(s, {-1, -1});
    cerr << "k1 = " << k1 << " =?= " << k << endl;
    assert(k == k1);
}
#else
{
    (void)w; (void)h; (void)k; (void)edges;
}
#endif
