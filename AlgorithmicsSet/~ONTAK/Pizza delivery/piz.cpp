#include <bits/stdc++.h>

using namespace std;

const size_t N = 2048;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

vector<int64_t> sssp(size_t src, const vector<vector<pair<size_t, int>>>& graph)
{
    const size_t n = graph.size();

    vector<int64_t> dist(n, INT64_MAX / 3);
    vector<bool> lock(n);
    min_priority_queue<pair<int64_t, size_t>> Q;

    auto maybe = [&](size_t u, int64_t d) {
        if(d < dist[u])
            dist[u] = d, Q.emplace(d, u);
    };
    maybe(src, 0);
    while(not Q.empty())
    {
        size_t u = Q.top().second; Q.pop();
        if(lock[u]) continue;
        lock[u] = true;
        for(auto e : graph[u])
            maybe(e.first, dist[u] + e.second);
    }

    return dist;
}

template<typename F>
size_t predicate_search(size_t lo, size_t hi, F f)
{
    while(lo < hi)
    {
        auto mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, a, b;
    cin >> n >> m >> a >> b;
    a--; b--;

    int64_t w_sum = 0;
    vector<int> W(n);
    for(auto& p : W)
        cin >> p, w_sum += p;

    vector<vector<pair<size_t, int>>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int w;
        cin >> u >> v >> w; u--; v--;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    auto dpairs = [&](size_t s) {
        auto D = sssp(s, graph);
        vector<pair<int64_t, size_t>> pr;
        for(size_t i = 0; i < n; i++)
            pr.emplace_back(D[i], i);
        sort(pr.begin(), pr.end());
        return pr;
    };

    auto A = dpairs(a), B = dpairs(b);

    vector<size_t> atA(n), atB(n), brA = {0}, brB = {0};
    for(size_t i = 0; i < n; i++)
    {
        atA[A[i].second] = i, atB[B[i].second] = i;
    }
    for(size_t i = 1; i < n; i++)
    {
        if(A[i].first != A[i-1].first)
            brA.push_back(i);
        if(B[i].first != B[i-1].first)
            brB.push_back(i);
    }
    brA.push_back(n);
    brB.push_back(n);



    static size_t left[N][N];
    static int64_t left_w[N][N];
    for(size_t p = 0; p <= n; p++)
    {
        vector<bool> ex(n);
        left  [p][0] = n - p;
        left_w[p][0] = w_sum;
        for(size_t i = 0; i < p; i++)
            ex[A[i].second] = true, left_w[p][0] -= W[A[i].second];
        for(size_t q = 0; q < n; q++)
        {
            left  [p][q+1] = left  [p][q];
            left_w[p][q+1] = left_w[p][q];
            if(not ex[B[q].second])
            {
                ex[B[q].second] = true;
                left  [p][q+1]--;
                left_w[p][q+1] -= W[B[q].second];
            }
        }
    }

    static bool done[2][N][N];
    static int64_t cache[2][N][N];

    function<int64_t(bool, size_t, size_t)> optimal = [&](bool snd, size_t p, size_t q) {
        if(done[snd][p][q])
            return cache[snd][p][q];
        done[snd][p][q] = true;

        if(left[p][q] == 0)
            return cache[snd][p][q] = 0;

        int64_t r = INT64_MIN;
        if(not snd)
        {
            auto bp = lower_bound(brA.begin(), brA.end(), p+1) - brA.begin();
            size_t p1 = brA[predicate_search(bp, brA.size(), [&](size_t x) {
                return left[brA[x]][q] < left[p][q];
            })];
            r = (left_w[p][q] - left_w[p1][q]) + max(left_w[p1][q] - optimal(1, p1, q), optimal(0, p1, q));
        }
        else
        {
            auto bq = lower_bound(brB.begin(), brB.end(), q+1) - brB.begin();
            size_t q1 = brB[predicate_search(bq, brB.size(), [&](size_t x) {
                return left[p][brB[x]] < left[p][q];
            })];
            r = (left_w[p][q] - left_w[p][q1]) + max(left_w[p][q1] - optimal(0, p, q1), optimal(1, p, q1));
        }
        return cache[snd][p][q] = r;
    };

    auto s = optimal(0, 0, 0);
    cout << s << ' ' << w_sum-s << endl;
}
