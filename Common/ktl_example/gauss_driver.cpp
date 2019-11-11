#include <bits/stdc++.h>
#include <ktl/math/gaussian_elimination.cpp>
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
