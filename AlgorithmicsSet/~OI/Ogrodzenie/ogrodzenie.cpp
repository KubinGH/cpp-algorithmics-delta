#include <bits/stdc++.h>
#define where if

using namespace std;

template<typename T>
using point_t = complex<T>;
#define X real()
#define Y imag()

template<typename T>
bool lexcomp (const point_t<T>& lhs, const point_t<T>& rhs)
{
    return lhs.X < rhs.X or (lhs.X == rhs.X and lhs.Y < rhs.Y);
}
bool plexcomp (const pair<point_t<int64_t>, int64_t>& lhs,
               const pair<point_t<int64_t>, int64_t>& rhs)
{
    return lexcomp(lhs.first, rhs.first) or (lhs.first == rhs.first and lhs.second < rhs.second);
}
template<typename T>
T ori(const point_t<T>& a, const point_t<T>& b, const point_t<T>& c)
{
    return sign((c.Y-a.Y) * (b.X-a.X) - (b.Y-a.Y) * (c.X-a.X));
}

int main()
{
    uint32_t n;
    cin >> n;
    vector<pair<point_t<int64_t>, int64_t>> in(n);
    for(uint32_t i = 0; i < n; i++)
    {
        int64_t x, y, v; cin >> x >> y >> v;
        in[i] = {{x, y}, v};
    }
    sort(in.begin(), in.end(), plexcomp);
    vector<point_t<int64_t>> P(n);
    vector<int64_t> V(n);
    for(uint32_t i = 0; i < n; i++)
        tie(P[i], V[i]) = in[i];
    assert(n <= 30);
    vector<vector<int64_t>> DP(1u << n, vector<int64_t>(n))[2];
    for(uint32_t p = 0; p < 2; p++)
    {
        for(uint32_t m = 1; m < (1u << n); m++)
        {
            if((m & (m-1)) == 0)
            {
                uint32_t i = 31 - __builtin_clz(m);
                DP[p][m][i] = V[i];
                continue;
            }
            else for(uint32_t i = 0; i < n; i++) where (m & (1u << i))
            {
                DP[p][m][i] = numeric_limits<int64_t>::min();
                for(uint32_t j = 0; j < n; j++) where ()
                    DP[p][m][i] = max(DP[p][m^(1u<<i)][j] + V[i], DP[p][m][i]);
            }
        }
        reverse(P.begin(), P.end());
        reverse(V.begin(), V.end());
    }
    for(uint32_t m = 1; m <)
}
