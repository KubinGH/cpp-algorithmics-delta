#include <bits/stdc++.h>
#include <ktl/util/extio.cpp>
#include <ktl/util/debug_macros.cpp>
#include <ktl/structures/disjoint_set.cpp>

using namespace std;

const size_t K = 64, L = 256;

using uint = unsigned;

struct point { int x, y; };

bool operator< (const point& lhs, const point& rhs) { return tie(lhs.x, lhs.y) < tie(rhs.x, rhs.y); }
ostream& operator<< (ostream& out, const point& p) { return out << make_pair(p.x, p.y); }

struct line
{
    int a, b, c;
    int operator() (const point& p)
    {
        return a*p.x + b*p.y + c;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    if(n == 1) { cout << 0; return 0; }

    vector<point> points(n);

    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    auto randint = [&](int lo, int hi) {
        return uniform_int_distribution<int>{lo, hi}(gen);
    };

    set<point> rep;
    int m = 0;
    for(size_t i = 0; i < n; i++)
    {
        //cin >> points[i].x >> points[i].y;
        do {
            points[i] = {randint(0, 30000), randint(0, 30000)};
        } while(rep.find(points[i]) != rep.end());
        rep.insert(points[i]);
        cout << points[i].x << " " << points[i].y << endl;

        m = max(m, max(points[i].x, points[i].y));
    }

    auto d = [&](size_t i, size_t j) {
        return hypot(points[i].x-points[j].x, points[i].y-points[j].y);
    };

    auto random_line = [&]() {
        size_t i = randint(0, n - 1), j;
        do {
            j = randint(0, n - 1);
        } while(i == j);
        auto p = points[i], q = points[j];
        auto l = line {p.y - q.y, q.x - p.x, p.x*q.y - q.x*p.y};
        assert(l(p) == 0 and l(q) == 0);
        return l;
    };

    auto hashie = [&](size_t k) {
        vector<line> lines(k);
        generate(lines.begin(), lines.end(), random_line);
        map<uint64_t, vector<size_t>> groups;
        for(size_t i = 0; i < n; i++)
        {
            uint64_t mask = 0;
            for(size_t j = 0; j < k; j++)
                if(lines[j](points[i]) >= 0)
                    mask |= (1ull << j);
            groups[mask].push_back(i);
        }
        return groups;
    };

    vector<size_t> closest(n, 0); closest[0] = 1;
    for(size_t run = 0; run < L; run++)
    {
        cdbg << note(run) << endl;
        auto groups = hashie(K);
        for(const auto& g : groups)
        {
            const auto& pt = g.second;
            cdbg << '\r' << note(pt.size());
            for(size_t ii = 0; ii < pt.size(); ii++)
                for(size_t jj = 0; jj < pt.size(); jj++)
            {
                size_t i = pt[ii], j = pt[jj];
                if(i != j and d(i, j) < d(i, closest[i]))
                        closest[i] = j;
            }
        }
        cdbg << endl;
        for(size_t t = 0; t < 64; t++)
        {
            size_t i = randint(0, n - 1);
            size_t w = i == 0 ? 1 : 0;
            for(size_t j = 0; j < n; j++)
                if(i != j and d(i, j) < d(i, w))
                    w = j;
            if(w != closest[i])
            {
                cdbg << "fail " << t << ": " << i << " " << w << " " << closest[i] << endl;
                break;
            }
        }
    }

    disjoint_set dset(n);
    size_t r = n;
    for(size_t i = 0; i < n; i++)
        if(dset.unite(i, closest[i]))
            r--;
    cout << r;
}
