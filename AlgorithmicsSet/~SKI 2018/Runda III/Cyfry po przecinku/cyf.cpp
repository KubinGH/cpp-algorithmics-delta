#include <bits/stdc++.h>

using namespace std;

#include <ext/numeric>
using __gnu_cxx::power;
template<typename T>
struct mod_multiplies : multiplies<T>
{
    T m; mod_multiplies(T m) : m(m) {}
    T operator() (T x, T y) const { return ((x%m) * (y%m)) % m; }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint64_t b, x, y, k;
        cin >> b >> x >> y >> k;
        uint64_t r = (power(b, k-1, mod_multiplies<uint64_t>(y)) * (x%y)) % y;
        cout << (b * r) / y << "\n";
    }
}
