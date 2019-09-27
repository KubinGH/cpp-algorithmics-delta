#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

int main()
{
    size_t n, t;
    uint g;
    cin >> n >> g >> t;

    vector<uint> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];

    uint64_t result = 0;

    auto pw = power(g, t);
    for(size_t _Tm_ = 0; _Tm_ < pw; _Tm_++)
    {
        size_t Tm = _Tm_;
        multiset<uint> L(A.begin(), A.end());
        uint r = 0;
        for(size_t i = 0; i < t; i++, Tm /= g)
        {
            uint x = Tm%g + 1;
            if(L.empty() or *(--L.end()) >= x)
            {
                auto it = L.lower_bound(x);
                L.erase(it);
                r += x;
            }
        }
        result += r;
    }

    cout << fixed << setprecision(10) << (long double)(result) / pw;
}
