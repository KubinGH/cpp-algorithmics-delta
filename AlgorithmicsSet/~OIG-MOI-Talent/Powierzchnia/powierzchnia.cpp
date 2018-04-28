#include <bits/stdc++.h>
#define RESULT(v) { cout << min((v), w*h-(v)); return 0; }
#define CLAMP(a, b, x) x = (x < a ? a : (x > b ? b : x))

using namespace std;

int main()
{
    double w, h, x1, y1, x2, y2;
    cin >> w >> h >> x1 >> y1 >> x2 >> y2;
    cout << fixed; cout.precision(2);
    if(x1 == x2)
        RESULT(x1*h);
    if(y1 == y2)
        RESULT(y1*w);
    if(x1 > x2)
        swap(x1, x2), swap(y1, y2);
    double a = (y2-y1)/(x2-x1), b = y1 - a*x1;
    double x0 = -b/a, xh = (h-b)/a;
    double y0 = (0 <= x0 and x0 <= w) ? 0 : (a > 0 ? b : a*w+b),
           yh = (0 <= xh and xh <= w) ? h : (a > 0 ? a*w+b : b);
    int16_t c_x0 = (x0 < 0 ? -1 : (x0 > w ? 1 : 0));
    int16_t c_xh = (xh < 0 ? -1 : (xh > w ? 1 : 0));
    if(c_x0 == 0 and c_xh == 0)
        RESULT(h*(min(x0, xh) + 0.5*abs(xh-x0)))
    if(abs(c_x0) == 1 and abs(c_xh) == 1)
        RESULT(w*(min(y0, yh) + 0.5*abs(yh-y0)));
    CLAMP(0, h, y0); CLAMP(0, h, yh);
    CLAMP(0, w, x0); CLAMP(0, w, xh);
    RESULT(0.5*abs(yh-y0)*abs(xh-x0));
}
