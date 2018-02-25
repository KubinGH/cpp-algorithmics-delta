#include <bits/stdc++.h>

using namespace std;

struct rect
{
    int64_t x1, y1, x2, y2;
    rect() { x1 = y1 = x2 = y2 = 0; }
    rect(int _x1, int _y1, int _x2, int _y2) { x1 = _x1, y1 =_y1, x2 = _x2, y2 = _y2; }
    int64_t get_area()
    {
        return (x2 - x1) * (y2 - y1);
    }
    bool overlaps(rect o)
    {
        return not ((x2 < o.x1 or x1 > o.x2) or (y2 < o.y1 or y1 > o.y2));
    }
    rect get_overlap(rect o)
    {
        return rect(max(x1, o.x1), max(y1, o.y1), min(x2, o.x2), min(y2, o.y2));
    }
};

ostream& operator<<(ostream& out, const rect& o)
{
    out << "rect(" << o.x1 << " " << o.y1 << " " << o.x2 << " " << o.y2 << ")";
    return out;
}

istream& operator>>(istream& in, rect& o)
{
    in >> o.x1 >> o.y1 >> o.x2 >> o.y2;
    swap(o.y1, o.y2);
    return in;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    rect overlap;
    cin >> overlap;
    bool ok = true;
    for(uint32_t i = 1; i < n; i++)
    {
        rect current;
        cin >> current;
        if(overlap.overlaps(current))
            overlap = overlap.get_overlap(current);
        else
        {
            ok = false;
            break;
        }
    }
    if(ok)
        cout << overlap.get_area();
    else
        cout << '0';
}
