#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

struct circle { int64_t x, y, r; };

bool intersect_nz(const circle& a, const circle& b)
{
    return power(a.r+b.r, 2) > power(a.x-b.x, 2) + power(a.y-b.y, 2);
}

int main()
{
    size_t n;
    cin >> n;

    vector<circle> P(n);
    for(auto& p : P)
        cin >> p.x >> p.y >> p.r;

    int result = 0;
    for(size_t i = 0; i < n; i++)
        for(size_t j = i+1; j < n; j++)
            result += intersect_nz(P[i], P[j]);
    cout << result;
}
