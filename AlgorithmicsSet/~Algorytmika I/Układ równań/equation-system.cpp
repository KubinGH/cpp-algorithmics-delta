#include <bits/stdc++.h>
#include <ktl/math/gaussian_elimination.cpp>

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
