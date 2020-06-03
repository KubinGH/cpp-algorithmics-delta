#include <bits/stdc++.h>

// -*- ktl/ktl_debug_mode.cpp -*-

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

// -$- ktl/ktl_debug_mode.cpp -$-

// -*- ktl/math/gaussian_elimination.cpp -*-

#include <cmath>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <utility>
#ifdef _KTL_DEBUG
#include <algorithm>
using std::all_of;
#endif

using std::abs;
using std::vector; using std::pair;
using std::size_t;

template<typename T>
bool gauss_is_zero(const T& v)
    { return v == T(0); }
template<>
bool gauss_is_zero<double>(const double& v)
    { return abs(v) < 1e-5; }
template<>
bool gauss_is_zero<long double>(const long double& v)
    { return abs(v) < 1e-5; }

template<typename T>
bool gauss_compare_sel(const T& a, const T& b)
    { return a < b; }
template<>
bool gauss_compare_sel<double>(const double& a, const double& b)
    { return abs(a) < abs(b); }
template<>
bool gauss_compare_sel<long double>(const long double& a, const long double& b)
    { return abs(a) < abs(b); }

template<typename T>
vector<size_t> gaussian_elimination(vector<vector<T>>& a, size_t& swap_count, size_t augment)
{
    const size_t n = a.size();
    const size_t m = a[0].size() - augment;

    KTL_DEBUG_ASSERT(all_of(a.begin(), a.end(), [&](const vector<T>& v) { return a[0].size() == v.size(); }));

    vector<size_t> where (m, SIZE_MAX);
    for(size_t col = 0, row = 0; col < m and row < n; col++)
    {
        size_t select = row;
        for(size_t i = row; i < n; i++)
            if(gauss_compare_sel(a[select][col], a[i][col]))
                select = i;

        if(gauss_is_zero(a[select][col]))
            continue;

        a[row].swap(a[select]);
        if(row != select)
            swap_count++;
        where[col] = row;

        for(size_t i = 0; i < n; i++)
        {
            if(i != row)
            {
                T c = a[i][col] / a[row][col];
                for(size_t j = col; j < m+augment; j++)
                    a[i][j] -= a[row][j] * c;
            }
        }
        row++;
    }
    return where;
}

template<typename T>
vector<size_t> gaussian_elimination(vector<vector<T>>& a, size_t augment = 0)
{
    size_t _ = 0;
    return gaussian_elimination(a, _, augment);
}

enum equation_system_status { None, Unique, Infinite };

template<typename T>
pair<equation_system_status, vector<T>> solve_system_of_linear_equations(vector<vector<T>> eq)
{
    const size_t n = eq.size();
    const size_t m = eq[0].size() - 1;

    auto where = gaussian_elimination(eq, 1);

    vector<T> solution(m, 0);

    for(size_t i = 0; i < m; i++)
        if(where[i] != SIZE_MAX)
            solution[i] = eq[where[i]][m] / eq[where[i]][i];

    for(size_t i = 0; i < n; i++)
    {
        T sum = 0;
        for(size_t j = 0; j < m; j++)
            sum += solution[j] * eq[i][j];
        if(not gauss_is_zero(sum - eq[i][m]))
            return {None, {}};
    }

    for(size_t i = 0; i < m; i++)
        if(where[i] == SIZE_MAX)
            return {Infinite, solution};

    return {Unique, solution};
}

template<typename T>
T determinant(vector<vector<T>> a)
{
    KTL_DEBUG_ASSERT(a.size() == a[0].size());

    size_t swap_count = 0;
    auto where = gaussian_elimination(a, swap_count, 0);

    T result = 1;
    for(size_t i = 0; i < a.size(); i++)
        result *= a[i][i];

    return swap_count % 2 ? -result : result;
}

// -$- ktl/math/gaussian_elimination.cpp -$-


using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<long double>> eq(n, vector<long double>(m+1));
    for(auto& row : eq)
        for(auto& val : row)
            cin >> val;

    auto result = solve_system_of_linear_equations(eq);

    assert(result.first != None);

    cout << fixed << setprecision(6);
    for(auto& sol : result.second)
        cout << sol << '\n';
}
