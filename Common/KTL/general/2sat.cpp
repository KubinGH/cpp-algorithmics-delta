// Simple 2-SAT solver with Kosaraju's algorithm. O(n) complexity.
// Returns a solution if one exists.
// Clauses are provided in a 1-indexed form, and the negation is the
// arithmetical negation.
// add_or_clause(-1, 2) adds (!a_1 v a_2).

// Last revision: April 2019

#pragma once

#include <vector>
#include <cstddef>
#include <algorithm>
#include "../graph/kosaraju.cpp"

using std::vector;
using std::size_t;
using std::reverse;

struct solver_2sat
{
    size_t n;
    vector<vector<size_t>> imp_graph;

    solver_2sat(size_t _n) : n(_n), imp_graph(2*n) {}

    static constexpr size_t as_index(int32_t p)
    {
        return p < 0 ? 2*(-p-1) + 1 : 2*(p-1);
    }

    void add_implication(int32_t a, int32_t b)
    {
        imp_graph[as_index(a)].push_back(as_index(b));
    }
    void add_or_clause(int32_t a, int32_t b)
    {
        add_implication(-a, b);
        add_implication(-b, a);
    }
    void add_xnor_clause(int32_t a, int32_t b)
    {
        add_or_clause(a, -b);
        add_or_clause(-a, b);
    }
    void add_xor_clause(int32_t a, int32_t b)
    {
        add_or_clause(a, b);
        add_or_clause(-a, -b);
    }

    struct solution_2sat { bool exists; vector<bool> value; };
    solution_2sat solve()
    {
        auto pscc = kosaraju{imp_graph}();
        auto scc = pscc.first; auto scc_idx = pscc.second;
        const size_t s = scc.size();
        for(size_t u = 0; u < 2*n; u += 2)
        {
            if(scc_idx[u] == scc_idx[u^1])
                return {false, {}};
        }

        vector<bool> is_set(s), truth_value(s);
        for(size_t u = s; u --> 0; )
        {
            if(not is_set[u])
                is_set[u] = true, truth_value[u] = true;
            for(size_t i : scc[u])
            {
                size_t v = scc_idx[i^1];
                is_set[v] = true; truth_value[v] = not truth_value[u];
            }
        }
        vector<bool> out(n);
        for(size_t i = 0; i < n; i++)
            out[i] = truth_value[scc_idx[2*i]];
        return {true, out};
    }
};