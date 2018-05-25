#include <bits/stdc++.h>

using namespace std;

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t m;
  cin >> m;
  for(uint32_t i = 0; i < m; i++)
  {
    uint32_t n;
    int64_t xf, yf;
    cin >> n >> xf >> yf;
    int64_t xi, yi;
    cin >> xi >> yi; xi -= xf; yi -= yf;
    int64_t x1 = xi, y1 = yi, x2, y2;
    int32_t guard = 0;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        cin >> x2 >> y2; x2 -= xf; y2 -= yf;
        // AxBy - AyBx
        int64_t a = x1*y2, b = y1*x2;
        if(a > b)       guard++;
        else if(a < b)  guard--;
        x1 = x2; y1 = y2;
    }
    int64_t a = x1*yi, b = y1*xi;
    if(a > b)       guard++;
    else if(a < b)  guard--;
    if(abs(guard) == n)
        cout << "TAK\n";
    else
        cout << "NIE\n";
  }
}
