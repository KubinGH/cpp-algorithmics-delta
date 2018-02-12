#include <iostream>
#include <array>
#include <cmath>
#define C(i, j) (C0[j] - C0[i] - (DS[j] - DS[i]) * WS[i])
#define R(i, j) (C(0, i) + C(i+1, j) + C(j+1, n))
#define UPDATE(_j) result = min(result, R(i, (_j)))

using namespace std;

const size_t MAX = 20000;
const double PHI = (sqrt(5) + 1) / 2;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t n;
    cin >> n;
    static array<uint32_t, MAX> W, D;
    static array<uint32_t, MAX+1> WS, DS, C0;
    for(uint16_t i = 0; i < n; i++)
    {
        cin >> W[i] >> D[i];
        if(i > 0) { WS[i+1] = WS[i]; DS[i+1] = DS[i]; C0[i+1] = C0[i]; }
        WS[i+1] += W[i]; DS[i+1] += D[i];
        C0[i+1] += WS[i+1] * D[i];
    }
    uint32_t result = -1;
    for(uint16_t i = 0; i < 10; i++)
        for(uint16_t j = i + 1; j < n; j++)
            result = min(result, R(i, j));
    for(uint16_t i = 10; i < n - 10; i++)
    {
        uint32_t a = i+1, b = n;
        UPDATE((a+b)/2-2); UPDATE((a+b)/2-1); UPDATE((a+b)/2);
        UPDATE((a+b)/2+1); UPDATE((a+b)/2+2);
        double c = b - (b - a) / PHI, d = a + (b - a) / PHI;
        while(abs(c - d) > 1)
        {

            if(R(i, c) < R(i, d))
            {
                b = round(d);
                d = c;
                c = b - (b - a) / PHI;
            }
            else
            {
                a = round(c);
                c = d;
                d = a + (b - a) / PHI;
            }
            UPDATE((a+b)/2-2); UPDATE((a+b)/2-1); UPDATE((a+b)/2);
            UPDATE((a+b)/2+1); UPDATE((a+b)/2+2);
        }
    }
    for(uint16_t i = n - 10; i < n - 1; i++)
        for(uint16_t j = i + 1; j < n; j++)
            UPDATE(j);
    cout << result << endl;

}
