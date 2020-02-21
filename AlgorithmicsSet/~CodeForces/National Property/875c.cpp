#include <bits/stdc++.h>
#include <ktl/general/2sat.cpp>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<int>> seq(n);
    for(auto& s : seq)
    {
        size_t k;
        cin >> k;
        s.resize(k);
        for(auto& x : s)
            cin >> x;
    }

    auto fail = []() {
        cout << "No" << endl;
        exit(0);
    };

    solver_2sat sat(m);

    for(size_t i = 0; i+1 < n; i++)
    {
        const auto& A = seq[i]; auto a = A.size();
        const auto& B = seq[i+1]; auto b = B.size();

        if(a > b and equal(B.begin(), B.end(), A.begin()))
            fail();
        else if(a <= b and equal(A.begin(), A.end(), B.begin()))
            {}
        else
        {
            auto [ita, itb] = mismatch(A.begin(), A.end(), B.begin());
            auto x = *ita, y = *itb;
            if(x < y)
                sat.add_or_clause(x, -y);
            else
                sat.force_true(x), sat.force_false(y);
        }
    }

    if(auto solution = sat.solve(); solution.exists)
    {
        cout << "Yes" << endl;
        cout << count(solution.value.begin(), solution.value.end(), true) << endl;
        for(size_t i = 0; i < m; i++)
            if(solution.value[i])
                cout << i+1 << ' ';
    }
    else
        fail();
}
