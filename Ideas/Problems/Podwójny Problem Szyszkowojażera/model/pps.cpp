#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 16;

struct point_t
{
    double x, y;
    point_t() : x(0), y(0) {}
    point_t(double x, double y) : x(x), y(y) {}
    bool operator< (const point_t& b) const
        { return tie(x, y) < tie(b.x, b.y); }
};
double hypot(point_t a, point_t b)
    { return hypot(a.x-b.x, a.y-b.y); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static point_t P[MAX_N];
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i].x >> P[i].y;
    static double R[1u << MAX_N][MAX_N];
    static uint32_t B[1u << MAX_N];
    for(uint32_t mask = 0; mask < (1u << n); mask++)
    {
        //cerr << bitset<4>(mask) << endl;
        B[mask] = n;
        if(mask == 0)
        {
            for(uint32_t i = 0; i < n; i++)
                R[mask][i] = 0;
            B[mask] = 0;
        }
        else for(uint32_t i = 0; i < n; i++)
        {
            R[mask][i] = 1e16;
            if(mask & (1u << i))
            {
                if((mask ^ (1u << i)) != 0) for(uint32_t j = 0; j < n; j++)
                {
                    double d = R[mask^(1u<<i)][j] + hypot(P[i], P[j]);
                    R[mask][i] = min(R[mask][i], d);
                }
                else
                    R[mask][i] = 0;
                if(B[mask] == n or R[mask][i] < R[mask][B[mask]])
                    B[mask] = i;
            }
            //cerr << i << ": " << R[mask][i] << endl;
        }
        //cerr << "-> " << R[mask][B[mask]] << endl;
    }
    double r = 1e16;
    for(uint32_t mask = 0; mask < (1u << n); mask++)
    {
        uint32_t xmask = mask ^ ((1u<<n)-1);
        r = min(r, R[mask][B[mask]] + R[xmask][B[xmask]]);
    }
    cout << fixed << setprecision(3) << r;
}
