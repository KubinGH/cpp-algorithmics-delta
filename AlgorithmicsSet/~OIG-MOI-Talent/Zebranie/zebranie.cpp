#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef int int32_t;
const size_t MAX = 1e5;

struct rect_t
{
    int32_t x1, y1, x2, y2;
    rect_t() : x1(0), y1(0), x2(0), y2(0) {}
    rect_t(int32_t x1, int32_t y1, int32_t x2, int32_t y2) :
        x1(x1), y1(y1), x2(x2), y2(y2) {}
    bool is_degenerate() const
    {
        return x1 > x2 or y1 > y2;
    }
    rect_t intersect(const rect_t& o) const
    {
        return rect_t(max(x1, o.x1), max(y1, o.y1),
                      min(x2, o.x2), min(y2, o.y2));
    }
};

int main()
{
    uint32_t n;
    scanf("%u", &n);
    if(n == 1) { printf("0"); return 0; }
    static int32_t X[MAX], Y[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t x, y;
        scanf("%d %d", &x, &y);
        X[i] = x - y; Y[i] = x + y;
    }
    int32_t lo = 0, hi = 2e6;
    while(lo < hi)
    {
        int32_t d = (lo + hi) / 2;
        rect_t valid(X[0]-d, Y[0]-d, X[0]+d, Y[0]+d);
        for(uint32_t i = 1; i < n; i++)
        {
            rect_t other(X[i]-d, Y[i]-d, X[i]+d, Y[i]+d);
            valid = valid.intersect(other);
            if(valid.is_degenerate())
                break;
        }
        if(valid.is_degenerate())
            lo = d + 1;
        else
            hi = d;
    }
    printf("%d", lo);
}
