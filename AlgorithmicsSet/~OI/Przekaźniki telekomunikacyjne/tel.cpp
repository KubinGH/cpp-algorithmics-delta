#include <bits/stdc++.h>

using namespace std;

template<typename Argument, typename Function>
Argument partition_point(Function f, Argument lo, Argument hi)
{
    while(lo < hi)
    {
        size_t mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

struct query
{
    char t;
    size_t x, y;
    int s, a;
    size_t i;
};

struct tower
{
    int s, a;
};

void divida_et_impera(const vector<query>& queries, vector<int64_t>& answer, size_t L, size_t R)
{
    if(R - L <= 1) return;

    size_t M = (L + R) / 2;
    divida_et_impera(queries, answer, L, M);
    divida_et_impera(queries, answer, M, R);

    vector<size_t> indices; indices.reserve((R - L) * 4);

    for(size_t i = L; i < R; i++)
    {
        const auto& q = queries[i];
        if(q.x)
            indices.push_back(q.x-1);
        indices.push_back(q.x);
        if(q.y)
            indices.push_back(q.y-1);
        indices.push_back(q.y);
    }

    sort(indices.begin(), indices.end());
    indices.erase(unique(indices.begin(), indices.end()), indices.end());

    size_t n = indices.size();

    static size_t ico[1 << 20];
    for(size_t i = 0; i < n; i++)
        ico[indices[i]] = i;

    vector<int64_t> S(n);
    vector<int> A(n);
    for(size_t i = L; i < M; i++)
        if(queries[i].t == '+')
    {
        const auto& q = queries[i];
        S[ico[q.x]] += q.s;
        S[ico[q.y]] -= q.s + q.a * int64_t(q.y - q.x);
        A[ico[q.x]] += q.a;
        A[ico[q.y]] -= q.a;
    }

    vector<int64_t> w(n);

    int64_t s = 0, a = 0;
    for(size_t i = 0; i < n; i++)
    {
        int64_t d = i ? indices[i] - indices[i-1] : 1;
        w[i] = s * d + a * (d*(d+1)/2) + S[i];
        s += S[i] + a * d;
        a += A[i];
    }

    vector<int64_t> z(n+1);
    partial_sum(w.begin(), w.end(), z.begin() + 1);

    for(size_t i = M; i < R; i++)
        if(queries[i].t == '?')
            answer[queries[i].i] += z[ico[queries[i].y]] - z[ico[queries[i].x]];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<tower> last_tower(n);
    vector<query> queries; queries.reserve(2 * m);

    auto make_tower = [&](size_t p, int s, int a) {
        int ip = p;
        size_t i = partition_point<int64_t>([&](int x) {
            return s / a >= ip - x;
        }, 0, n);

        size_t j = partition_point<int64_t>([&](int x) {
            return s / a < x - ip;
        }, 0, n);

        return make_pair(
            query {'+', i, p, s - (ip - (int)i)*a, a, SIZE_MAX},
            query {'+', p, j, s, -a, SIZE_MAX}
        );
    };

    vector<int64_t> query_index, answer;
    for(size_t i = 0; i < m; i++)
    {
        char t;
        cin >> t;
        if(t == 'P')
        {
            size_t p; int s, a;
            cin >> p >> s >> a; p--;
            auto d = make_tower(p, s, a);
            queries.push_back(d.first);
            queries.push_back(d.second);
            last_tower[p] = {s, a};
        }
        else if(t == 'U')
        {
            size_t p;
            cin >> p; p--;
            auto d = make_tower(p, last_tower[p].s, last_tower[p].a);
            d.first.s = -d.first.s; d.first.a = -d.first.a;
            d.second.s = -d.second.s; d.second.a = -d.second.a;
            queries.push_back(d.first);
            queries.push_back(d.second);
            last_tower[p] = {0, 0};
        }
        else if(t == 'Z')
        {
            size_t x, y;
            cin >> x >> y; x--;
            query_index.push_back(queries.size());
            queries.push_back({'?', x, y, 0, 0, answer.size()});
            answer.emplace_back();
        }
    }

    divida_et_impera(queries, answer, 0, queries.size());

    for(size_t ii = 0; ii < answer.size(); ii++)
    {
        size_t i = query_index[ii];
        cout << answer[ii] / (queries[i].y - queries[i].x) << '\n';
    }
}
