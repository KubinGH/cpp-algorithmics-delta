#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 8;

struct point_t
{
    double x, y;
    point_t() : x(0), y(0) {}
    point_t(double x, double y) : x(x), y(y) {}
    bool operator< (const point_t& b) const
    {
        return tie(x, y) < tie(b.x, b.y);
    }
};
double hypot(point_t a, point_t b)
{
    return hypot(a.x-b.x, a.y-b.y);
}

int main()
{
    uint32_t n;
    cin >> n;
    if(n > MAX_N)
    {
        cout << "n exceeds MAX_N";
        return 0;
    }
    static point_t P[MAX_N];
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i].x >> P[i].y;
    static double R[1u << MAX_N];
    for(uint32_t mask = 0; mask < (1u << n); mask++)
    {
        R[mask] = 1e16;
        static point_t T[MAX_N];
        uint32_t t = 0;
        for(uint32_t i = 0; i < n; i++)
            if(mask & (1u << i))
                T[t++] = P[i];
        sort(T, T + t);
        if(t > 0) do {
            double c = 0;
            for(uint32_t i = 0; i < t - 1; i++)
                c += hypot(T[i], T[i+1]);
            R[mask] = min(R[mask], c);
        } while(next_permutation(T, T + t));
        else
            R[mask] = 0;
    }
    double r = R[(1u<<n)-1];
    for(uint32_t mask = 0; mask < (1u << n); mask++)
        r = min(r, R[mask] + R[mask ^ ((1u<<n)-1)]);
    cout << fixed << setprecision(3) << r;
}
