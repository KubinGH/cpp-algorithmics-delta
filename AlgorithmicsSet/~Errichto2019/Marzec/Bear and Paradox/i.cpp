/*
A skąd wiadomo, że to była kurtyzana?

- A co ty głąbie, didaskaliów nie czytasz?
 [..]
- "Pokój cały pełen zwierciadeł"

KONIEC ANEGDOTY
*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cfloat>
#include <vector>

using namespace std;

using frac = pair<int, int>;

bool frac_cmp(const frac& lhs, const frac& rhs)
{
    const auto& [a, b] = lhs; const auto& [c, d] = rhs;
    return make_pair((int64_t)a * d, a) < make_pair((int64_t)c * b, c);
}
bool frac_eq(const frac& lhs, const frac& rhs)
{
    const auto& [a, b] = lhs; const auto& [c, d] = rhs;
    return (int64_t)a * d == (int64_t)b * c;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<frac> A(n);
    vector<int> P; P.reserve(n);
    int64_t T = 0;
    for(auto& [p, _] : A)
        cin >> p, P.push_back(p);
    for(auto& [_, t] : A)
        cin >> t, T += t;

    sort(A.rbegin(), A.rend(), frac_cmp);
    vector<vector<size_t>> groups = {{0}};
    for(size_t i = 1; i < n; i++)
    {
        if(not frac_eq(A[i], A[i-1]))
            groups.emplace_back();
        groups.back().push_back(i);
    }

    sort(P.begin(), P.end());
    P.erase(unique(P.begin(), P.end()), P.end());
    const size_t m = P.size();

    cout << fixed << setprecision(8);
    double lo = 0, hi = 1;
    while(hi - lo > 1e-10)
    {
        double c = (lo + hi) / 2;

        bool ok = true;

        int64_t T0 = 0;
        vector<pair<size_t, double>> conditions; conditions.reserve(n);
        vector<double> values(m+1, DBL_MAX);
        for(const auto& group : groups)
        {
            int64_t T1 = 0;
            for(auto i : group)
                T1 += A[i].second;
            for(auto i : group)
            {
                auto [p, t] = A[i];
                auto q = lower_bound(P.begin(), P.end(), p) - P.begin();
                values[q] = min(values[q], p*(1 - c*(T0 + T1) / T));
                conditions.emplace_back(q, p*(1 - c*(T0 + t) / T));
            }
            T0 += T1;
        }
        for(size_t i = m; i --> 0; )
            values[i] = min(values[i], values[i+1]);
        for(auto [q, v] : conditions)
            if(values[q + 1] < v)
                ok = false;

        if(ok)
            lo = c;
        else
            hi = c;
    }

    cout << lo << endl;
}
