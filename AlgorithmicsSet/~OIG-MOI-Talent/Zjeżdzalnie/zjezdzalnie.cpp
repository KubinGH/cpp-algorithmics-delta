#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct coor_t { T x, y; };
template<typename T>
struct get_neighbours
{
    uint32_t i = 0;
    T x, y, w, h, nx, ny;
    get_neighbours(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) { set_next(); }
    void set_next()
    {
        if(i <= 0 and x < w - 1)        nx = x + 1, ny = y, i = 1;
        else if(i <= 1 and y < h - 1)   nx = x, ny = y + 1, i = 2;
        else if(i <= 2 and x > 0)       nx = x - 1, ny = y, i = 3;
        else if(i <= 3 and y > 0)       nx = x, ny = y - 1, i = 4;
        else i = 5;
    }
    coor_t<T> operator* () { return {nx, ny}; }
    get_neighbours& operator++ () { set_next(); return *this; }
    get_neighbours& begin() { return *this; }
    get_neighbours& end() { return *this; }
    bool operator!= (get_neighbours& o) const { (void)o; return i <= 4; }
};

int main()
{
    uint32_t h, w;
    cin >> h >> w;
    vector<vector<uint32_t>> G(w*h);
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
    {
        cout << "(" << x << ", " << y << "): ";
        for(coor_t<uint32_t> c : get_neighbours<uint32_t>(x, y, w, h))
            cout << "(" << c.x << ", " << c.y << "); "; cout << endl;
    }
}
