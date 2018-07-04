#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

double atan2(pair<int32_t, int32_t> p)
    { return atan2(p.second, p.first); }
double atan2_comp(pair<int32_t, int32_t> p1, pair<int32_t, int32_t> p2)
{
    return atan2(p1) < atan2(p2) or (atan2(p1) == atan2(p2) and p1 < p2);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static pair<int32_t, int32_t> V[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> V[i].first >> V[i].second;
    sort(V, V + n, atan2_comp);
    static int32_t X[MAX], Y[MAX];
    static int32_t SX[MAX+1], SY[MAX+1];
    for(uint32_t i = 0; i < n; i++)
    {
        tie(X[i], Y[i]) = V[i];
        SX[i+1] = SX[i] + X[i];
        SY[i+1] = SY[i] + Y[i];
    }
    auto sum_x = [&](uint32_t i, uint32_t j) {
        if(i <= j)
            return SX[j+1] - SX[i];
        else
            return SX[n] + SX[j+1] - SX[i];
    };
    auto sum_y = [&](uint32_t i, uint32_t j) {
        if(i <= j)
            return SY[j+1] - SY[i];
        else
            return SY[n] + SY[j+1] - SY[i];
    };
    auto get = [&](uint32_t i, uint32_t j) {
        uint64_t sx = sum_x(i, j), sy = sum_y(i, j);
        return sx*sx + sy*sy;
    };
    uint64_t result = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t lo = 0, hi = n;
        while(lo < hi)
        {
            uint32_t d = (lo+hi)/2;
            result = max(result, get(i, (i+d)%n));
            if(d == 0 or get(i, (i+d-1)%n) <= get(i, (i+d)%n))
                lo = d + 1;
            else
                hi = d;
        }
    }
    cout << result;
}
