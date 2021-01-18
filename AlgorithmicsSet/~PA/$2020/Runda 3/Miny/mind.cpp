#include <bits/stdc++.h>
#include <ktl/graph/kosaraju.cpp>

// #define DEBUG

#ifdef DEBUG
#define cdbg cerr
#else
struct __cdbg { template<typename T> const __cdbg& operator<< (const T& x) const { (void)x; return *this; } } cdbg;
#endif

using namespace std;

constexpr uint mod = 1e9 + 7;

vector<vector<size_t>> construct_explosion_graph(
    const vector<int64_t>& A, const vector<int64_t>& R)
{
    const size_t n = A.size();

    const size_t w = 1 << __lg(2*n - 1);
    auto segments = [&](size_t l, size_t r) {
        vector<size_t> nodes;
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) nodes.emplace_back(l++);
            if(r % 2) nodes.emplace_back(--r);
        }
        return nodes;
    };

    vector<vector<size_t>> graph(2*w);
    for(size_t i = 0; i < n; i++)
    {
        size_t l = lower_bound(A.begin(), A.end(), A[i] - R[i]) - A.begin(),
               r = upper_bound(A.begin(), A.end(), A[i] + R[i]) - A.begin();
        for(auto v : segments(l, r))
            graph[i + w].push_back(v), cdbg << i+w << " -> " << v << '\n';
    }
    for(size_t i = 1; i < w; i++)
        graph[i].push_back(2*i), graph[i].push_back(2*i+1);

    return graph;
}

vector<pair<size_t, size_t>> get_explosion_intervals(
    size_t n, const vector<vector<size_t>>& graph)
{
    const size_t w = graph.size() / 2;

    kosaraju kosa(graph);
    auto [scc, scc_idx] = kosa();
    auto scc_graph = kosa.make_scc_graph(scc, scc_idx);

    for(auto& c : scc)
    {
        cdbg << scc_idx[c[0]] << ": ";
        for(auto u : c)
            cdbg << u << "; ";
        cdbg << '\n';
    }

    const size_t s = scc.size();
    vector<bool> exists(s);
    vector<size_t> left(s, n), right(s, 0);
    vector<pair<size_t, size_t>> intervals;
    for(size_t i = s; i --> 0; )
    {
        for(auto u : scc[i])
          if(w <= u and u < w+n)
        {
            exists[i] = true;
            left [i] = min(left [i], u-w);
            right[i] = max(right[i], u-w);
        }

        for(auto j : scc_graph[i])
        {
             left[i] = min( left[i],  left[j]);
            right[i] = max(right[i], right[j]);
        }

        if(exists[i])
            intervals.emplace_back(left[i], right[i]);
    }

    return intervals;
}

uint count_nondominated_subsets_masks(size_t m, vector<pair<size_t, size_t>> I)
{
    (void)m;
    const size_t n = I.size();

    uint result = 0;
    for(size_t mask = 0; mask < (1u << n); mask++)
    {
        bool ok = true;
        for(size_t i = 0; i < n; i++)
            for(size_t j = 0; j < n; j++)
                if(i != j and (mask >> i & 1) and (mask >> j & 1) and
                  I[i].first <= I[j].first and I[j].second <= I[i].second)
                   ok = false;
        result += ok;
    }

    return result;
}

uint count_nondominated_subsets_quadratic(size_t m, vector<pair<size_t, size_t>> I)
{
    const size_t n = I.size();

    sort(I.begin(), I.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first or (lhs.first == rhs.first and lhs.second > rhs.second);
    });
    vector<vector<uint>> Q(n+1, vector<uint>(m+1));
    fill(Q[n].begin(), Q[n].end(), 1);
    for(size_t i = n; i --> 0; )
    {
        cdbg << I[i].first << ".." << I[i].second << '\n';
        Q[i] = Q[i+1];
        for(size_t r = 0; r <= I[i].second; r++)
            Q[i][r] += Q[i+1][I[i].second+1];
        cdbg << " ";
        for(auto x : Q[i])
            cdbg << x << " ";
        cdbg << '\n';
    }

    return Q[0][0];
}

struct fenwick_tree
{
    size_t n;
    vector<size_t> F;

    fenwick_tree(size_t m) : n(m), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    uint get_prefix(size_t p) const
    {
        uint r = 0;
        while(p)
            r = (r + F[p]) % mod, p -= lsb(p);
        return r;
    }

    void delta(size_t p, uint v)
    {
        p++;
        while(p <= n)
            F[p] = (F[p] + v) % mod, p += lsb(p);
    }
};

uint count_nondominated_subsets(size_t m, vector<pair<size_t, size_t>> I)
{
    const size_t n = I.size();

    sort(I.begin(), I.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first or (lhs.first == rhs.first and lhs.second > rhs.second);
    });
    fenwick_tree F(m+1);
    F.delta(0, +1);
    for(size_t i = n; i --> 0; )
    {
        auto v = F.get_prefix(I[i].second+1 + 1);
        F.delta(0, v); F.delta(I[i].second+1, mod-v);
    }

    return F.get_prefix(0 + 1);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n0;
    cin >> n0;
    vector<int64_t> A(n0), R(n0);
    for(size_t i = 0; i < n0; i++)
        cin >> A[i] >> R[i];

    cout << count_nondominated_subsets(n0, get_explosion_intervals(n0, construct_explosion_graph(A, R))) << endl;
}
