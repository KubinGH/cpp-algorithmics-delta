#include <bits/stdc++.h>
#include <ktl/math/modular.cpp>
#include <ktl/math/gaussian_elimination.cpp>

using namespace std;

using mymint = mint<uint32_t, 0>;

int main()
{
    size_t n; uint32_t p;
    cin >> n >> p;
    mint_global_mod(p);

    vector<vector<mymint>> eq(n+1, vector<mymint>(n+2));
    for(size_t i = 0; i <= n; i++)
    {
        mymint x, y;
        cin >> x >> y;
        mymint xj = 1;
        for(size_t j = 0; j <= n; j++, xj *= x)
            eq[i][j] = xj;
        eq[i][n+1] = y;
    }

    auto result = solve_system_of_linear_equations(eq);

    assert(result.first != None);

    for(auto& sol : result.second)
        cout << sol << '\n';
}
