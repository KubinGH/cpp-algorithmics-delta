#include <bits/stdc++.h>

using namespace std;

typedef tuple<uint64_t, uint64_t, uint64_t, uint64_t> dt;

vector<uint64_t> get_divs_sqrt(uint64_t n)
{
    vector<uint64_t> result;
    for(uint32_t i = 1; i <= floor(sqrt(n)); i++)
        if(n % i == 0)
            result.push_back(i);
    return result;
}

ostream& operator<< (ostream& out, const dt& o)
{
    return out << "<" << get<0>(o) << ", " << get<1>(o)
               << ", " << get<2>(o) << ", " << get<3>(o) << ">";
}

int main()
{
    uint64_t n, k;
    cin >> n >> k; k--;
    set<dt> all;
    vector<uint64_t> divs = get_divs_sqrt(n);
for(uint64_t f = 0; f < 2; f++)
    for(uint64_t i = f ? divs.size() : 0;
        (not f and i < divs.size()) or (f and i --> 0);
        i += not f)
    {
        uint64_t d = f ? n / divs[i] : divs[i];
        for(uint64_t x : get_divs_sqrt(d)) for(uint64_t y : get_divs_sqrt(n / d))
        {
            uint64_t a = d / x, b = n / (d*y);
            all.insert(make_tuple(a, x, b, y));
            all.insert(make_tuple(a, x, y, b));
            all.insert(make_tuple(x, a, b, y));
            all.insert(make_tuple(x, a, y, b));
        }
    }
    uint64_t i = 0;
    for(dt o : all)
    {
        if(i == k)
        {
            cout << get<0>(o) << " " << get<1>(o) << " "
                 << get<2>(o) << " " << get<3>(o);
            return 0;
        }
        i++;
    }
    cout << "NIE";
}
