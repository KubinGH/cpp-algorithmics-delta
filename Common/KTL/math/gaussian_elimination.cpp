// Gaussian elimination.
// Solves a system of linear equations. Transformations are done in-place on the provided 2D vector.
// Should adapt easily with mints.
// gaussian_elimination(a) performs the elimination on the matrix a in-place and
// returns the vector `where` of indices of non-zero element row in given column.
// solve_system_of_linear_equations(eq) returns solutions to the system of equations specified by the matrix `eq`.
// determinant(a) returns the determinant of the matrix a.

// Complexity: O(n^2 m), where n x m is the dimensions of the provided matrix (n rows, m columns).
// Last revision: April 2019

#pragma once

#include <cmath>
#include <vector>
#include <cstddef>
#include <cstdint>

#include "../ktl_debug_mode.cpp"
#ifdef _KTL_DEBUG
#include <algorithm>
using std::all_of;
#endif

using std::abs;
using std::vector;
using std::size_t;

using namespace std;

template<typename T>
bool gauss_is_zero(const T& v)
    { return v == T(0); }
template<>
bool gauss_is_zero<double>(const double& v)
    { return abs(v) < 1e-5; }
template<>
bool gauss_is_zero<long double>(const long double& v)
    { return abs(v) < 1e-10; }

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
vector<size_t> gaussian_elimination(vector<vector<T>>& a, size_t& swap_count)
{
    const size_t n = a.size();
    const size_t m = a[0].size() - 1;

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
                for(size_t j = col; j <= m; j++)
                    a[i][j] -= a[row][j] * c;
            }
        }
        row++;
    }
    return where;
}

template<typename T>
vector<size_t> gaussian_elimination(vector<vector<T>>& a)
{
    size_t _ = 0;
    return gaussian_elimination(a, _);
}

enum equation_system_status { None, Unique, Infinite };

template<typename T>
pair<equation_system_status, vector<T>> solve_system_of_linear_equations(vector<vector<T>> eq)
{
    const size_t n = eq.size();
    const size_t m = eq[0].size() - 1;

    auto where = gaussian_elimination(eq);

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
    auto where = gaussian_elimination(a, &swap_count);

    T result = 1;
    for(size_t i = 0; i < a.size(); i++)
        result *= a[i][i];

    return swap_count % 2 ? -result : result;
}

/*//$!$Driver
#include <bits/stdc++.h>
using namespace std;

int main()
{
    size_t n, m;
    cin >> n >> m;
    vector<vector<double>> equations(n, vector<double>(m+1));
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j <= m; j++)
            cin >> equations[i][j];

        for(size_t j = 0; j < m; j++)
            cout << equations[i][j] << char('a' + j) << (j+1 < m ? " + " : " = ");
        cout << equations[i][m] << endl;
    }

    auto response = solve_system_of_linear_equations(equations);
    auto status = response.first;
    const auto& solution = response.second;

    if(status == None)
        cout << "No solutions." << endl;
    else
    {
        cout << fixed << setprecision(3);
        for(size_t j = 0; j < m; j++)
            cout << char('a' + j) << " = " << solution[j] << endl;
        if(status == Unique)
            cout << "Solution is unique." << endl;
        else if(status == Infinite)
            cout << "Infinitely many solutions exist." << endl;
    }
}
*/
