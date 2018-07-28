#include <bits/stdc++.h>
#define X real()
#define Y imag()

using namespace std;


template<typename T>
T cross(const complex<T>& a, const complex<T>& b)
{
    return a.X * b.Y - b.X * a.Y;
}
template<typename T>
istream& operator>> (istream& in, complex<T>& o)
{
    T x, y;
    cin >> x >> y;
    o = {x, y};
    return in;
}
int64_t sign(int64_t x) { return (x >= 0) - (x <= 0); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    while(n --> 0)
    {
        complex<int64_t> a, b, c, d;
        cin >> a >> b >> c >> d;
        bool yes = false;
        /////
        if(yes)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}
