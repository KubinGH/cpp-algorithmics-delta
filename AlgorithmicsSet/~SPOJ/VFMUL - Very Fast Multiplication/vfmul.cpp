#include <bits/stdc++.h>
#include <ktl/math/fft.cpp>
#include <ktl/math/poly.cpp>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t q;
    cin >> q;
    while(q --> 0)
    {
        string s, z;
        cin >> s >> z;

        polynomial<long, rfft<long, double>> a(s.size()), b(z.size());
        for(size_t i = 0; i < s.size(); i++)
            a[s.size() - i - 1] = s[i] - '0';
        for(size_t i = 0; i < z.size(); i++)
            b[z.size() - i - 1] = z[i] - '0';

        auto c = a * b;

        for(size_t i = 0; i < c.P.size(); i++)
        {
            if(c[i] >= 10)
            {
                if(i == c.P.size() - 1)
                    c.P.push_back(0);
                c[i+1] += c[i] / 10;
            }
            c[i] %= 10;
        }
        if(c.P.empty())
            cout << 0;
        else for(size_t i = c.P.size(); i --> 0; )
            cout << c[i];
        cout << endl;
    }
}
