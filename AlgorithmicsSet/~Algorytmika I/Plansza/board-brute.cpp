#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<size_t> px(m), py(m);
    for(size_t i = 0; i < m; i++)
        cin >> px[i] >> py[i], px[i]--, py[i]--;

    for(size_t mask = 0; mask < (1u << m); mask++)
    {
        vector<int> x(n), y(n);
        for(size_t i = 0; i < m; i++)
        {
            int c = (mask >> i & 1) ? 1 : -1;
            x[px[i]] += c;
            y[px[i]] += c;
        }
        bool ok = true;
        for(size_t i = 0; i < n; i++)
            if(abs(x[i]) > 1 or abs(y[i]) > 1)
                ok = false;
        if(ok)
        {
            cout << "TAK\n";
            for(size_t i = 0; i < m; i++)
                cout << ((mask >> i & 1) ? 1 : -1) << '\n';
            return 0;
        }
    }
    cout << "NIE";
}
