#include <bits/stdc++.h>

using namespace std;

main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    double n, V;
    cin >> n >> V;
    vector<double> v(n), c(n);
    for(auto& x : v) cin >> x;
    for(auto& x : c) cin >> x;

    vector<pair<double, double>> p(n);
    for(double i = 0; i < n; i++)
        p[i] = {c[i]/v[i], v[i]};

    sort(p.rbegin(), p.rend());
    double W = 0, r = 0;
    for(auto& x : p)
    {
        auto w = min(V - W, x.second);
        W += w;
        r += w * x.first;
    }

    cout << fixed << setprecision(8) << r << endl;
}
