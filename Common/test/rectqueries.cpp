#include <bits/stdc++.h>
#include <ktl/structures/fenwick_multi.cpp>

using namespace std;

int main()
{
    const size_t w = 16, h = 16;
    dfenwick_tree<int, 2> f1(h, w), f2(h, w);

    auto get_prefix = [&](int x, int y) {
        return (x-1)*(y-1)*f1.get_prefix(x, y) - f2.get_prefix(x, y);
    };
    auto get = [&](int x1, int y1, int x2, int y2) {
        return get_prefix(x2, y2) + get_prefix(x1, y1) - get_prefix(x1, y2) - get_prefix(x2, y1);
    };
    auto delta = [&](int v, int x1, int y1, int x2, int y2) {
        f1.delta(v, x1, y1);
        f1.delta(v, x2, y2);
        f1.delta(-v, x1, y2);
        f1.delta(-v, x2, y1);
        //f1.delta(-v, x1+1, y1);
        //f1.delta(-v, x1, y1+1);
        //f1.delta(2*v, x1+1, y1+1);
        //f1.delta(v, x2, y1);
        //f1.delta(v, x1, y2);
    };

    while(true)
    {
        {
            int v;
            size_t x, y, s;
            cin >> v >> x >> y >> s;
            delta(v, x, y, x+s, y+1);
        }
        for(size_t y = 0; y < 16; y++, cout << endl)
            for(size_t x = 0; x < 16; x++, cout << " ")
                cout << setw(3) << setfill(' ') << get(x, y, x+1, y+1);
    }


}
