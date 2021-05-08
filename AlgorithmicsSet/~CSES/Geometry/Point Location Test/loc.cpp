#include <bits/stdc++.h>

using namespace std;

using vec = complex<int64_t>;

int64_t dot(vec a, vec b)
{
    return (conj(a) * b).real();
}
int64_t cross(vec a, vec b)
{
    return (conj(a) * b).imag();
}
template<typename T>
int sgn(T x) { return x > 0 ? +1 : (x < 0 ? -1 : 0); }

istream& operator>> (istream& in, vec& v)
{
    int64_t x, y;
    in >> x >> y;
    v = vec(x, y);
    return in;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        vec p, q, r;
        cin >> p >> q >> r;
        auto s = sgn(cross(q - p, r - p));
        if(s == +1)
            cout << "LEFT\n";
        else if(s == -1)
            cout << "RIGHT\n";
        else
            cout << "TOUCH\n";
    }
}
