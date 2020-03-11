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

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<pair<int, int>> A(n);
    int64_t T = 0;
    for(auto& [p, _] : A)
        cin >> p;
    for(auto& [_, t] : A)
        cin >> t, T += t;

    sort(A.rbegin(), A.rend(), [](const auto& lhs, const auto& rhs) {
        const auto& [a, b] = lhs; const auto& [c, d] = rhs;
        return make_pair((int64_t)a * d, a) < make_pair((int64_t)b * c, c);
    });


    double lo = 0, hi = 1;
    while(hi - lo > 1e-10)
    {
        double c = (lo + hi) / 2;

        bool ok = true;

        if(ok)
            lo = c + 1e-10;
        else
            hi = c;
    }

    cout << fixed << setprecision(7) << lo - 1e-10 << endl;
}
