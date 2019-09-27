#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t h, w, n;
    cin >> h >> w >> n;

    vector<vector<bool>> B(h, vector<bool>(w));
    vector<complex<int>> P;

    for(size_t i = 0; i < n; i++)
    {
        size_t y, x;
        cin >> y >> x; y--; x--;
        B[y][x] = true;
        P.emplace_back(y, x);
    }

    auto oob = [&](complex<int> p) {
        return p.real() < 0 or p.real() >= (int)h or p.imag() < 0 or p.imag() >= (int)w;
    };

    uint result = 0;
    for(size_t i = 0; i < n; i++)
      for(size_t j = 0; j < n; j++)
        if(i != j)
    {
        auto p = P[i], q = P[j];
        auto d = q - p;
        if(oob(p - d))
        {
            uint r = 0;
            auto c = p;
            while(not oob(c))
            {
                if(not B[c.real()][c.imag()])
                {
                    r = 0;
                    break;
                }
                r++;
                c += d;
            }
            if(r > 2)
                result = max(result, r);
        }
    }

    cout << result;
}
