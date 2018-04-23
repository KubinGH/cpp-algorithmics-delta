#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
const double EPSILON = 1e-7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << setprecision(6) << fixed;
    uint32_t n; double k;
    cin >> n >> k;
    static array<double, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    double lo = 0, hi = 1e18;
    while(hi - lo > EPSILON)
    {
        double x = (lo + hi) / 2;
        double ck = k;
        bool ok = true;
        for(uint32_t i = 0; i < n and ok; i++)
            ck -= ceil(A[i] / x);
        if(ck >= 0)
            hi = x;
        else
            lo = x + EPSILON;
    }
    cout << (lo + hi) / 2;
}
