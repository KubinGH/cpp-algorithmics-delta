#include <algorithm>
#include <iostream>
#include <bitset>
#include <random>
#include <vector>
#include <stack>
#include <map>

// Biblioteka KTL jest mojego autorstwa. Zaznaczam,
// ze jest ogolnodostepna w Internecie.

#include <ktl/math/modular.cpp>
#include <ktl/math/gaussian_elimination.cpp>

using namespace std;

const uint MOD = 1e9 + 7;

using mymint = mint<uint, MOD>;
using graph_t = vector<vector<size_t>>;

vector<vector<size_t>> get_components(const graph_t& graph)
{
    vector<bool> vis(graph.size());
    vector<size_t> run;
    function<void(size_t)> dfs = [&](size_t u) {
        run.push_back(u);
        vis[u] = true;
        for(auto v : graph[u])
            if(not vis[v])
                dfs(v);
    };
    vector<vector<size_t>> result;
    for(size_t u = 0; u < graph.size(); u++)
    {
        if(vis[u]) continue;
        dfs(u);
        result.push_back(run);
        run.clear();
    }
    return result;
}

bool randomness[64] = {
    0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
    1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1,
    1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0,
    0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0
};
struct disjoint_set
{
    struct save { size_t u, v, up, vsm, vom; };
    vector<size_t> parent, selfmask, outmask;
    vector<save> saves;

    disjoint_set(size_t n) : parent(n), selfmask(n), outmask(n)
    {
        iota(parent.begin(), parent.end(), 0);
        for(size_t i = 0; i < n; i++)
            selfmask[i] = 1 << i;
        saves.reserve(n);
    }
    size_t sets() const
    {
        return parent.size() - saves.size();
    }
    bool conn(size_t u, size_t v) const
    {
        return (outmask[u] & selfmask[v]) or (outmask[v] & selfmask[u]);
    }
    size_t find(size_t u) const
    {
        return u == parent[u] ? u : find(parent[u]);
    }
    bool unite(size_t u, size_t v)
    {
        static size_t no = 0;
        if((u = find(u)) != (v = find(v)))
        {
            if(randomness[no = (no+1)&63]) swap(u, v);
            saves.push_back({u, v, parent[u], selfmask[v], outmask[v]});
            parent[u] = v;
            selfmask[v] |= selfmask[u];
            outmask[v] |= outmask[u];
            return true;
        }
        else
            return false;
    }
    void rollback()
    {
        const auto& s = saves.back();
        parent[s.u] = s.up;
        selfmask[s.v] = s.vsm;
        outmask[s.v] = s.vom;
        saves.pop_back();
    }
};

namespace cycles
{

    map<uint, mymint> solve(graph_t graph, vector<uint> K)
    {
        vector<size_t> S;
        for(auto cc : get_components(graph))
            S.push_back(cc.size());

        sort(S.begin(), S.end());
        vector<pair<size_t, uint>> C = {{0, 0}};

        for(auto s : S)
        {
            if(C.back().first != s)
                C.emplace_back(s, 0);
            C.back().second++;
        }
        C.erase(C.begin());

        map<uint, mymint> answer;
        sort(K.begin(), K.end());
        for(auto k : K)
        {
            mymint result = 1;
            mymint l = k - 1;
            for(auto [s, c] : C)
                result *= power(power(l, s) + (s%2 ? -l : l), c);
            answer[k] = result;
        }

        return answer;
    }
}

namespace general
{
    const size_t MAX = 31;

    vector<bool> get_independent_sets(const graph_t& graph)
    {
        const size_t n = graph.size();
        array<size_t, MAX> nin;
        for(size_t u = 0; u < n; u++)
        {
            nin[u] = (1 << n) - 1;
            for(size_t v : graph[u])
                nin[u] &= ~(1 << v);
        }

        vector<bool> ind(1 << n, true);
        for(size_t mask = 1; mask < (1u << n); mask++)
        {
            for(size_t u = 0; u < n; u++)
              if((mask & (1 << u)) and (nin[u] & mask) != mask)
            {
                ind[mask] = false;
                break;
            }
        }

        return ind;
    }

    vector<mymint> k_colorings(const graph_t& graph)
    {
        const size_t n = graph.size();
        vector<mymint> A(1 << n), B = A;
        auto ind = get_independent_sets(graph);
        B[0] = 1;
        vector<mymint> result(n+1);
        for(size_t k = 1; k <= n; k++)
        {
            A[0] = 1;
            for(size_t mask = 1; mask < (1u << n); mask++)
            {
                A[mask] = 0;
                size_t sub = 0;
                do {
                    if(ind[sub])
                        A[mask] += B[mask ^ sub];
                } while((sub = (sub-1) & mask));
            }
            result[k] = A.back();
            swap(A, B);
        }
        return result;
    }

