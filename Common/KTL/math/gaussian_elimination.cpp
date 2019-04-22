// Gaussian elimination.
// Solves a system of linear equations. Transformations are done in-place on the provided 2D vector.
// Should adapt easily with mints (gauss_compare_sel should probably be overloaded).
// Complexity: O(n^2 m), where n x m is the dimensions of the provided matrix (n rows, m columns).
// Last revision: April 2019

#include <cmath>
#include <vector>
#include <cstddef>
#include <cstdint>

using std::abs;
using std::vector;
using std::size_t;

using namespace std;

enum gauss_result { None, Unique, Infinite };

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
pair<gauss_result, vector<T>> gaussian_elimination(vector<vector<T>>& a)
{
    const size_t n = a.size();
    const size_t m = a[0].size() - 1;

    vector<T> solution(m, 0);

    vector<size_t> where (m, SIZE_MAX);
    for(size_t col=0, row=0; col < m and row < n; col++)
    {
        size_t select = row;
        for(size_t i = row; i < n; i++)
            if(gauss_compare_sel(a[select][col], a[i][col]))
                select = i;

        if(gauss_is_zero(a[select][col]))
            continue;

        for(size_t i = col; i <= m; i++)
            swap(a[select][i], a[row][i]);

        where[col] = row;

        for(size_t i=0; i<n; ++i)
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

    for(size_t i = 0; i < m; i++)
        if(where[i] != SIZE_MAX)
            solution[i] = a[where[i]][m] / a[where[i]][i];

    for(size_t i = 0; i < n; i++)
    {
        T sum = 0;
        for(size_t j = 0; j < m; j++)
            sum += solution[j] * a[i][j];
        if(not gauss_is_zero(sum - a[i][m]))
            return {None, {}};
    }

    for(size_t i = 0; i < m; i++)
        if(where[i] == SIZE_MAX)
            return {Infinite, solution};

    return {Unique, solution};
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

    auto response = gaussian_elimination(equations);
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