    void deletion_contraction_coloring(
        const vector<pair<size_t, size_t>>& edges,
        disjoint_set& dset, vector<mymint>& out, size_t i = 0, int sign = 1
    )
    {
        if(dset.sets() == 1)
            out[1] += sign;
        else if(i < edges.size())
        {
            auto [s, t] = edges[i];
            s = dset.find(s); t = dset.find(t);

            if(s != t and dset.conn(s, t))
            {
                auto ms = dset.outmask[s], mt = dset.outmask[t];
                dset.outmask[s] &= ~dset.selfmask[t];
                dset.outmask[t] &= ~dset.selfmask[s];
                deletion_contraction_coloring(edges, dset, out, i + 1, sign);
                dset.outmask[s] = ms;
                dset.outmask[t] = mt;

                dset.unite(s, t);
                deletion_contraction_coloring(edges, dset, out, i + 1, -sign);
                dset.rollback();
            }
            else
                deletion_contraction_coloring(edges, dset, out, i + 1, sign);
        }
        else
            out[dset.sets()] += sign;
    }

    vector<mymint> get_chromatic_polynomial_conn(const graph_t& graph)
    {
        const size_t n = graph.size();
        size_t m = 0;
        for(size_t u = 0; u < n; u++)
            m += graph[u].size();
        m /= 2;
        if((double)m/n > log2(3))
        {
            vector<vector<mymint>> eq(n+1, vector<mymint>(n+2));
            vector<mymint> Y = k_colorings(graph);
            for(size_t x = 0; x <= n; x++)
            {
                eq[x][0] = 1;
                for(size_t i = 1; i <= n; i++)
                    eq[x][i] = eq[x][i-1] * x;
                eq[x].back() = Y[x];
            }
            return solve_system_of_linear_equations(eq).second;
        }
        else
        {
            vector<pair<size_t, size_t>> edges;
            disjoint_set dset(n);
            for(size_t u = 0; u < n; u++)
                for(auto v : graph[u])
            {
                if(u < v)
                    edges.emplace_back(u, v);
                dset.outmask[u] |= 1 << v;
            }
            static mt19937 gen(42);
            shuffle(edges.begin(), edges.end(), gen);

            vector<mymint> coeff(n+1);
            deletion_contraction_coloring(edges, dset, coeff);
            return coeff;
        }
    }

    pair<vector<mymint>, uint> get_chromatic_polynomial(const graph_t& graph)
    {
        vector<mymint> P = {1};

        static mt19937 gen(1337);

        uint shift = 0;
        for(auto cc : get_components(graph))
        {
            shuffle(cc.begin(), cc.end(), gen);
            if(cc.size() == 1)
            {
                shift++;
                continue;
            }
            graph_t sub(cc.size());
            auto idx = [&](size_t u) {
                return find(cc.begin(), cc.end(), u) - cc.begin();
            };
            for(auto u : cc)
                for(auto v : graph[u])
                    sub[idx(u)].push_back(idx(v));

            auto Q = get_chromatic_polynomial_conn(sub);

            vector<mymint> R(P.size() + Q.size());
            for(size_t i = 0; i < P.size(); i++)
                for(size_t j = 0; j < Q.size(); j++)
                    R[i+j] += P[i] * Q[j];
            P = R;
        }

        return {P, shift};
    }

    map<uint, mymint> solve(graph_t graph, vector<uint> X)
    {
        auto [poly, shift] = get_chromatic_polynomial(graph);
        map<uint, mymint> answer;
        for(auto x : X)
        {
            mymint result = 0;
            for(size_t k = poly.size(); k --> 0; )
                result *= x, result += poly[k];

            result *= power(mymint(x), shift);
            answer[x] = result;
        }
        return answer;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    graph_t graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<uint> queries(q);
    for(auto& x : queries)
        cin >> x;

    map<uint, mymint> answer;

    if(all_of(graph.begin(), graph.end(), [&](const vector<size_t>& vec) {
        return vec.size() == 2;
    }))
        answer = cycles::solve(graph, queries);
    else
        answer = general::solve(graph, queries);

    for(auto x : queries)
        cout << answer[x] << '\n';
}
